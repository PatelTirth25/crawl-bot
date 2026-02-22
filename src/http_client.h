#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

// Simple HTTP client using libcurl.
// Currently supports HTTP GET requests.

class HttpClient {
public:
  HttpClient();
  ~HttpClient();

  // Performs HTTP GET and returns response body
  std::string get(const std::string &url) const;
  bool isUrlAllowed(const std::string &robotsContent,
                    const std::string &url) const;

private:
  static size_t writeCallback(void *contents, size_t size, size_t nmemb,
                              void *userp);
};

#endif
