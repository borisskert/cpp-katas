cmake_minimum_required(VERSION 3.8)
project(cpp_katas)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) OR BUILD_TESTING)
    # init igloo git submodule
    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    else()
        message(FATAL_ERROR "Unable to checkout git submodules: Git or `.git` folder not found")
    endif()

    # https://github.com/joakimkarlsson/igloo/issues/21
    # To avoid errors during compilation of igloo
#    set(CMAKE_CXX_FLAGS "-Wno-error=deprecated-declarations")

    # igloo needs some CXX11 features like `std::auto_ptr` to be enabled
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_HAS_AUTO_PTR_ETC=1")

    include_directories("${PROJECT_SOURCE_DIR}/extern/igloo")
    add_subdirectory(test)
endif()
