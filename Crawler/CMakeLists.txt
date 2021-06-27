cmake_minimum_required(VERSION 3.0)

project("Crawler")

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} CrawlerMain.cpp)

add_subdirectory(PageLoader)
add_subdirectory(HtmlDocument)
add_subdirectory(LinkExtractor)
add_subdirectory(Repositories/LinkRepository)
add_subdirectory(Repositories/WebRepository)
add_subdirectory(Repositories/DocumentRepository)
add_subdirectory(DocumentExtractor)
add_subdirectory(MySqlConnector)

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
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/MySqlСonnector/libMySqlConnector.so"
)

set_target_properties(LinkRepository PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Repositories/LinkRepository/libLinkRepository.so"
)

set_target_properties(WebRepositoryDB PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Repositories/WebRepository/libWebRepositoryDB.so"
)

set_target_properties(DocumentRepository PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Repositories/DocumentRepository/libDocumentRepository.so"
)

set_target_properties(DocumentExtractor PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/DocumentExtractor/libDocumentExtractor.so"
)

target_link_libraries(${PROJECT_NAME} PageLoader HtmlDocument LinkExtractor MySqlConnector LinkRepository 
                                      WebRepositoryDB DocumentExtractor DocumentRepository)