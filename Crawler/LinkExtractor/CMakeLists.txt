project(LinkExtractor)

add_library(
    LinkExtractor SHARED

    LinkExtractor.hpp
    LinkExtractor.cpp
)

target_link_libraries(LinkExtractor -lboost_regex)