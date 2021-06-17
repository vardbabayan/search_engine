cmake_minimum_required(VERSION 3.0)

project("Crawler")

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} CrawlerMain.cpp)

add_subdirectory(PageLoader)
add_subdirectory(HtmlDocument)
add_subdirectory(LinkExtractor)
add_subdirectory(LinkRepository)
add_subdirectory(WebRepository)
add_subdirectory(DocumentRepository)
add_subdirectory(DocumentExtractor)
add_subdirectory(MySql)

set_target_properties(PageLoader PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/PageLoader/libPageLoader.so"
)

set_target_properties(HtmlDocument PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/HtmlDocument/libHtmlDocument.so"
)

set_target_properties(LinkExtractor PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/LinkExtractor/libLinkExtractor.so"
)

set_target_properties(MySqlConnector PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/MySql/libMySqlConnector.so"
)

set_target_properties(LinkRepository PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/LinkRepository/libLinkRepository.so"
)

set_target_properties(WebRepositoryDB PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/WebRepository/libWebRepositoryDB.so"
)

set_target_properties(DocumentRepository PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DocumentRepository/libDocumentRepository.so"
)

set_target_properties(DocumentExtractor PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DocumentExtractor/libDocumentExtractor.so"
)

target_link_libraries(${PROJECT_NAME} PageLoader HtmlDocument LinkExtractor MySqlConnector LinkRepository 
                                      WebRepositoryDB DocumentExtractor DocumentRepository)