project(DocumentExtractor)

add_library(
    DocumentExtractor SHARED

    DocumentExtractor.hpp
    DocumentExtractor.cpp

    DocumentInfo.hpp
    DocumentInfo.cpp
)

target_link_libraries(DocumentExtractor)