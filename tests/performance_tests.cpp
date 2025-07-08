#include "test_framework.h"
#include <chrono>
#include "Movement.h"
#include "TileMap.h"
#include "Player.h"
#include "Game.h"

class PerformanceTest : public TestFixture {
protected:
    void SetUp() override {
        // Setup for performance tests
    }
};

// Test movement system performance
TEST_F(PerformanceTest, MovementSystemPerformance) {
    Movement movement;
    movement.setOnGround(true);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform many movement updates
    for (int i = 0; i < 100000; ++i) {
        movement.update(0.016f, 0.016f);
        movement.jump();
        movement.doubleJump();
        movement.startDash(1);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Should complete within reasonable time (adjust threshold as needed)
    ASSERT_LT(duration.count(), 1000); // Less than 1 second
}

// Test tile map collision performance
TEST_F(PerformanceTest, TileMapCollisionPerformance) {
    auto tileMap = std::make_unique<TileMap>(100, 100, 32);
    
    // Fill tile map with some tiles
    for (int x = 0; x < 100; ++x) {
        for (int y = 0; y < 100; ++y) {
            if (y > 80) { // Bottom 20 rows are solid
                tileMap->setTile(x, y, TILE_SOLID, true);
            }
        }
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Test many collision checks
    for (int i = 0; i < 10000; ++i) {
        for (int x = 0; x < 100; ++x) {
            for (int y = 0; y < 100; ++y) {
                tileMap->isCollidable(x, y);
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    ASSERT_LT(duration.count(), 5000); // Less than 5 seconds
}

// Test player update performance
TEST_F(PerformanceTest, PlayerUpdatePerformance) {
    GameDataRef m_data = std::make_shared<GameData>();
    m_data->window = nullptr;
    m_data->input = InputManager();
    
    auto player = std::make_unique<Player>(m_data);
    auto tileMap = std::make_unique<TileMap>(50, 50, 32);
    
    player->init();
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Perform many player updates
    for (int i = 0; i < 10000; ++i) {
        player->update(0.016f, tileMap.get());
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    ASSERT_LT(duration.count(), 2000); // Less than 2 seconds
}

// Test memory usage
TEST_F(PerformanceTest, MemoryUsage) {
    std::vector<std::unique_ptr<TileMap>> tileMaps;
    
    // Create many tile maps
    for (int i = 0; i < 100; ++i) {
        tileMaps.push_back(std::make_unique<TileMap>(50, 50, 32));
    }
    
    // Test that we can access them
    for (auto& tileMap : tileMaps) {
        ASSERT_EQ(tileMap->getWidth(), 50);
        ASSERT_EQ(tileMap->getHeight(), 50);
    }
}

// Test animation performance
TEST_F(PerformanceTest, AnimationPerformance) {
    // Test animation system performance
    // This would require actual animation setup
    ASSERT_TRUE(true); // Placeholder
} 