#pragma once
#include <optional>
#include <utility>

#include "arch_pkg.h"
#include "cpp_deps.h"
#include "file_utils/path_utils.h"

namespace Dependency {

// LoadStore
bool                              StoreToStream(std::ostream& os, FileUtils::Paths_t const& paths);
std::optional<FileUtils::Paths_t> Load_Paths(std::istream& is);

// Dirs2Srcs_t
bool StoreToStream(std::ostream& os, FileUtils::Dirs2Srcs_t const& dirs2srcs);
std::optional<FileUtils::Dirs2Srcs_t> Load_Dirs2Srcs(std::istream& is);

// DepRels_t
bool                     StoreToStream(std::ostream& os, DepRels_t const& dep_rels);
std::optional<DepRels_t> Load_DepRels(std::istream& is);

// Arch_t
bool StoreToStream(std::ostream& os, Arch_t const& arch);
}  // namespace Dependency
