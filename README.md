# SigmaHackNSlash

## Project Description

**SigmaHackNSlash** is a 2D hack-and-slash game written in C++ using the SFML library. The game uses a state-based architecture (State Pattern) and includes resource management systems, tile maps, and advanced player movement mechanics with double jump and dash abilities.

## Features

### 🎮 Game Mechanics
- **State System**: Management of different game screens (Splash, Main Menu, Game)
- **Advanced Player Movement**: 
  - Walking with acceleration and deceleration
  - **Double Jump**: Jump twice while in the air
  - **Dash**: Quick movement with 1.5s cooldown (ground only)
  - Gravity and physics-based movement
- **Tile Map**: Tile-based map system with 32x32 pixel tiles and collision detection
- **Animations**: Animation system for different player states (idle, run, jump, fall)
- **Collision System**: Precise collision detection with tile-based environment

### 🛠️ Technical Systems
- **Resource Management**: Central system for loading textures and sounds
- **Input Management**: Keyboard and mouse handling with key press detection
- **Logging**: File-based logging system with different log levels
- **Rendering**: Rendering with constant 60 FPS
- **Physics Engine**: Custom physics system with velocity, acceleration, and friction

## System Requirements

### Minimum Requirements
- **Operating System**: Linux, Windows, macOS
- **Compiler**: GCC 7+, Clang 6+, MSVC 2019+
- **CMake**: Version 3.16 or newer
- **SFML**: Version 3.0 or newer

### Dependencies
- **SFML 3.0** with components:
  - Graphics
  - Window  
  - System

## Installation and Compilation

### 1. Clone Repository
```bash
git clone <repository-url>
cd SigmaHackNSlash
```

### 2. Install SFML

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install libsfml-dev
```

#### Arch Linux:
```bash
sudo pacman -S sfml
```

#### Windows (vcpkg):
```bash
vcpkg install sfml
```

### 3. Build Project
```bash
# Create build directory
mkdir build
cd build

# Configure CMake
cmake ..

# Compile
make -j$(nproc)

# Alternatively for Windows with Visual Studio:
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

### 4. Run the Game
```bash
# From build directory
./bin/SigmaHackNSlash

# Or from root directory
./build/bin/SigmaHackNSlash
```

## Project Structure

```
SigmaHackNSlash/
├── CMakeLists.txt          # Main CMake configuration file
├── include/                # Header files
│   ├── Animation.h         # Animation system
│   ├── AssetsManager.h     # Resource management
│   ├── Collision.h         # Collision detection
│   ├── DEFINITIONS.h       # Constants and definitions
│   ├── Game.h             # Main game class
│   ├── GameState.h        # Game state
│   ├── InputManager.h     # Input management
│   ├── Logger.h           # Logging system
│   ├── MainMenuState.h    # Main menu state
│   ├── Movement.h         # Player movement physics
│   ├── Player.h           # Player class
│   ├── SplashState.h      # Splash screen state
│   ├── State.h            # Base state class
│   ├── StateMachine.h     # State machine
│   └── TileMap.h          # Tile map system
├── src/                   # Source files
│   ├── CMakeLists.txt     # CMake for src directory
│   ├── Animation.cpp      # Animation implementation
│   ├── AssetsManager.cpp
│   ├── Collision.cpp      # Collision detection
│   ├── Game.cpp
│   ├── GameState.cpp
│   ├── InputManager.cpp
│   ├── Logger.cpp
│   ├── main.cpp           # Entry point
│   ├── MainMenuState.cpp
│   ├── Movement.cpp       # Movement physics
│   ├── Player.cpp         # Player implementation
│   ├── SplashState.cpp
│   ├── StateMachine.cpp
│   └── TileMap.cpp        # Tile map system
└── resources/             # Game resources
    ├── background_splash.png
    ├── BODY_male.png
    ├── player.png
    └── splash_title.png
```

## Architecture

### Design Pattern: State Pattern
The game uses the State Pattern to manage different screens:

- **SplashState**: Welcome screen with logo
- **MainMenuState**: Main menu with options
- **GameState**: Main game state with player and tile map

### Key Classes

#### Game
Main game class responsible for:
- SFML window initialization
- Game loop (60 FPS)
- Game data management

