cmake_minimum_required(VERSION 3.10)
project(crawl_bot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_executable(bot
    src/main.cpp
    src/config_parser.cpp
    src/http_client.cpp
)

target_include_directories(bot PRIVATE src)
target_link_libraries(bot PRIVATE CURL::libcurl)
