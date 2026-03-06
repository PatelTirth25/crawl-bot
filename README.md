# Crawl Bot (CVMFS Evaluation Exercise)

This project implements a small HTTP request bot in C++.

## Features

- JSON-based configuration
- HTTP requests using libcurl
- robots.txt compliance for User-agent: *
- Modular architecture

## Architecture

- **ConfigParser** – parses the JSON configuration
- **HttpClient** – handles HTTP requests
- **RobotsTxt** – parses robots.txt and enforces crawling rules

## Build

```bash
./build.sh
./build/bot file.json 
```
