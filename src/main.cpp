#include "config_parser.h"
#include "http_client.h"
#include <iostream>

int main(int argc, char *argv[]) {
  // Check if the user provided exactly one argument
  if (argc != 2) {
    std::cerr << "Usage Error: Missing configuration file.\n";
    std::cout << "Usage: ./bot <config_file.json>\n";
    return 1;
  }

  // Use the argument from the command line instead of a hardcoded string
  std::string configFilePath = argv[1];

  try {
    ConfigParser parser(configFilePath);
    BotConfig config = parser.parse();

    std::cout << "Bot name: " << config.bot_name << "\n";

    HttpClient client;

    for (const auto &req : config.requests) {
      std::cout << "\nFetching [" << req.name << "] " << req.url << "...\n";

      // The GET request happens here
      std::string html = client.get(req.url);

      std::cout << "Fetched " << html.size() << " bytes from " << req.url
                << "\n";
    }
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return 1;
  }

  return 0;
}
