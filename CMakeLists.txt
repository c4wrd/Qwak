cmake_minimum_required(VERSION 3.3)
project(Qwak)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(QWAK_FILES Token.cpp Token.h location.h Lexer.cpp Lexer.h Parser.cpp Parser.h Tree.cpp Tree.h)
add_executable(Main main.cpp ${QWAK_FILES} keywords.h errors.h)
add_executable(LexerTests tests/lexer/test_file_io.cpp ${QWAK_FILES})