cmake_minimum_required(VERSION 3.16)

# Enable testing
enable_testing()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Test executables
add_executable(UnitTests
    test_main.cpp
    test_framework.h
    test_framework.cpp
    test_movement.cpp
    test_player.cpp
    test_tilemap.cpp
    test_input_manager.cpp
    test_assets_manager.cpp
    test_animation.cpp
    test_collision.cpp
    integration_tests.cpp
    performance_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/InputManager.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/TileMap.cpp
    ${CMAKE_SOURCE_DIR}/src/Movement.cpp
    ${CMAKE_SOURCE_DIR}/src/Animation.cpp
    ${CMAKE_SOURCE_DIR}/src/Collision.cpp
    ${CMAKE_SOURCE_DIR}/src/AssetsManager.cpp
    ${CMAKE_SOURCE_DIR}/src/Logger.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/GameState.cpp
    ${CMAKE_SOURCE_DIR}/src/StateMachine.cpp
    ${CMAKE_SOURCE_DIR}/src/SplashState.cpp
    ${CMAKE_SOURCE_DIR}/src/MainMenuState.cpp
)

# Link libraries
target_link_libraries(UnitTests
    SFML::Graphics
    SFML::Window
    SFML::System
)

# Add test
add_test(NAME UnitTests COMMAND UnitTests)

# Set working directory for tests
set_tests_properties(UnitTests PROPERTIES
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
) 