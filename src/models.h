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

inline std::string getRobotsUrl(const std::string &url) {
  // find the 3rd slash in url
  size_t pos = url.find("/", 8); // Skip "https://"
  if (pos == std::string::npos)
    return url + "/robots.txt";
  return url.substr(0, pos) + "/robots.txt";
}

#endif
