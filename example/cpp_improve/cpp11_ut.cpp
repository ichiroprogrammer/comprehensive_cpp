#include <regex>
#include <string>
#include <utility>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0

std::pair<std::string, std::string> url2addr(std::string const& url)
{
#if 0  // 正規表現のエスケープ
    std::regex re("^(https?|ftp):\\/\\/([^\\/\\s]+)(\\/.*)?$");
#else
    std::regex re(R"(^(https?|ftp)://([^/\s]+)(/.*)?$)");  // 生文字リテラル
#endif
    std::smatch match;

    if (std::regex_search(url, match, re) && match.size() > 3) {
        std::string host = match.str(2);
        std::string path = match.str(3);
        return {host, path};
    }
    else {
        return {"", ""};
    }
}
// @@@ sample end

TEST(cpp11, raw_literal)
{
    // @@@ sample begin 0:1

    std::string const url = "https://www.example.com/path/to/resource";

    auto [host, path] = url2addr(url);
    ASSERT_EQ("www.example.com", host);
    ASSERT_EQ("/path/to/resource", path);
    // @@@ sample end
}

}  // namespace
