cmake_minimum_required(VERSION 3.16)
project(SigmaHackNSlash)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

# Enable testing if requested
option(ENABLE_TESTS "Enable unit tests" OFF)
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/GameState.cpp
    src/Player.cpp
    src/Movement.cpp
    src/TileMap.cpp
    src/InputManager.cpp
    src/AssetsManager.cpp
    src/Animation.cpp
    src/Collision.cpp
    src/StateMachine.cpp
    src/SplashState.cpp
    src/MainMenuState.cpp
    src/Logger.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

# Set working directory for resources
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
