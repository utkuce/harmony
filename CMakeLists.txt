cmake_minimum_required(VERSION 3.0.0)
project(harmony VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp util.cpp)

find_package(redis++ CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE redis++::redis++)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
