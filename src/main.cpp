#include "config_parser.h"
#include "http_client.h"
#include <iostream>

int main() {
  try {
    // Parse the JSON config file
    ConfigParser parser("../example.json");
    BotConfig config = parser.parse();

    std::cout << "Bot name: " << config.bot_name << "\n";

    // Perform HTTP requests via below struct
    HttpClient client;

    for (const auto &req : config.requests) {
      std::cout << "\nFetching [" << req.name << "] " << req.url << "...\n";

      std::string html = client.get(req.url);

      std::cout << "Fetched: " << html.size() << " bytes from " << req.url
                << " Content: \n"
                << html << "\n";
    }
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << "\n";
    return 1;
  }

  return 0;
}
