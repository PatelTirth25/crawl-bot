cmake_minimum_required(VERSION 3.10)
project(crawl_bot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(CURL REQUIRED)

# Main binary
add_executable(bot
    src/main.cpp
    src/config_parser.cpp
    src/http_client.cpp
    src/robots_parser.cpp
)

target_include_directories(bot PRIVATE src)
target_link_libraries(bot PRIVATE CURL::libcurl)

# Tests
enable_testing()
find_package(Catch2 REQUIRED)

add_executable(tests
    tests/test_config.cpp
    tests/test_robots.cpp
    tests/test_url.cpp

    src/config_parser.cpp
    src/robots_parser.cpp
)

target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME crawl_tests COMMAND tests)
