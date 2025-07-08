#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define LOG_FILEPATH "../log.txt"

#define SPLASHSTATE_BACKGROUND_PATH             "../../resources/background_splash.png"
#define SPLASHSTATE_SHOWTIME 3.0f

#define MAINMENU_BACKGROUND_PATH                "../../resources/background_splash.png"
#define MAINMENU_TITLE_PATH                     "../../resources/background_splash.png"
#define MAINMENU_PLAYBUTTON_PATH                "../../resources/background_splash.png"

#define GAMESTATE_BACKGROUND_PATH               "../../resources/background_splash.png"

#define PLAYER_TEXTURE_PATH                     "../../resources/BODY_male.png"
#define BODY_MALE_TEXTURE_PATH                  "../../resources/BODY_male.png"

// Animation frame times
#define ANIMATION_FRAME_TIME_IDLE               0.2f
#define ANIMATION_FRAME_TIME_WALK               0.1f
#define ANIMATION_FRAME_TIME_JUMP               0.15f
#define ANIMATION_FRAME_TIME_DASH               0.05f

// Player movement constants
#define PLAYER_MAX_SPEED                        200.0f
#define PLAYER_ACCELERATION                     800.0f
#define PLAYER_DECELERATION                    1000.0f
#define PLAYER_JUMP_FORCE                       400.0f
#define PLAYER_GRAVITY                          1200.0f
#define PLAYER_DASH_FORCE                       500.0f
#define PLAYER_DASH_DURATION                    0.2f
#define PLAYER_DASH_COOLDOWN                    0.5f

// Tile map constants
#define TILE_SIZE                               32
#define MAP_WIDTH                               50
#define MAP_HEIGHT                              30

// Tile types
#define TILE_EMPTY                              -1
#define TILE_SOLID                              0
#define TILE_PLATFORM                           1
#define TILE_SPIKE                              2
#define TILE_COLLECTIBLE                        3

#endif //DEFINITIONS_H
