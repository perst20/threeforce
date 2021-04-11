cmake_minimum_required(VERSION 3.17)
project(threeforce)

set(CMAKE_CXX_STANDARD 17)

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        ${X11_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        include
)

file(GLOB
        SOURCES src/*.cpp)

add_executable(threeforce ${SOURCES})

target_link_libraries(threeforce PRIVATE
        X11::X11
        OpenGL::GL
        OpenGL::GLU
        OpenGL::GLX
        GLEW::GLEW
        )

#add_custom_command(
#        TARGET threeforce POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${CMAKE_SOURCE_DIR}/res/*
#        ${CMAKE_CURRENT_BINARY_DIR})

ADD_CUSTOM_TARGET(
        copy_shader_files
        ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
)

ADD_DEPENDENCIES (threeforce copy_shader_files)