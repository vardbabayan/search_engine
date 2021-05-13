project(WebRepository)

add_library(
    WebRepository SHARED

    WebRepository.hpp
    WebRepository.cpp

    Website.hpp
    Website.cpp
)

target_link_libraries(WebRepository)