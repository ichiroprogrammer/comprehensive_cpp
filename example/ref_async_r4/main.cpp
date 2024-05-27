#include "controller.h"
#include "model.h"
#include "view.h"

// @@@ sample begin 0:0

int main(int, char**)
{                                                   //   修正前のソースコード
    auto view  = View{std::cout};                   // > auto view  = View{};
    auto model = Model{};                           //   auto model = Model{};
    model.Attach(view);                             //   model.Attach(view);
    auto controller = Controller{model, std::cin};  // > auto controller = Controller{model};

    return controller.WatchInput();
}
// @@@ sample end
