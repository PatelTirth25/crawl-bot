#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "robots_parser.h"

TEST_CASE("robots.txt allows root path", "[robots]") {
  std::string robots = R"(
        User-agent: *
        Disallow: /private
    )";

  RobotsTxt parser(robots);

  REQUIRE(parser.isAllowed("/") == true);
}

TEST_CASE("robots.txt blocks disallowed path", "[robots]") {
  std::string robots = R"(
        User-agent: *
        Disallow: /search
    )";

  RobotsTxt parser(robots);

  REQUIRE(parser.isAllowed("/search") == false);
}

TEST_CASE("robots.txt allows non-matching path", "[robots]") {
  std::string robots = R"(
        User-agent: *
        Disallow: /admin
    )";

  RobotsTxt parser(robots);

  REQUIRE(parser.isAllowed("/public") == true);
}
