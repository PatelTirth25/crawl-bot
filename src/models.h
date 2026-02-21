#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

// Represents a single HTTP request entry from the JSON file
struct Request {
  std::string name;
  std::string url;
};

// Represents the full bot configuration.
struct BotConfig {
  std::string bot_name;
  std::vector<Request> requests;
};

#endif
