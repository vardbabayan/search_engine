project(MysqlConnector)

set(CMAKE_CXX_STANDARD 17)

add_library( 
    MysqlConnector SHARED
    
    MysqlConnector.hpp
    MysqlConnector.cpp
)

target_link_libraries(MysqlConnector -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl -lresolv)
target_compile_options(MysqlConnector PUBLIC -L/usr/lib/x86_64-linux-gnu)