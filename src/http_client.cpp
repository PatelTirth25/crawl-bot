#include "http_client.h"
#include <curl/curl.h>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

// Global init necessary for libcurl to prepare internal network resources
HttpClient::HttpClient() { curl_global_init(CURL_GLOBAL_DEFAULT); }
HttpClient::~HttpClient() { curl_global_cleanup(); }

// libcurl calls this multiple times as chunks of data arrive from the web
size_t HttpClient::writeCallback(void *contents, size_t size, size_t nmemb,
                                 void *userp) {
  size_t total_size = size * nmemb;

  // Cast userp back to our string to store the incoming chunk
  std::string *buffer = static_cast<std::string *>(userp);
  buffer->append(static_cast<char *>(contents), total_size);
  return total_size;
}

std::string HttpClient::get(const std::string &url) const {
  CURL *curl = curl_easy_init();
  if (!curl)
    throw std::runtime_error("Failed to initialize CURL");

  std::string response;

  // Set configuration: URL, User-Agent identification, and redirect following
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "CRAWL-Bot/1.0");
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  // Link our string response to the callback function
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HttpClient::writeCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  // Perform the actual network request
  CURLcode res = curl_easy_perform(curl);

  // Clean up local request handle immediately to prevent leaks
  if (res != CURLE_OK) {
    curl_easy_cleanup(curl);
    throw std::runtime_error(curl_easy_strerror(res));
  }

  curl_easy_cleanup(curl);
  return response;
}

// Simple helper to escape regex special characters
std::string escapeRegex(std::string text) {
  static const std::regex specChars{R"([-[\]{}()*+?.,\^$|#\s])"};
  return std::regex_replace(text, specChars, R"(\$&)");
}

bool HttpClient::isUrlAllowed(const std::string &robotsContent,
                              const std::string &url) const {

  // Extract the path (e.g., "/search" from "https://google.com/search")
  size_t pathPos = url.find("/", 8);
  std::string path = (pathPos == std::string::npos) ? "/" : url.substr(pathPos);

  // Create a Regex pattern
  // This pattern looks for "Disallow:" followed by any number of spaces,
  // then the specific path.
  try {
    std::string escapedPath = escapeRegex(path);

    // look for Disallow: [path]
    std::string pattern = "Disallow:\\s*" + escapedPath + "(\\s*|\\s*#.*)$";

    std::regex re(pattern, std::regex_constants::icase |
                               std::regex_constants::multiline);

    // Search the robotsContent for this pattern
    if (std::regex_search(robotsContent, re)) {
      return false; // Match found ,Disallowed
    }
  } catch (const std::regex_error &e) {
    // If regex fails, return false
    return false;
  }

  return true;
}
