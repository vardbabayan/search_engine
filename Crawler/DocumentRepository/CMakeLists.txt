project(DocumentRepository)

add_library(
    DocumentRepository SHARED

    DocumentRepository.hpp
    DocumentRepository.cpp

    Document.hpp
    Document.cpp
)

target_link_libraries(DocumentRepository)