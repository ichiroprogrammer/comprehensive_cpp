#include "gtest_wrapper.h"

#include "file_utils/load_store.h"
#include "file_utils/load_store_row.h"
#include "file_utils/path_utils.h"

namespace FileUtils {
namespace {

TEST(load_store, Row)
{
    auto const row_exp = std::string{"ut_data/load_store/pkg_org"};
    auto const row_act = std::string{"ut_data/load_store/pkg_act"};

    RemoveFile(row_act);

    auto row_data0 = std::optional<std::vector<std::string>>{LoadFromFile(row_act, Load_Strings)};

    // row_actはないのでエラーなはず
    ASSERT_FALSE(row_data0);

    // ディレクトリなのでエラーなはず
    ASSERT_FALSE(StoreToFile("ut_data/app1", *row_data0, StoreToStream));

    row_data0 = LoadFromFile(row_exp, Load_Strings);
    ASSERT_TRUE(row_data0);
    ASSERT_TRUE(StoreToFile(row_act, *row_data0, StoreToStream));

    auto row_data1 = std::optional<std::vector<std::string>>{LoadFromFile(row_act, Load_Strings)};
    ASSERT_TRUE(row_data1);

    ASSERT_EQ(*row_data0, *row_data1);

    RemoveFile(row_act);
}
}  // namespace
}  // namespace FileUtils
