#pragma once

// @@@ sample begin 0:0

// Pod0, Pod1の定義は別ファイルでされていると前提。
struct Pod0;
struct Pod1;

// 下記関数宣言のコンパイルには、Pod0、Pod1の完全な定義は必要ない。
extern void forward_decl(Pod0 const* pod_0, Pod1* pod_1) noexcept;
extern Pod1 forward_decl(Pod0 const* pod_0) noexcept;
extern void forward_decl(Pod0 pod_0) noexcept;
// @@@ sample end
