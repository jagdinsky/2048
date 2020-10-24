cmake_minimum_required(VERSION 3.5)

add_executable(2048 main.cpp GameEngine.cpp GameLogic.cpp)

target_link_libraries(2048 display_lib)

file(COPY ../../data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
