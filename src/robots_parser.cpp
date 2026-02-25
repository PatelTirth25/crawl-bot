#include "robots_parser.h"
#include <sstream>

RobotsTxt::RobotsTxt(const std::string &content) {
  std::istringstream stream(content);
  std::string line;
  bool applies = false;

  while (std::getline(stream, line)) {
    // Remove comments
    auto comment = line.find('#');
    if (comment != std::string::npos)
      line = line.substr(0, comment);

    // Trim whitespace
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);

    if (line.empty())
      continue;

    if (line.rfind("User-agent:", 0) == 0) {
      std::string agent = line.substr(11);
      agent.erase(0, agent.find_first_not_of(" \t"));
      applies = (agent == "*");
    }

    if (applies && line.rfind("Disallow:", 0) == 0) {
      std::string path = line.substr(9);
      path.erase(0, path.find_first_not_of(" \t"));
      if (!path.empty())
        disallowed_paths.push_back(path);
    }
  }
}

bool RobotsTxt::isAllowed(const std::string &path) const {
  for (const auto &disallowed : disallowed_paths) {
    if (path.rfind(disallowed, 0) == 0) {
      return false; // prefix match
    }
  }
  return true;
}
