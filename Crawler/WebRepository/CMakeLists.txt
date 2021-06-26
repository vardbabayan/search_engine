project(WebRepositoryDB)

add_library(
    WebRepositoryDB SHARED

    WebRepositoryDB.hpp
    WebRepositoryDB.cpp
    
    Website.hpp
    Website.cpp
)

target_link_libraries(WebRepositoryDB)