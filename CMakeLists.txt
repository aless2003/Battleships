# cmake_minimum_required(VERSION <specify CMake version here>)
project(Battleships)

set(CMAKE_CXX_STANDARD 14)

add_executable(Battleships main.cpp Spielfeld.cpp Spielfeld.hpp Spieler.cpp Spieler.hpp Schiffe.cpp Schiffe.hpp Design.cpp Design.hpp Game.cpp Game.hpp Feld.cpp Feld.hpp)