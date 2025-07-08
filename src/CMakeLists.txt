# Collect all source files
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
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        SFML::Graphics SFML::Window SFML::System)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "SigmaHackNSlash"
    DEBUG_POSTFIX "_d"
)

# Include directories for this target
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Platform specific settings
if(WIN32)
    # Copy SFML DLLs to output directory on Windows
    if(SFML_FOUND)
        foreach(SFML_LIB ${SFML_LIBRARIES})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${SFML_LIB}>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
            )
        endforeach()
    endif()
endif()

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Install resources
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources
    DESTINATION bin
    FILES_MATCHING PATTERN "*"
) 
