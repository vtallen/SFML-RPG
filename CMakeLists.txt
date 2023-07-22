cmake_minimum_required(VERSION 3.14)
project(RPG_ENGINE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
        main.cpp
        game.cpp game.h

        engine/state.cpp engine/state.h
        states/game_state.cpp states/game_state.h
        engine/entity.cpp engine/entity.h
        states/main_menu_state.cpp states/main_menu_state.h

        engine/gui/button.cpp engine/gui/button.h
        entities/player.cpp entities/player.h
        engine/entity_components/movement_component.cpp engine/entity_components/movement_component.h
        engine/entity_components/animation_component.cpp engine/entity_components/animation_component.h

        states/editor_state.cpp states/editor_state.h
        engine/entity_components/hitbox_component.cpp engine/entity_components/hitbox_component.h engine/entity_components/hitbox_component.cpp engine/tile/tile.cpp engine/tile/tile.h)
add_executable(RPG_ENGINE ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(RPG_ENGINE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
