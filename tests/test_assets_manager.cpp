#include "test_framework.h"
#include "AssetsManager.h"
#include "DEFINITIONS.h"

class AssetsManagerTest : public TestFixture {
protected:
    AssetsManager assetsManager;
    
    void SetUp() override {
        // assetsManager = AssetsManager(); // Removed: causes copy assignment error
    }
};

// Test assets manager initialization
TEST_F(AssetsManagerTest, Initialization) {
    ASSERT_NO_THROW(AssetsManager());
}

// Test texture loading
TEST_F(AssetsManagerTest, TextureLoading) {
    // Test loading valid texture
    ASSERT_NO_THROW(assetsManager.loadTexture("test", PLAYER_TEXTURE_PATH));
    
    // Test getting loaded texture
    ASSERT_NO_THROW(assetsManager.getTexture("test"));
}

// Test font loading
TEST_F(AssetsManagerTest, FontLoading) {
    // Test that font loading doesn't crash
    // Note: Would need actual font file for full test
    ASSERT_NO_THROW(assetsManager.loadFont("test", "non_existent_font.ttf"));
}

// Test invalid texture access
TEST_F(AssetsManagerTest, InvalidTextureAccess) {
    // Test getting non-existent texture
    ASSERT_THROW(assetsManager.getTexture("non_existent"), std::exception);
}

// Test multiple texture loading
TEST_F(AssetsManagerTest, MultipleTextureLoading) {
    ASSERT_NO_THROW(assetsManager.loadTexture("texture1", PLAYER_TEXTURE_PATH));
    ASSERT_NO_THROW(assetsManager.loadTexture("texture2", PLAYER_TEXTURE_PATH));
    
    ASSERT_NO_THROW(assetsManager.getTexture("texture1"));
    ASSERT_NO_THROW(assetsManager.getTexture("texture2"));
}

// Test texture caching
TEST_F(AssetsManagerTest, TextureCaching) {
    // Load same texture twice
    assetsManager.loadTexture("cached", PLAYER_TEXTURE_PATH);
    assetsManager.loadTexture("cached", PLAYER_TEXTURE_PATH);
    
    // Should not crash
    ASSERT_NO_THROW(assetsManager.getTexture("cached"));
} 