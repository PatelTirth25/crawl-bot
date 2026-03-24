/*
 * Crawl Bot – CVMFS GSoC Evaluation Exercise
 *
 * This program implements a simple HTTP request bot that reads a JSON
 * configuration and fetches web pages while respecting robots.txt rules.
 *
 * Architecture Overview:
 *
 * 1. ConfigParser
 *    - Parses the input JSON configuration file using nlohmann-json.
 *    - Maps data into strongly-typed C++ structures (BotConfig, Request).
 *
 * 2. HttpClient
 *    - Lightweight wrapper around libcurl.
 *    - Performs HTTP GET requests and returns response bodies as strings.
 *    - Configured with a custom User-Agent for polite crawling behavior.
 *
 * 3. RobotsTxt
 *    - Parses robots.txt content for "User-agent: *".
 *    - Extracts Disallow rules and applies prefix-based matching.
 *    - Determines whether a given URL path is allowed to be fetched.
 *
 * 4. UrlUtils
 *    - Provides helper utilities for:
 *        • Extracting host and path from URLs
 *        • Constructing robots.txt URLs
 *        • Generating sanitized output filenames
 *
 * 5. main()
 *    - Loads configuration via ConfigParser
 *    - Iterates over configured requests:
 *        a) Fetch robots.txt (if available)
 *        b) Validate access permissions
 *        c) Fetch HTML content if allowed
 *        d) Store output in structured files under /out
 *
 * Note:
 *
 * - Components are intentionally separated:
 *     • Parsing (ConfigParser)
 *     • Networking (HttpClient)
 *     • Policy enforcement (RobotsTxt)
 *     • Utility logic (UrlUtils)
 *
 * - The implementation prioritizes clarity, modularity, and correctness.
 * - Testability is supported via modular design and unit tests (Catch2).
 */

#include "config_parser.h"
#include "http_client.h"
#include "robots_parser.h"
#include "url_utils.h"
#include <filesystem>
#include <fstream>
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

    std::string outputDir = "out";

    // Create directory if it doesn't exist
    std::filesystem::create_directories(outputDir);

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

      std::string filename = generateFilename(config.bot_name, req.url);

      // Full path: out/<filename>
      std::filesystem::path fullPath =
          std::filesystem::path(outputDir) / filename;

      std::ofstream outFile(fullPath);
      if (!outFile.is_open()) {
        std::cerr << "Failed to write file: " << fullPath << "\n";
      } else {
        outFile << html;
        outFile.close();

        std::cout << "Saved output to: " << fullPath << "\n";
      }
    }
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return 1;
  }
}
