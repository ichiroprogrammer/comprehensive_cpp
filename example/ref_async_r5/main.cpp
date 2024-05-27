#include <unistd.h>

#include <fstream>

#include "arg.h"
#include "controller.h"
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
    //                                                      //   修正前のソースコード
    auto view  = View{ios.GetOStream()};                    // > auto view  = View{std::cout};
    auto model = Model{};                                   //   auto model = {};
    model.Attach(view);                                     //   model.Attach(view);
    auto controller = Controller{model, ios.GetIStream()};  // > auto controller
                                                            //       = Controller{model, std::cin};

    return controller.WatchInput();
}
// @@@ sample end
