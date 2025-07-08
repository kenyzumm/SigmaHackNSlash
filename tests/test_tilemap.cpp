#include "test_framework.h"
#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include <fstream> // Added for file operations

class TileMapTest : public TestFixture {
protected:
    std::unique_ptr<TileMap> tileMap;
    
    void SetUp() override {
        tileMap = std::make_unique<TileMap>(10, 10, 32);
    }
};

// Test tile map initialization
TEST_F(TileMapTest, Initialization) {
    ASSERT_EQ(tileMap->getWidth(), 10);
    ASSERT_EQ(tileMap->getHeight(), 10);
    ASSERT_EQ(tileMap->getTileSize(), 32);
}

// Test tile setting and getting
TEST_F(TileMapTest, TileSettingAndGetting) {
    // Set a tile
    tileMap->setTile(5, 5, TILE_SOLID, true);
    
    // Get the tile
    Tile tile = tileMap->getTile(5, 5);
    ASSERT_EQ(tile.id, TILE_SOLID);
    ASSERT_TRUE(tile.isCollidable);
}

// Test tile collision detection
TEST_F(TileMapTest, CollisionDetection) {
    // Set collidable tile
    tileMap->setTile(3, 3, TILE_SOLID, true);
    ASSERT_TRUE(tileMap->isCollidable(3, 3));
    
    // Set non-collidable tile
    tileMap->setTile(4, 4, TILE_EMPTY, false);
    ASSERT_FALSE(tileMap->isCollidable(4, 4));
}

// Test boundary conditions
TEST_F(TileMapTest, BoundaryConditions) {
    // Test negative coordinates
    ASSERT_FALSE(tileMap->isCollidable(-1, 0));
    ASSERT_FALSE(tileMap->isCollidable(0, -1));
    
    // Test coordinates beyond map size
    ASSERT_FALSE(tileMap->isCollidable(10, 5));
    ASSERT_FALSE(tileMap->isCollidable(5, 10));
    
    // Test edge coordinates
    ASSERT_FALSE(tileMap->isCollidable(9, 9)); // Should be valid
    ASSERT_FALSE(tileMap->isCollidable(0, 0)); // Should be valid
}

// Test tile map file operations
TEST_F(TileMapTest, FileOperations) {
    const std::string testFile = "test_map.txt";
    
    // Set some tiles
    tileMap->setTile(1, 1, TILE_SOLID, true);
    tileMap->setTile(2, 2, TILE_EMPTY, false);
    
    // Save to file
    ASSERT_NO_THROW(tileMap->saveToFile(testFile));
    
    // Create new tile map and load from file
    auto loadedTileMap = std::make_unique<TileMap>(10, 10, 32);
    ASSERT_NO_THROW(loadedTileMap->loadFromFile(testFile));
    
    // Verify loaded data
    ASSERT_EQ(loadedTileMap->getTile(1, 1).id, TILE_SOLID);
    ASSERT_TRUE(loadedTileMap->getTile(1, 1).isCollidable);
    ASSERT_EQ(loadedTileMap->getTile(2, 2).id, TILE_EMPTY);
    ASSERT_FALSE(loadedTileMap->getTile(2, 2).isCollidable);
    
    // Clean up test file
    std::remove(testFile.c_str());
}

// Test tile map rendering
TEST_F(TileMapTest, Rendering) {
    // Set some tiles
    tileMap->setTile(1, 1, TILE_SOLID, true);
    tileMap->setTile(2, 2, TILE_EMPTY, false);
    
    // Test that rendering doesn't crash
    // Note: This requires a valid SFML window context
    ASSERT_NO_THROW(tileMap->render(nullptr));
}

// Test different tile map sizes
TEST_F(TileMapTest, DifferentSizes) {
    auto smallTileMap = std::make_unique<TileMap>(5, 5, 16);
    ASSERT_EQ(smallTileMap->getWidth(), 5);
    ASSERT_EQ(smallTileMap->getHeight(), 5);
    ASSERT_EQ(smallTileMap->getTileSize(), 16);
    
    auto largeTileMap = std::make_unique<TileMap>(100, 100, 64);
    ASSERT_EQ(largeTileMap->getWidth(), 100);
    ASSERT_EQ(largeTileMap->getHeight(), 100);
    ASSERT_EQ(largeTileMap->getTileSize(), 64);
}

// Test tile map performance
TEST_F(TileMapTest, Performance) {
    // Test setting many tiles
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            tileMap->setTile(x, y, TILE_SOLID, true);
        }
    }
    
    // Test getting many tiles
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            ASSERT_EQ(tileMap->getTile(x, y).id, TILE_SOLID);
            ASSERT_TRUE(tileMap->getTile(x, y).isCollidable);
        }
    }
}

// Test tile map edge cases
TEST_F(TileMapTest, EdgeCases) {
    // Test setting tile at edge
    tileMap->setTile(9, 9, TILE_SOLID, true);
    ASSERT_TRUE(tileMap->isCollidable(9, 9));
    
    // Test setting tile at origin
    tileMap->setTile(0, 0, TILE_SOLID, true);
    ASSERT_TRUE(tileMap->isCollidable(0, 0));
}

// Test tile map with invalid file
TEST_F(TileMapTest, InvalidFile) {
    // Test loading from non-existent file
    ASSERT_NO_THROW(tileMap->loadFromFile("non_existent_file.txt"));
    
    // Map should remain unchanged
    ASSERT_FALSE(tileMap->isCollidable(0, 0));
}

// Test tile map memory usage
TEST_F(TileMapTest, MemoryUsage) {
    // Test that large tile maps can be created
    auto largeTileMap = std::make_unique<TileMap>(1000, 1000, 32);
    ASSERT_EQ(largeTileMap->getWidth(), 1000);
    ASSERT_EQ(largeTileMap->getHeight(), 1000);
    
    // Test setting tiles in large map
    largeTileMap->setTile(500, 500, TILE_SOLID, true);
    ASSERT_TRUE(largeTileMap->isCollidable(500, 500));
} 