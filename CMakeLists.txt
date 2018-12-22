cmake_minimum_required(VERSION 3.12)
project(majanGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(majanGame main.cpp Majan.h Majan.cpp Deck.h Deck.cpp Round.h Player.h Round.cpp Player.cpp Dice.h Dice.cpp Option.cpp Option.h)