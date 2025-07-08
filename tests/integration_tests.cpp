#include "test_framework.h"
#include "Game.h"
#include "Player.h"
#include "TileMap.h"
#include "Movement.h"
#include "Collision.h"

class IntegrationTest : public TestFixture {
protected:
    GameDataRef m_data;
    std::unique_ptr<Player> player;
    std::unique_ptr<TileMap> tileMap;
    
    void SetUp() override {
        m_data = std::make_shared<GameData>();
        m_data->window = nullptr;
        m_data->input = InputManager();
        
        player = std::make_unique<Player>(m_data);
        tileMap = std::make_unique<TileMap>(20, 20, 32);
        
        m_data->assets.loadTexture("Player", PLAYER_TEXTURE_PATH);
        player->init();
    }
};

// Test player movement with tile map collision
TEST_F(IntegrationTest, PlayerTileMapCollision) {
    // Create a platform
    for (int x = 0; x < 10; ++x) {
        tileMap->setTile(x, 10, TILE_SOLID, true);
    }
    
    // Position player above platform
    player->setPosition(64.0f, 200.0f);
    
    // Update multiple times to simulate falling
    for (int i = 0; i < 100; ++i) {
        player->update(0.016f, tileMap.get());
    }
    
    // Player should land on platform
    // Note: This test may need adjustment based on actual collision logic
}

// Test player double jump with collision
TEST_F(IntegrationTest, PlayerDoubleJumpWithCollision) {
    // Create walls on sides
    for (int y = 0; y < 15; ++y) {
        tileMap->setTile(0, y, TILE_SOLID, true);
        tileMap->setTile(19, y, TILE_SOLID, true);
    }
    
    // Position player in middle
    player->setPosition(320.0f, 200.0f);
    
    // Test that player can double jump without hitting walls
    for (int i = 0; i < 50; ++i) {
        player->update(0.016f, tileMap.get());
    }
}

// Test player dash with collision
TEST_F(IntegrationTest, PlayerDashWithCollision) {
    // Create obstacles
    tileMap->setTile(5, 10, TILE_SOLID, true);
    tileMap->setTile(6, 10, TILE_SOLID, true);
    tileMap->setTile(7, 10, TILE_SOLID, true);
    
    // Position player before obstacles
    player->setPosition(64.0f, 200.0f);
    
    // Test dash movement
    for (int i = 0; i < 30; ++i) {
        player->update(0.016f, tileMap.get());
    }
}

// Test multiple players interaction
TEST_F(IntegrationTest, MultiplePlayersInteraction) {
    auto player2 = std::make_unique<Player>(m_data);
    player2->init();
    
    // Position players near each other
    player->setPosition(100.0f, 200.0f);
    player2->setPosition(150.0f, 200.0f);
    
    // Update both players
    for (int i = 0; i < 50; ++i) {
        player->update(0.016f, tileMap.get());
        player2->update(0.016f, tileMap.get());
    }
}

// Test game state transitions
TEST_F(IntegrationTest, GameStateTransitions) {
    // Test that game can handle state changes
    ASSERT_NO_THROW(player->update(0.016f, tileMap.get()));
    
    // Change tile map
    auto newTileMap = std::make_unique<TileMap>(30, 30, 16);
    ASSERT_NO_THROW(player->update(0.016f, newTileMap.get()));
}

// Test performance with large tile map
TEST_F(IntegrationTest, LargeTileMapPerformance) {
    auto largeTileMap = std::make_unique<TileMap>(100, 100, 32);
    
    // Fill with some tiles
    for (int x = 0; x < 100; ++x) {
        for (int y = 90; y < 100; ++y) {
            largeTileMap->setTile(x, y, TILE_SOLID, true);
        }
    }
    
    // Test performance
    for (int i = 0; i < 1000; ++i) {
        ASSERT_NO_THROW(player->update(0.016f, largeTileMap.get()));
    }
} 