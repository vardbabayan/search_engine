project(MySqlConnector)

set(CMAKE_CXX_STANDARD 17)

add_library( 
    MySqlConnector SHARED

    MySqlConnector.hpp
    MySqlConnector.cpp
)

target_link_libraries(MySqlConnector -lmysqlcppconn)