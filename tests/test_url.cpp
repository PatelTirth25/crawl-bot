#include "url_utils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Extract robots.txt URL", "[url]") {
  std::string url = "https://example.com/page";

  REQUIRE(getRobotsUrl(url) == "https://example.com/robots.txt");
}

TEST_CASE("Extract path from URL", "[url]") {
  std::string url = "https://example.com/search?q=test";

  REQUIRE(getPathFromUrl(url) == "/search?q=test");
}
