#include "view.h"

// @@@ sample begin 0:0

void View::update(Model const& model)
{                                                 //   修正前のソースコード
    for (auto const& str : model.GetStrings()) {  //   for (auto const& str : model.GetStrings()) {
        os_ << str << std::endl;                  // >     std::cout << str << std::endl;
    }                                             //   }
}
// @@@ sample end
