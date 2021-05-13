project(LinkRepository)

add_library(
    LinkRepository SHARED

    LinkRepository.hpp
    LinkRepository.cpp

    LinkEntry.hpp
    LinkEntry.cpp

    LinkStatus.hpp
)

target_link_libraries(LinkRepository (mysql_config --cflags), (mysql_config --libs))