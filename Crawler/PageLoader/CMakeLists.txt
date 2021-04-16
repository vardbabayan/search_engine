project(PageLoader)

add_library( 
    PageLoader SHARED
    
    LoadResult.hpp
    LoadResult.cpp

    PageLoader.hpp
    PageLoader.cpp
)

target_link_libraries(PageLoader -lcurl)