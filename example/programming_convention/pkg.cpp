// @@@ sample begin 0:0

// PackageC内の*.cppファイルの内部とする
#include <memory>  // システムヘッダ
#include <mutex>   // システムヘッダ
#include <string>  // システムヘッダ

// PackageBがエクスポートするするヘッダを使用するために、
// 以下のようなコンパイルオプションが必要になる
//      -I<DIR>/PackageA/h
// <DIR>はコンパイラが実行されるディレクトリ
//
#include "PackageA/xxx.h"  // PackageAのインクルード
#include "PackageB/b0.h"   // PackageBのインクルード
#include "PackageB/b3.h"   // PackageBのインクルード
#include "internal.h"      // パッケージ外部非公開ヘッダのインクルード
// @@@ sample end
