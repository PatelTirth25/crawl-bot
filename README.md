# Crawl Bot

This project implements a small HTTP request bot in C++ as part of the CVMFS GSoC evaluation task.

The bot reads a JSON configuration file, fetches web pages using HTTP, respects `robots.txt` rules, and stores the fetched HTML content locally.

---

## Features

- JSON-based configuration parsing using `nlohmann-json`
- HTTP requests using `libcurl`
- Custom User-Agent support
- Basic `robots.txt` compliance (`User-agent: *`)
- Modular architecture (separation of parsing, networking, and policy logic)
- Saves fetched HTML to structured output files
- Basic unit testing using Catch2 + CTest

---

## Architecture

- **ConfigParser**
  - Parses the JSON configuration into C++ structures

- **HttpClient**
  - Wrapper around libcurl for HTTP GET requests

- **RobotsTxt**
  - Parses `robots.txt` and determines if a path is allowed

- **UrlUtils**
  - Utility functions for extracting host, path, and generating filenames

---

## Dependencies

- C++17
- libcurl
- nlohmann-json
- Catch2 (for tests)

## Install (Arch Linux)

```bash
sudo pacman -S curl nlohmann-json catch2
```

## Build

```bash
./build.sh
./build/bot file.json 
```

## Test

```bash
./build.sh
./build/tests
```
## Output

Fetched html content will be stored in ```./out/``` directory.
