add_library( 
    page_loader STATIC
    LoadResult.hpp
    LoadResult.cpp
    PageLoader.hpp
    PageLoader.cpp
)

target_link_libraries(page_loader)