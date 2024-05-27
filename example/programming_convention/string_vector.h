#include <string>
#include <vector>

// @@@ sample begin 0:0

// このファイルをインクルードすると、
// そのファイルでのstd::vector<std::string>のインスタンス化は抑止される。
extern template class std::vector<std::string>;
// @@@ sample end
