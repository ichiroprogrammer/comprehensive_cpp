#include <unistd.h>

#include <cassert>

#include "arg.h"

// @@@ sample begin 0:0

std::optional<opt_result> getopt(int argc, char* const* argv)
{
    auto opt   = int{};
    auto ifile = std::string{};
    auto ofile = std::string{};

    // @@@ ignore begin
    optind = 0;

    while ((opt = ::getopt(argc, argv, "hi:o:")) != -1) {
        switch (opt) {
        case 'i':
            ifile = optarg;
            break;
        case 'o':
            ofile = optarg;
            break;
        case 'h':
        default:
            return std::nullopt;
        }
    }

    // @@@ ignore end
    return opt_result{std::move(ifile), std::move(ofile)};
}
// @@@ sample end
// @@@ sample begin 0:1

namespace {
template <typename FSTREAM, typename IOSTREAM>
bool select_iostream(std::string const& filename, FSTREAM& fs, IOSTREAM& cin_cout, IOSTREAM*& output)
{
    output = &cin_cout;

    if (filename.size() != 0) {
        fs.open(filename);
        if (!fs) {
            return false;
        }
        output = &fs;
    }

    return true;
}
}  // namespace

bool IOStreamSelector::Open()
{
    if (!select_iostream(ifile_, ifs_, std::cin, is_)) {
        return false;
    }

    return select_iostream(ofile_, ofs_, std::cout, os_);
}

std::istream& IOStreamSelector::GetIStream()
{
    assert(is_ != nullptr);

    return *is_;
}

std::ostream& IOStreamSelector::GetOStream()
{
    assert(os_ != nullptr);

    return *os_;
}
// @@@ sample end
