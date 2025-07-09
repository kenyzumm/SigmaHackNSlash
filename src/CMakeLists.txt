# CMakeLists.txt for src/

set(SOURCES
    main.cpp
    Game.cpp
    GameState.cpp
    MainMenuState.cpp
    SplashState.cpp
    StateMachine.cpp
    AssetsManager.cpp
    InputManager.cpp
    Logger.cpp
    Player.cpp
    Animation.cpp
    Collision.cpp
    Movement.cpp
    TileMap.cpp
    HUD.cpp
    Bullet.cpp
)

add_executable(SigmaHackNSlash ${SOURCES})

# Include headers from ../include
# (CMAKE_CURRENT_SOURCE_DIR is src/)
target_include_directories(SigmaHackNSlash PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link SFML (inherited from parent)
target_link_libraries(SigmaHackNSlash PRIVATE SFML::Graphics SFML::Window SFML::System)

# Set output directory for this target
set_target_properties(SigmaHackNSlash PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
) 
