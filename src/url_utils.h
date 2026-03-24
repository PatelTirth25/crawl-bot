#ifndef URL_UTILS_H
#define URL_UTILS_H

#include <algorithm>
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

// Extract host (e.g., www.google.com)
inline std::string getHostFromUrl(const std::string &url) {
  size_t start = url.find("://");
  start = (start == std::string::npos) ? 0 : start + 3;

  size_t end = url.find("/", start);
  return (end == std::string::npos) ? url.substr(start)
                                    : url.substr(start, end - start);
}

// Sanitize string for safe filename
inline std::string sanitize(const std::string &input) {
  std::string result = input;

  std::replace(result.begin(), result.end(), '/', '-');
  std::replace(result.begin(), result.end(), '?', '-');
  std::replace(result.begin(), result.end(), '&', '-');
  std::replace(result.begin(), result.end(), '=', '-');

  if (result.empty() || result == "-")
    return "root";

  return result;
}

// Generate filename
inline std::string generateFilename(const std::string &botName,
                                    const std::string &url) {
  std::string host = getHostFromUrl(url);
  std::string path = getPathFromUrl(url);

  path = sanitize(path);

  return botName + "-" + host + "-" + path + ".html";
}

#endif
