#include "config_parser.h"
#include <catch2/catch_test_macros.hpp>
#include <fstream>

TEST_CASE("Parse valid config", "[config]") {
  std::ofstream file("test_config.json");

  file << R"({
        "bot_name": "testBot",
        "requests": [
            { "name": "Test", "url": "https://example.com" }
        ]
    })";

  file.close();

  ConfigParser parser("test_config.json");
  BotConfig config = parser.parse();

  REQUIRE(config.bot_name == "testBot");
  REQUIRE(config.requests.size() == 1);
  REQUIRE(config.requests[0].url == "https://example.com");
}
