cmake_minimum_required(VERSION 3.0)

project("Crawler")

set(CMAKE_CXX_STANDARD 17)

include_directories("PageLoader")
include_directories("HtmlDocument")
include_directories("LinkExtractor")
include_directories("LinkRepository")
include_directories("WebRepository")

add_executable(${PROJECT_NAME} CrawlerMain.cpp)

add_subdirectory(PageLoader)
add_subdirectory(HtmlDocument)
add_subdirectory(LinkExtractor)
add_subdirectory(LinkRepository)
add_subdirectory(WebRepository)

set_target_properties(PageLoader PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/PageLoader/libPageLoader.so"
)

set_target_properties(HtmlDocument PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/HtmlDocument/libpage_loader.so"
)

set_target_properties(LinkExtractor PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/PageLoader/libLinkExtractor.so"
)

set_target_properties(LinkRepository PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/PageLoader/libLinkExtractor.so"
)

set_target_properties(WebRepository PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/WebRepository/libLinkExtractor.so"
)

target_link_libraries(${PROJECT_NAME} PageLoader HtmlDocument LinkExtractor LinkRepository WebRepository)