project(HtmlDocument)

add_library(
    HtmlDocument SHARED

    HtmlDocument.hpp
    HtmlDocument.cpp

    HtmlElement.hpp
    HtmlElement.cpp

    HtmlNode.hpp
    HtmlNode.cpp
)

target_link_libraries(HtmlDocument -lgumbo)