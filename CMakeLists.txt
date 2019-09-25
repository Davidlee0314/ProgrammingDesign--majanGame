cmake_minimum_required(VERSION 3.12)
project(majanGame)

set(CMAKE_CXX_STANDARD 14)
set(SOURCES
        Condition.cpp
        Condition.hpp
        GameMgr.cpp
        GameMgr.hpp
        main.cpp
        Majan.cpp
        Majan.hpp
        Texture.cpp
        Texture.hpp
        Player.hpp
        Player.cpp
        Deck.cpp
        Deck.hpp
        Option.hpp
        Option.cpp
        Dice.cpp
        Dice.hpp
        Round.hpp
        Round.cpp
)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
link_directories(/usr/local/lib)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
add_executable(majanGame ${SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})