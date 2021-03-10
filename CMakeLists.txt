cmake_minimum_required(VERSION 3.0)

project("search_engine")

#set(CMALE_CXX_FLAGS "-std=c++11 -03")

include_directories(${PROJECT_SOURCE_DIR} "Crawler/PageLoader")
include_directories(${PROJECT_SOURCE_DIR} "Crawler/HTMLParser")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurl -l gumbo")

#include_directories(${PROJECT_SOURCE_DIR} "json/include/")

file(GLOB CPP "*.cpp")

add_executable(${PROJECT_NAME} Crawler/CrawlerMain.cpp)