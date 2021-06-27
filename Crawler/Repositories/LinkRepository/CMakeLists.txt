project(LinkRepository)

add_library(
    LinkRepository SHARED

    LinkRepositoryDB.hpp
    LinkRepositoryDB.cpp

    LinkEntry.hpp
    LinkEntry.cpp

    LinkStatus.hpp
)

target_link_libraries(LinkRepository)