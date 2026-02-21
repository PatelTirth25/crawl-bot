#include "config_parser.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

// Constructor stores the file path for later use
ConfigParser::ConfigParser(const std::string &path) : file_path(path) {}

BotConfig ConfigParser::parse() const {
  std::ifstream input(file_path);
  if (!input.is_open()) {
    throw std::runtime_error("Failed to open config file: " + file_path);
  }

  json j;
  input >> j; // Load file stream into the JSON object

  BotConfig config;

  config.bot_name = j.at("bot_name").get<std::string>();

  // Iterate through the 'requests' array and populate our vector
  for (const auto &item : j.at("requests")) {
    Request req;
    req.name = item.at("name").get<std::string>();
    req.url = item.at("url").get<std::string>();
    config.requests.push_back(req);
  }

  return config;
}
