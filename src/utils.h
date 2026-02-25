#ifndef URL_UTILS_H
#define URL_UTILS_H

#include <string>

// Extracts the robots.txt URL from a full URL
inline std::string getRobotsUrl(const std::string &url) {
  size_t pos = url.find("/", 8); // skip scheme
  if (pos == std::string::npos)
    return url + "/robots.txt";
  return url.substr(0, pos) + "/robots.txt";
}

// Extracts path from URL
inline std::string getPathFromUrl(const std::string &url) {
  size_t pos = url.find("/", 8);
  return (pos == std::string::npos) ? "/" : url.substr(pos);
}

#endif
