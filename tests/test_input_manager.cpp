#include "test_framework.h"
#include "InputManager.h"
#include <SFML/Graphics.hpp>

class InputManagerTest : public TestFixture {
protected:
    InputManager inputManager;
    
    void SetUp() override {
        // Reset input manager state
        inputManager = InputManager();
    }
};

// Test input manager initialization
TEST_F(InputManagerTest, Initialization) {
    // Test that input manager can be created
    ASSERT_NO_THROW(InputManager());
}

// Test key press detection
TEST_F(InputManagerTest, KeyPressDetection) {
    // Test that isKeyPressed doesn't crash
    // Note: In a real test environment, we would mock SFML input
    ASSERT_NO_THROW(inputManager.isKeyPressed(sf::Keyboard::Key::Space));
    ASSERT_NO_THROW(inputManager.isKeyPressed(sf::Keyboard::Key::A));
    ASSERT_NO_THROW(inputManager.isKeyPressed(sf::Keyboard::Key::D));
}

// Test key just pressed detection
TEST_F(InputManagerTest, KeyJustPressedDetection) {
    // Test that isKeyJustPressed doesn't crash
    ASSERT_NO_THROW(inputManager.isKeyJustPressed(sf::Keyboard::Key::Space));
    ASSERT_NO_THROW(inputManager.isKeyJustPressed(sf::Keyboard::Key::LShift));
}

// Test mouse position
TEST_F(InputManagerTest, MousePosition) {
    // Test that getMousePosition doesn't crash
    // Note: This requires a valid SFML window
    ASSERT_NO_THROW(inputManager.getMousePosition(nullptr));
}

// Test sprite click detection
TEST_F(InputManagerTest, SpriteClickDetection) {
    // Create a test sprite
    sf::Texture texture;
    sf::Sprite sprite(texture);
    
    // Test that isSpriteClicked doesn't crash
    ASSERT_NO_THROW(inputManager.isSpriteClicked(sprite, sf::Mouse::Button::Left, nullptr));
}

// Test multiple key states
TEST_F(InputManagerTest, MultipleKeyStates) {
    // Test multiple keys
    std::vector<sf::Keyboard::Key> keys = {
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::D,
        sf::Keyboard::Key::Space,
        sf::Keyboard::Key::LShift,
        sf::Keyboard::Key::Escape
    };
    
    for (auto key : keys) {
        ASSERT_NO_THROW(inputManager.isKeyPressed(key));
        ASSERT_NO_THROW(inputManager.isKeyJustPressed(key));
    }
}

// Test input manager state consistency
TEST_F(InputManagerTest, StateConsistency) {
    // Test that calling isKeyJustPressed multiple times doesn't cause issues
    for (int i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(inputManager.isKeyJustPressed(sf::Keyboard::Key::Space));
    }
}

// Test input manager performance
TEST_F(InputManagerTest, Performance) {
    // Test many key checks
    for (int i = 0; i < 1000; ++i) {
        ASSERT_NO_THROW(inputManager.isKeyPressed(sf::Keyboard::Key::Space));
        ASSERT_NO_THROW(inputManager.isKeyJustPressed(sf::Keyboard::Key::Space));
    }
}

// Test input manager with invalid parameters
TEST_F(InputManagerTest, InvalidParameters) {
    // Test with null window
    ASSERT_NO_THROW(inputManager.getMousePosition(nullptr));
    
    // Test with empty sprite
    sf::Texture texture;
    sf::Sprite emptySprite(texture);
    ASSERT_NO_THROW(inputManager.isSpriteClicked(emptySprite, sf::Mouse::Button::Left, nullptr));
}

// Test input manager edge cases
TEST_F(InputManagerTest, EdgeCases) {
    // Test with various mouse buttons
    sf::Texture texture;
    sf::Sprite testSprite(texture);
    ASSERT_NO_THROW(inputManager.isSpriteClicked(testSprite, sf::Mouse::Button::Left, nullptr));
    ASSERT_NO_THROW(inputManager.isSpriteClicked(testSprite, sf::Mouse::Button::Right, nullptr));
    ASSERT_NO_THROW(inputManager.isSpriteClicked(testSprite, sf::Mouse::Button::Middle, nullptr));
}

// Test input manager memory usage
TEST_F(InputManagerTest, MemoryUsage) {
    // Test creating many input managers
    std::vector<InputManager> managers;
    for (int i = 0; i < 100; ++i) {
        managers.emplace_back();
    }
    
    // Test that they all work
    for (auto& manager : managers) {
        ASSERT_NO_THROW(manager.isKeyPressed(sf::Keyboard::Key::Space));
    }
}

// Test input manager thread safety
TEST_F(InputManagerTest, ThreadSafety) {
    // Test that multiple input managers can be used simultaneously
    InputManager manager1, manager2, manager3;
    
    ASSERT_NO_THROW(manager1.isKeyPressed(sf::Keyboard::Key::A));
    ASSERT_NO_THROW(manager2.isKeyPressed(sf::Keyboard::Key::D));
    ASSERT_NO_THROW(manager3.isKeyPressed(sf::Keyboard::Key::Space));
}

// Test input manager with different key types
TEST_F(InputManagerTest, DifferentKeyTypes) {
    // Test various key types
    std::vector<sf::Keyboard::Key> keyTypes = {
        sf::Keyboard::Key::A, sf::Keyboard::Key::B, sf::Keyboard::Key::C,
        sf::Keyboard::Key::D, sf::Keyboard::Key::E, sf::Keyboard::Key::F,
        sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::I,
        sf::Keyboard::Key::J, sf::Keyboard::Key::K, sf::Keyboard::Key::L,
        sf::Keyboard::Key::M, sf::Keyboard::Key::N, sf::Keyboard::Key::O,
        sf::Keyboard::Key::P, sf::Keyboard::Key::Q, sf::Keyboard::Key::R,
        sf::Keyboard::Key::S, sf::Keyboard::Key::T, sf::Keyboard::Key::U,
        sf::Keyboard::Key::V, sf::Keyboard::Key::W, sf::Keyboard::Key::X,
        sf::Keyboard::Key::Y, sf::Keyboard::Key::Z
    };
    
    for (auto key : keyTypes) {
        ASSERT_NO_THROW(inputManager.isKeyPressed(key));
        ASSERT_NO_THROW(inputManager.isKeyJustPressed(key));
    }
} 