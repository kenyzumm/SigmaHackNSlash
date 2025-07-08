# 🧪 **Test Suite Documentation**

## **Overview**
This test suite provides comprehensive testing for the SigmaHackNSlash game engine using a custom, lightweight test framework without external dependencies.

## **Test Framework**

### **Custom Test Framework**
- **No external dependencies** - Built-in framework using only standard C++
- **Simple and lightweight** - Easy to understand and maintain
- **Rich output** - Colored console output with timing information
- **Test fixtures** - Support for setup/teardown functionality
- **Comprehensive assertions** - All common assertion types included

### **Framework Features**
- ✅ Test suites and test cases
- ✅ Setup and teardown methods
- ✅ Timing measurements
- ✅ Detailed error reporting
- ✅ Colored console output
- ✅ Exit codes for CI/CD integration

## **Test Structure**

### **Unit Tests**
- **`test_movement.cpp`** - Tests for the Movement class
  - Basic initialization and state management
  - Horizontal movement and physics
  - Jump and double jump mechanics
  - Dash mechanics and cooldowns
  - Velocity limits and boundary conditions

- **`test_player.cpp`** - Tests for the Player class
  - Player initialization and positioning
  - Movement state tracking
  - Collision detection with tile maps
  - Input handling and rendering
  - Performance under load

- **`test_tilemap.cpp`** - Tests for the TileMap class
  - Tile setting and retrieval
  - Collision detection
  - File I/O operations
  - Boundary condition handling
  - Memory usage with large maps

- **`test_input_manager.cpp`** - Tests for the InputManager class
  - Key press detection
  - Mouse input handling
  - Sprite click detection
  - Performance and thread safety

- **`test_assets_manager.cpp`** - Tests for the AssetsManager class
  - Texture and font loading
  - Resource caching
  - Error handling for missing assets

- **`test_animation.cpp`** - Tests for the Animation class
  - Animation state management
  - Frame data handling
  - Sprite updates

- **`test_collision.cpp`** - Tests for the Collision class
  - Collision detection algorithms
  - Position and size management
  - Edge case handling

### **Integration Tests**
- **`integration_tests.cpp`** - System integration tests
  - Player-TileMap collision interactions
  - Double jump mechanics with obstacles
  - Dash mechanics with collision detection
  - Multiple player interactions
  - Game state transitions

### **Performance Tests**
- **`performance_tests.cpp`** - Performance benchmarks
  - Movement system performance
  - Tile map collision performance
  - Player update performance
  - Memory usage analysis

## **Running Tests**

### **Prerequisites**
```bash
# No external dependencies required!
# Only SFML is needed for the game itself
```

### **Building Tests**
```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DENABLE_TESTS=ON

# Build tests
make UnitTests
```

### **Running Tests**
```bash
# Run all tests
./UnitTests

# Run specific test suites (framework supports filtering)
./UnitTests

# Run with verbose output (built-in)
./UnitTests
```

## **Test Framework Usage**

### **Writing Tests**
```cpp
#include "test_framework.h"

// Simple test
TEST(MovementTest, BasicMovement) {
    Movement movement;
    movement.update(1.0f, 0.016f);
    ASSERT_GT(movement.getVelocityX(), 0.0f);
}

// Test with fixture
class PlayerTest : public TestFixture {
protected:
    Player player;
    
    void SetUp() override {
        player.init();
    }
};

TEST_F(PlayerTest, Initialization) {
    ASSERT_FLOAT_EQ(player.getX(), 100.0f);
    ASSERT_FLOAT_EQ(player.getY(), 200.0f);
}
```

### **Available Assertions**
```cpp
ASSERT_TRUE(condition)           // Assert condition is true
ASSERT_FALSE(condition)          // Assert condition is false
ASSERT_EQ(expected, actual)      // Assert equality
ASSERT_FLOAT_EQ(expected, actual) // Assert float equality with tolerance
ASSERT_GT(value1, value2)        // Assert greater than
ASSERT_LT(value1, value2)        // Assert less than
ASSERT_LE(value1, value2)        // Assert less than or equal
ASSERT_GE(value1, value2)        // Assert greater than or equal
ASSERT_NO_THROW(expression)      // Assert no exception thrown
ASSERT_THROW(expression, type)   // Assert specific exception thrown
```

## **Test Categories**

### **🧪 Unit Tests**
Test individual components in isolation:
- **Movement System**: Physics, jumping, dashing
- **Player Logic**: State management, collision
- **Tile Map**: Data structures, collision detection
- **Input Handling**: Key detection, mouse input
- **Asset Management**: Resource loading, caching

### **🔗 Integration Tests**
Test component interactions:
- **Player-TileMap**: Collision detection and response
- **Movement-Collision**: Physics with obstacles
- **Multi-Player**: Multiple entity interactions
- **State Transitions**: Game state changes

### **⚡ Performance Tests**
Benchmark critical systems:
- **Movement Performance**: 100k+ movement updates
- **Collision Performance**: Large tile map collision checks
- **Player Updates**: High-frequency player updates
- **Memory Usage**: Large map creation and access

## **Test Coverage**

### **Core Systems**
- ✅ Movement physics and mechanics
- ✅ Player state management
- ✅ Tile map collision detection
- ✅ Input handling and processing
- ✅ Asset loading and management
- ✅ Animation system
- ✅ Collision detection algorithms

### **Edge Cases**
- ✅ Boundary conditions
- ✅ Invalid input handling
- ✅ Memory management
- ✅ Performance under load
- ✅ Error conditions

### **Integration Scenarios**
- ✅ Player movement with obstacles
- ✅ Multiple mechanics interaction
- ✅ Large map performance
- ✅ State transition handling

## **Continuous Integration**

### **GitHub Actions**
```yaml
name: Tests
on: [push, pull_request]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install dependencies
        run: sudo apt-get install -y libsfml-dev cmake build-essential
      - name: Build and test
        run: |
          mkdir build && cd build
          cmake .. -DENABLE_TESTS=ON
          make
          ./UnitTests
```

## **Test Maintenance**

### **Best Practices**
1. **Keep tests focused**: Each test should verify one specific behavior
2. **Use descriptive names**: Test names should clearly describe what they test
3. **Arrange-Act-Assert**: Structure tests with clear sections
4. **Test edge cases**: Include boundary conditions and error scenarios
5. **Maintain test data**: Keep test resources organized and documented

### **Debugging Tests**
```bash
# Run with debug output
./UnitTests

# Check exit code for CI
echo $?  # 0 = all tests passed, >0 = number of failed tests
```

## **Performance Benchmarks**

### **Expected Performance**
- **Movement Updates**: < 1ms for 100k operations
- **Collision Checks**: < 5s for 10M checks
- **Player Updates**: < 2s for 10k updates
- **Memory Usage**: < 100MB for large maps

### **Monitoring Performance**
```bash
# Run performance tests
./UnitTests

# Framework automatically reports timing for each test
```

## **Advantages of Custom Framework**

### **Benefits**
1. **No Dependencies**: No external libraries required
2. **Lightweight**: Minimal overhead and fast compilation
3. **Customizable**: Easy to extend and modify
4. **Portable**: Works on any platform with C++17
5. **Integrated**: Seamlessly integrated with the project

### **Features**
- **Automatic test registration** via macros
- **Test fixtures** with setup/teardown
- **Timing measurements** for performance tracking
- **Colored output** for better readability
- **Exit codes** for CI/CD integration
- **Exception handling** for robust error reporting

This custom test framework provides all the functionality needed for comprehensive testing without the overhead of external dependencies. 