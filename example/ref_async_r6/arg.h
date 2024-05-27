#include <fstream>
#include <iostream>
#include <optional>

// @@@ sample begin 0:0

struct opt_result {
    std::string ifile;
    std::string ofile;
};

std::optional<opt_result> getopt(int argc, char* const* argv);
// @@@ sample end
// @@@ sample begin 0:1

class IOStreamSelector {
public:
    IOStreamSelector(std::string ifile, std::string ofile)
        : ifile_{std::move(ifile)},
          ifs_{},
          is_{nullptr},
          ofile_{std::move(ofile)},
          ofs_{},
          os_{nullptr}
    {
    }

    bool          Open();
    std::istream& GetIStream();
    std::ostream& GetOStream();

private:
    // @@@ ignore begin

    std::string const ifile_;
    std::ifstream     ifs_;
    std::istream*     is_;

    std::string const ofile_;
    std::ofstream     ofs_;
    std::ostream*     os_;

    IOStreamSelector(IOStreamSelector const&)            = delete;
    IOStreamSelector& operator=(IOStreamSelector const&) = delete;
    // @@@ ignore end
};
// @@@ sample end
