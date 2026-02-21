#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "models.h"
#include <string>

// Responsible for loading and parsing the JSON configuration file.
class ConfigParser {
public:
  explicit ConfigParser(const std::string &path);

  // Parses the JSON file and returns a BotConfig
  BotConfig parse() const;

private:
  std::string file_path;
};

#endif
