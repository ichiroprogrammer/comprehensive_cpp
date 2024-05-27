#include "controller.h"
#include "model.h"
#include "view.h"

// @@@ sample begin 0:0

int main(int, char**)
{
    auto view  = View{};
    auto model = Model{};
    model.Attach(view);
    auto controller = Controller{model};

    return controller.WatchInput();
}
// @@@ sample end
