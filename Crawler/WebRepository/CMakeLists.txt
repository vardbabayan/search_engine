project(WebRepository)

add_library(
    WebRepository SHARED

    WebRepository.hpp
    WebRepository.cpp

    WebSite.hpp
    WebSite.cpp
)

target_link_libraries(WebRepository)