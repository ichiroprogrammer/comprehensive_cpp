#include "view.h"

// @@@ sample begin 0:0

void View::update(Model const& model)
{
    for (auto const& str : model.GetStrings()) {  //   コメントを除き
        os_ << str << std::endl;                  //   ref_async_r4/view.cppと同じ
    }
}
// @@@ sample end
