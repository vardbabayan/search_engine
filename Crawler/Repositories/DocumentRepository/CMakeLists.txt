project(DocumentRepository)

add_library(
    DocumentRepository SHARED

    DocumentRepositoryDB.hpp
    DocumentRepositoryDB.cpp

    Document.hpp
    Document.cpp
)

target_link_libraries(DocumentRepository)