// @@@ sample begin 0:0

#include <string>  // OK

#include "../h/suppress_warning.h"  // NG   上方向へのファイルパスは禁止

#include "../header.h"  // NG   上方向へのファイルパスは禁止
#include "inc/xxx.h"    // OK
// @@@ sample end

struct Pod0 {
    int a;
};

struct Pod1 {
    int a;
};

Pod1 forward_decl(Pod0 const* pod_0) noexcept
{
    if (pod_0 == nullptr) {
        return Pod1{0};
    }

    return Pod1{pod_0->a};
}

void forward_decl(Pod0 pod_0) noexcept { IGNORE_UNUSED_VAR(pod_0); }

void forward_decl(Pod0 const* pod_0, Pod1* pod_1) noexcept
{
    if (pod_0 == nullptr || pod_1 == nullptr) {
        return;
    }

    pod_1->a = pod_0->a;
}
