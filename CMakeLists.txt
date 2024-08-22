cmake_minimum_required(VERSION 3.8)
project(module-32_task-2)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(module-32_task-2 main.cpp)

target_link_libraries(module-32_task-2 PRIVATE nlohmann_json::nlohmann_json)
