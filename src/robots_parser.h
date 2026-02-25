#ifndef ROBOTS_PARSER_H
#define ROBOTS_PARSER_H

#include <string>
#include <vector>

class RobotsTxt {
public:
  explicit RobotsTxt(const std::string &content);

  // Checks whether a given URL path is allowed
  bool isAllowed(const std::string &path) const;

private:
  std::vector<std::string> disallowed_paths;
};

#endif
