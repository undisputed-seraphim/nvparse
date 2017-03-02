cmake_minimum_required(VERSION 3.0.2)
project(nvparse)

set(inc_dir ${CMAKE_SOURCE_DIR}/include)
file(GLOB src ${CMAKE_SOURCE_DIR}/src/*.*)
file(GLOB bison_src ${CMAKE_BINARY_DIR}/bison/*.cpp ${CMAKE_SOURCE_DIR}/bison/*.hpp)
file(GLOB flex_src ${CMAKE_BINARY_DIR}/flex/*.cpp)

if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

message(STATUS "${bison_src}")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

add_library(nvparse ${src} ${bison_src} ${flex_src})
target_include_directories(nvparse PUBLIC ${inc_dir} ${GLUT_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
target_link_libraries(nvparse PUBLIC ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})