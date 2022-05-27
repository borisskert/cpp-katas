file(GLOB_RECURSE SOURCES *.cpp)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

add_library(cpp_katas_lib ${SOURCES})

target_sources(cpp_katas_lib PUBLIC ${SOURCES})
target_include_directories(cpp_katas_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(cpp_katas_lib)

