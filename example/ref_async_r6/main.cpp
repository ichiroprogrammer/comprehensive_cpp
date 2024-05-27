#include <unistd.h>

#include <fstream>

#include "arg.h"
#include "controller.h"
#include "lib.h"
#include "model.h"
#include "view.h"

// @@@ sample begin 0:0

namespace {

void how_to_use(std::string_view program)
{
    std::cerr << program << " [OPTIONS]" << std::endl;
    std::cerr << "   -i <input-file>" << std::endl;
    std::cerr << "   -o <output-file>" << std::endl;
}
}  // namespace

int main(int argc, char** argv)
{
    auto ret = getopt(argc, argv);
    if (!ret) {
        how_to_use(argv[0]);
        return __LINE__;
    }

    auto ios = IOStreamSelector{std::move(ret->ifile), std::move(ret->ofile)};

    if (!ios.Open()) {
        how_to_use(argv[0]);
        return __LINE__;
    }

    auto view  = View{ios.GetOStream()};
    auto model = Model{};
    model.Attach(view);
    auto controller = Controller{model, ios.GetIStream()};

    controller.WatchInput();

    Dispatcher::Inst().ExecUntilStop();

    return controller.GetExitCode();
}
// @@@ sample end
