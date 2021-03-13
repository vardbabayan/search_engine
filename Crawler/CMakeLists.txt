cmake_minimum_required(VERSION 3.0)

project("search_engine")


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurl -l gumbo")

add_link_options(-lcurl)

add_subdirectory(PageLoader)

file(GLOB CPP "*.cpp")

add_executable(${PROJECT_NAME} CrawlerMain.cpp)