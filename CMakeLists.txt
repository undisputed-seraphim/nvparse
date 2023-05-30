cmake_minimum_required(VERSION 3.0.2)
project(nvparse)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(inc_dir ${CMAKE_SOURCE_DIR}/include)
file(GLOB src ${CMAKE_SOURCE_DIR}/src/*.*)

if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(GLEW_USE_STATIC_LIBS OFF)
find_package(GLEW REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bison)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/flex)
execute_process(COMMAND ${BISON_EXECUTABLE} "-d" "-p" "ps10_" "-o" "${CMAKE_BINARY_DIR}/bison/_ps1.0_parser.cpp" "${CMAKE_SOURCE_DIR}/bison/ps1.0_grammar.y")
execute_process(COMMAND ${BISON_EXECUTABLE} "-d" "-p" "rc10_" "-o" "${CMAKE_BINARY_DIR}/bison/_rc1.0_parser.cpp" "${CMAKE_SOURCE_DIR}/bison/rc1.0_grammar.y")
execute_process(COMMAND ${BISON_EXECUTABLE} "-d" "-p" "ts10_" "-o" "${CMAKE_BINARY_DIR}/bison/_ts1.0_parser.cpp" "${CMAKE_SOURCE_DIR}/bison/ts1.0_grammar.y")
execute_process(COMMAND ${BISON_EXECUTABLE} "-d" "-p" "vs10_" "-o" "${CMAKE_BINARY_DIR}/bison/_vs1.0_parser.cpp" "${CMAKE_SOURCE_DIR}/bison/vs1.0_grammar.y")
execute_process(COMMAND ${FLEX_EXECUTABLE} "-P" "ps10_" "-o" "${CMAKE_BINARY_DIR}/flex/_ps1.0_lexer.cpp" "${CMAKE_SOURCE_DIR}/flex/ps1.0_tokens.l")
execute_process(COMMAND ${FLEX_EXECUTABLE} "-P" "rc10_" "-o" "${CMAKE_BINARY_DIR}/flex/_rc1.0_lexer.cpp" "${CMAKE_SOURCE_DIR}/flex/rc1.0_tokens.l")
execute_process(COMMAND ${FLEX_EXECUTABLE} "-P" "ts10_" "-o" "${CMAKE_BINARY_DIR}/flex/_ts1.0_lexer.cpp" "${CMAKE_SOURCE_DIR}/flex/ts1.0_tokens.l")
execute_process(COMMAND ${FLEX_EXECUTABLE} "-P" "vs10_" "-o" "${CMAKE_BINARY_DIR}/flex/_vs1.0_lexer.cpp" "${CMAKE_SOURCE_DIR}/flex/vs1.0_tokens.l")
file(GLOB nvparse_lexer_parser_src ${CMAKE_BINARY_DIR}/bison/* ${CMAKE_BINARY_DIR}/flex/* )
add_library(nvparse_lexer_parser STATIC ${nvparse_lexer_parser_src})
target_include_directories(nvparse_lexer_parser PUBLIC ${CMAKE_BINARY_DIR}/bison ${CMAKE_SOURCE_DIR}/src)

add_library(nvparse STATIC ${src})
target_include_directories(nvparse PUBLIC ${inc_dir})
target_link_libraries(nvparse PUBLIC GLUT::GLUT GLEW::glew OpenGL::OpenGL nvparse_lexer_parser_src)

include(GNUInstallDirs)

install(TARGETS nvparse EXPORT nvparse-targets)
install(FILES "${CMAKE_SOURCE_DIR}/include/nvparse.h" DESTINATION CMAKE_INSTALL_INCLUDEDIR)
