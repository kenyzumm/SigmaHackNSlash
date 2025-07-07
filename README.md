# SigmaHackNSlash

## Project Description

**SigmaHackNSlash** is a 2D hack-and-slash game written in C++ using the SFML library. The game uses a state-based architecture (State Pattern) and includes resource management systems, tile maps, and advanced player movement mechanics.

## Features

### 🎮 Game Mechanics
- **State System**: Management of different game screens (Splash, Main Menu, Game)
- **Player Movement**: 
  - Walking with acceleration and deceleration
  - Jumping with gravity
  - Dash (quick movement) with cooldown
- **Tile Map**: Tile-based map system with 32x32 pixel tiles
- **Animations**: Animation system for different player states (idle, walk, jump, dash)

### 🛠️ Technical Systems
- **Resource Management**: Central system for loading textures and sounds
- **Input Management**: Keyboard and mouse handling
- **Logging**: File-based logging system
- **Rendering**: Rendering with constant 60 FPS

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
│   ├── AssetsManager.h     # Resource management
│   ├── DEFINITIONS.h       # Constants and definitions
│   ├── Game.h             # Main game class
│   ├── GameState.h        # Game state
│   ├── InputManager.h     # Input management
│   ├── Logger.h           # Logging system
│   ├── MainMenuState.h    # Main menu state
│   ├── SplashState.h      # Splash screen state
│   ├── State.h            # Base state class
│   └── StateMachine.h     # State machine
├── src/                   # Source files
│   ├── CMakeLists.txt     # CMake for src directory
│   ├── AssetsManager.cpp
│   ├── Game.cpp
│   ├── GameState.cpp
│   ├── InputManager.cpp
│   ├── Logger.cpp
│   ├── main.cpp           # Entry point
│   ├── MainMenuState.cpp
│   ├── SplashState.cpp
│   ├── StateMachine.cpp
│   └── TileMap.cpp        # Tile map system
└── resources/             # Game resources
    ├── background_splash.png
    ├── BODY_male.png
    └── player.png
```

## Architecture

### Design Pattern: State Pattern
The game uses the State Pattern to manage different screens:

- **SplashState**: Welcome screen with logo
- **MainMenuState**: Main menu with options
- **GameState**: Main game state

### Key Classes

#### Game
Main game class responsible for:
- SFML window initialization
- Game loop (60 FPS)
- Game data management

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
- Keyboard
- Mouse
- Key mapping

## Configuration

### Game Constants (DEFINITIONS.h)
```cpp
// Player movement
#define PLAYER_MAX_SPEED        200.0f
#define PLAYER_ACCELERATION     800.0f
#define PLAYER_JUMP_FORCE       400.0f
#define PLAYER_GRAVITY          1200.0f

// Map
#define TILE_SIZE               32
#define MAP_WIDTH               50
#define MAP_HEIGHT              30
```

### Resource Paths
```cpp
#define SPLASHSTATE_BACKGROUND_PATH     "../../resources/background_splash.png"
#define PLAYER_TEXTURE_PATH             "../../resources/player.png"
#define BODY_MALE_TEXTURE_PATH          "../../resources/BODY_male.png"
```

## Controls

### Basic Controls
- **WASD** or **Arrow Keys**: Player movement
- **Space**: Jump
- **Shift**: Dash (quick movement)
- **ESC**: Return to menu

## Development

### Adding New States
1. Create a new class inheriting from `State`
2. Implement required virtual methods
3. Add state to `StateMachine`

### Adding New Resources
1. Place file in `resources/` directory
2. Add path in `DEFINITIONS.h`
3. Load resource in `AssetsManager`

## Debugging

### Logging
The game automatically logs information to `log.txt`:
- Resource loading errors
- Game state information
- Input debugging

### Build Flags
```bash
# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Release build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

## License

[Add license information here]

## Authors

[Add author information here]

## Contact

[Add contact information here]

---

**Note**: The project is in development. Some features may be incomplete or change in future versions.
