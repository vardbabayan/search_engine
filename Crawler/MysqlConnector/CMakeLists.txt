project(MysqlConnector)

set(CMAKE_CXX_STANDARD 17)

add_library( 
    MysqlConnector SHARED
    
    MysqlConnector.hpp
    MysqlConnector.cpp
)

target_link_libraries(MysqlConnector `mysql_config --cflags --libs`)