cmake_minimum_required(VERSION 3.0)
project(Battleships)

set(CMAKE_CXX_STANDARD 14)
link_libraries(winmm)
link_libraries(pthread)
add_executable(Battleships main.cpp Spielfeld.cpp Spielfeld.hpp Spieler.cpp Spieler.hpp Schiffe.cpp Schiffe.hpp Game.cpp Game.hpp Feld.cpp Feld.hpp AudioSystem.cpp AudioSystem.hpp)