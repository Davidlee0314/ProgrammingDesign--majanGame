cmake_minimum_required(VERSION 3.12)
project(majanGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(majanGame Condition.cpp Condition.hpp GameMgr.cpp GameMgr.hpp main.cpp Majan.cpp Majan.hpp Texture.cpp Texture.hpp Player.hpp Player.cpp Deck.cpp Deck.hpp Option.hpp Option.cpp Dice.cpp Dice.hpp Round.hpp Round.cpp)

target_link_libraries(majanGame SDL2main SDL2 SDL2_test SDL2_image)