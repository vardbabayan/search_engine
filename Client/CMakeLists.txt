cmake_minimum_required(VERSION 3.0)
project(client)


find_package(Boost REQUIRED COMPONENTS system thread)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
  add_executable(client client.cpp)
  target_link_libraries(client ${Boost_LIBRARIES} pthread)
endif()