#### Player
Player character with advanced movement:
- **Movement System**: Physics-based movement with velocity and acceleration
- **Double Jump**: Can jump twice while in the air
- **Dash**: Quick movement with cooldown system
- **Animation**: Different animations for idle, run, jump, and fall states
- **Collision**: Precise collision detection with tile map

#### Movement
Physics engine for player movement:
- **Velocity-based movement** with acceleration and friction
- **Gravity system** for realistic falling
- **Jump mechanics** with customizable jump force
- **Double jump system** with state tracking
- **Dash system** with cooldown and duration

#### StateMachine
Manages transitions between game states:
- Adding/removing states
- Switching between states
- Background state handling

#### AssetsManager
Central resource management system:
- Texture loading
- Resource caching
- Memory management

#### InputManager
User input handling:
- Keyboard input with key press detection
- Mouse input
- Key mapping

#### TileMap
Tile-based map system:
- **Collision detection** with solid tiles
- **Tile rendering** with different tile types
- **Map loading/saving** from files
- **Dynamic tile modification**

## Configuration

### Game Constants (DEFINITIONS.h)
```cpp
// Player movement
#define PLAYER_MAX_SPEED        300.0f
#define PLAYER_ACCELERATION     1000.0f
#define PLAYER_JUMP_FORCE       400.0f
#define PLAYER_DOUBLE_JUMP_FORCE 350.0f
#define PLAYER_GRAVITY          980.0f
#define PLAYER_DASH_SPEED       700.0f
#define PLAYER_DASH_DURATION    0.18f
#define PLAYER_DASH_COOLDOWN    1.5f

// Map
#define TILE_SIZE               32
#define MAP_WIDTH               100
#define MAP_HEIGHT              100
```

### Resource Paths
```cpp
#define SPLASHSTATE_BACKGROUND_PATH     "../../resources/background_splash.png"
#define GAMESTATE_BACKGROUND_PATH       "../../resources/background_splash.png"
#define PLAYER_TEXTURE_PATH             "../../resources/player.png"
#define BODY_MALE_TEXTURE_PATH          "../../resources/BODY_male.png"
```

## Controls

### Movement Controls
- **A/D** or **Left/Right Arrow Keys**: Move left/right
- **Space**: Jump (first jump when on ground, double jump when in air)
- **Left Shift**: Dash (quick movement in current direction, 1.5s cooldown)

### Game Controls
- **Backspace**: Close game
- **ESC**: Return to menu (if implemented)

### Movement Mechanics

#### Double Jump
- **First Jump**: Press Space while on the ground
- **Double Jump**: Press Space again while in the air
- **Reset**: Double jump resets when you land on the ground

#### Dash
- **Activation**: Press Left Shift while moving left or right
- **Requirements**: Must be on the ground and moving
- **Cooldown**: 1.5 seconds between dashes
- **Duration**: 0.18 seconds of dash movement
- **Speed**: 700 pixels per second during dash

## Development

### Adding New States
1. Create a new class inheriting from `State`
2. Implement required virtual methods (`init()`, `handleInput()`, `update()`, `render()`)
3. Add state to `StateMachine`

### Adding New Movement Abilities
1. Add variables to `Movement` class
2. Implement logic in `Movement::update()`
3. Add input handling in `Player::handleInput()`
4. Update animations if needed

### Adding New Resources
1. Place file in `resources/` directory
2. Add path in `DEFINITIONS.h`
3. Load resource in `AssetsManager`

### Debugging
The game includes a comprehensive logging system:
- **Log Levels**: DEBUG, INFO, WARNING, ERROR, CRITICAL
- **File Output**: Logs are saved to files for debugging
- **Console Output**: Important events are printed to console

## Future Enhancements

### Planned Features
- **Combat System**: Attack mechanics and enemy AI
- **Sound System**: Background music and sound effects
- **Particle Effects**: Visual effects for dash and jumps
- **Level System**: Multiple levels and progression
- **Save System**: Game progress saving and loading

### Technical Improvements
- **Performance Optimization**: Better rendering and collision detection
- **Mobile Support**: Touch controls and mobile platforms
- **Multiplayer**: Local and online multiplayer support
