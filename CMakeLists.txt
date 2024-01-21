cmake_minimum_required(VERSION 3.28)
project(TankGamePA9)

# dependencies
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

# sources
set(game_src game/src)
add_executable(TankGame
    ${game_src}/main.cpp
    ${game_src}/Game.cpp
    ${game_src}/Map.cpp
    ${game_src}/Scene.h
    ${game_src}/Tank.cpp
    ${game_src}/Tile.cpp
    ${game_src}/bullets/BulletSystem.cpp
    ${game_src}/bullets/Bullet.cpp
    ${game_src}/kinematics/BodySystem.cpp
    ${game_src}/kinematics/AxisBoxBody.cpp
    ${game_src}/kinematics/CircleBody.cpp
    ${game_src}/math/Vec2.cpp
    ${game_src}/resources/ResourceManager.cpp
)

# libraries
target_link_libraries(TankGame PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)

# compiler flags
target_compile_features(TankGame PUBLIC cxx_std_17)