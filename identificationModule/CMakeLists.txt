file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library(identification-module SHARED ${SOURCES})
target_link_libraries(identification-module LINK_PRIVATE sc-memory)

target_include_directories(identification-module PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})