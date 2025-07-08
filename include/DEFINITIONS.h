#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// Path to log file
#define LOG_FILEPATH "../log.txt"

// Paths to graphical resources
#define SPLASHSTATE_BACKGROUND_PATH             "../../resources/background_splash.png" // Splash screen background
#define SPLASHSTATE_TITLE_PATH                 "../../resources/splash_title.png"
#define SPLASHSTATE_SHOWTIME 3.0f // Splash screen display time
#define MAINMENU_BACKGROUND_PATH                "../../resources/background_splash.png" // Main menu background
#define MAINMENU_TITLE_PATH                     "../../resources/splash_title.png" // Game title
#define MAINMENU_PLAYBUTTON_PATH                "../../resources/background_splash.png" // Play button
#define GAMESTATE_BACKGROUND_PATH               "../../resources/background_splash.png" // Game background
#define PLAYER_TEXTURE_PATH                     "../../resources/BODY_male.png" // Player texture
#define BODY_MALE_TEXTURE_PATH                  "../../resources/BODY_male.png" // Alternative player texture

// Animation frame time (in seconds)
#define ANIMATION_FRAME_TIME_IDLE               0.2f // Idle
#define ANIMATION_FRAME_TIME_WALK               0.1f // Walking
#define ANIMATION_FRAME_TIME_JUMP               0.15f // Jump
#define ANIMATION_FRAME_TIME_DASH               0.05f // Dash

// Player movement constants
#define PLAYER_MAX_SPEED                        200.0f // Maximum speed
#define PLAYER_ACCELERATION                     800.0f // Acceleration
#define PLAYER_DECELERATION                    1000.0f // Deceleration
#define PLAYER_JUMP_FORCE                       400.0f // Jump force
#define PLAYER_GRAVITY                          1200.0f // Gravity
#define PLAYER_DASH_FORCE                       500.0f // Dash force
#define PLAYER_DASH_DURATION                    0.2f // Dash duration
#define PLAYER_DASH_COOLDOWN                    0.5f // Dash cooldown

// Tile map constants
#define TILE_SIZE                               32 // Tile size (px)
#define MAP_WIDTH                               50 // Map width (tiles)
#define MAP_HEIGHT                              30 // Map height (tiles)

// Tile types
#define TILE_EMPTY                              -1 // Empty tile
#define TILE_SOLID                              0  // Solid tile
#define TILE_PLATFORM                           1  // Platform
#define TILE_SPIKE                              2  // Spikes
#define TILE_COLLECTIBLE                        3  // Collectible

#endif //DEFINITIONS_H
