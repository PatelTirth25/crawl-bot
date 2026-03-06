/*
 * Simple HTTP request bot.
 *
 * Architecture:
 *
 * 1. ConfigParser
 *    - Reads the JSON configuration file.
 *    - Converts it into C++ structures (BotConfig, Request).
 *
 * 2. HttpClient
 *    - Wrapper around curl.
 *    - Performs HTTP GET requests and returns the response body.
 *    - Uses a custom User-Agent as required by crawlers.
 *
 * 3. RobotsTxt
 *    - Parses robots.txt rules for the generic user agent (*).
 *    - Extracts Disallow rules and checks whether a path is allowed.
 *
 * 4. main()
 *    - Loads configuration.
 *    - For each request:
 *        a) Fetch robots.txt
 *        b) Verify crawling permission
 *        c) Fetch HTML content if allowed
 *
 * The implementation keeps components modular.
 */

#include "config_parser.h"
#include "http_client.h"
#include "robots_parser.h"
#include "utils.h"

#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: ./bot <config.json>\n";
    return 1;
  }

  try {
    ConfigParser parser(argv[1]);
    BotConfig config = parser.parse();

    HttpClient client;

    for (const auto &req : config.requests) {
      std::string robotsUrl = getRobotsUrl(req.url);

      try {
        std::string robotsContent = client.get(robotsUrl);
        RobotsTxt robots(robotsContent);

        if (!robots.isAllowed(getPathFromUrl(req.url))) {
          std::cout << "Skipping " << req.url << " (robots.txt disallow)\n";
          continue;
        }
      } catch (...) {
        std::cout << "robots.txt not found, proceeding...\n";
      }

      std::string html = client.get(req.url);
      std::cout << "Fetched " << html.size() << " bytes from " << req.url
                << "\n";
    }
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return 1;
  }
}
