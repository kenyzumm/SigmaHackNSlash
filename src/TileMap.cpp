#include "TileMap.h"
#include "DEFINITIONS.h"
#include <fstream>
#include <iostream>

TileMap::TileMap() : vertices(sf::PrimitiveType::Triangles), tileSize(TILE_SIZE, TILE_SIZE), mapSize(MAP_WIDTH, MAP_HEIGHT) {
    // Initialize tiles with empty
    tiles.resize(mapSize.y, std::vector<int>(mapSize.x, TILE_EMPTY));
}

TileMap::~TileMap() {
}

bool TileMap::load(const std::string& tilesetPath, sf::Vector2u tileSize, const std::vector<std::vector<int>>& tiles, sf::Vector2u mapSize) {
    this->tileSize = tileSize;
    this->mapSize = mapSize;
    this->tiles = tiles;
    
    // Load the tileset texture
    if (!texture.loadFromFile(tilesetPath)) {
        std::cerr << "Failed to load tileset: " << tilesetPath << std::endl;
        return false;
    }
    
    // Resize the vertex array to fit the level size
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(mapSize.x * mapSize.y * 6);
    
    // Populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < mapSize.x; ++i) {
        for (unsigned int j = 0; j < mapSize.y; ++j) {
            int tileNumber = tiles[j][i];
            if (tileNumber == TILE_EMPTY) continue;
            int tu = tileNumber % (texture.getSize().x / tileSize.x);
            int tv = tileNumber / (texture.getSize().x / tileSize.x);
            sf::Vertex* tri = &vertices[(i + j * mapSize.x) * 6];
            // First triangle
            tri[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            tri[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            tri[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            // Second triangle
            tri[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            tri[4].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            tri[5].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            // Texture coordinates
            tri[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            tri[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            tri[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            tri[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            tri[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            tri[5].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    updateCollisionRects();
    return true;
}

bool TileMap::loadFromFile(const std::string& mapPath, const std::string& tilesetPath) {
    std::ifstream file(mapPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << mapPath << std::endl;
        return false;
    }
    
    // Read map dimensions
    file >> mapSize.x >> mapSize.y;
    
    // Resize tiles vector
    tiles.resize(mapSize.y, std::vector<int>(mapSize.x));
    
    // Read tile data
    for (unsigned int y = 0; y < mapSize.y; ++y) {
        for (unsigned int x = 0; x < mapSize.x; ++x) {
            file >> tiles[y][x];
        }
    }
    
    file.close();
    
    return load(tilesetPath, tileSize, tiles, mapSize);
}

void TileMap::setTileSize(sf::Vector2u size) {
    tileSize = size;
}

void TileMap::setMapSize(sf::Vector2u size) {
    mapSize = size;
    tiles.resize(mapSize.y, std::vector<int>(mapSize.x, TILE_EMPTY));
}

void TileMap::setTile(int x, int y, int tileIndex) {
    if (x >= 0 && x < static_cast<int>(mapSize.x) && y >= 0 && y < static_cast<int>(mapSize.y)) {
        tiles[y][x] = tileIndex;
        updateVertices();
        updateCollisionRects();
    }
}

int TileMap::getTile(int x, int y) const {
    if (x >= 0 && x < static_cast<int>(mapSize.x) && y >= 0 && y < static_cast<int>(mapSize.y)) {
        return tiles[y][x];
    }
    return TILE_EMPTY;
}

void TileMap::clearTile(int x, int y) {
    setTile(x, y, TILE_EMPTY);
}

std::vector<sf::FloatRect> TileMap::getCollisionRects() const {
    return collisionRects;
}

sf::FloatRect TileMap::getTileBounds(int x, int y) const {
    if (x >= 0 && x < static_cast<int>(mapSize.x) && y >= 0 && y < static_cast<int>(mapSize.y)) {
        return sf::FloatRect(sf::Vector2f(x * tileSize.x, y * tileSize.y), sf::Vector2f(tileSize.x, tileSize.y));
    }
    return sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
}

bool TileMap::isSolid(int x, int y) const {
    int tile = getTile(x, y);
    return tile == TILE_SOLID || tile == TILE_SPIKE;
}

bool TileMap::isPlatform(int x, int y) const {
    return getTile(x, y) == TILE_PLATFORM;
}

bool TileMap::isSpike(int x, int y) const {
    return getTile(x, y) == TILE_SPIKE;
}

sf::Vector2i TileMap::worldToTile(const sf::Vector2f& worldPos) const {
    return sf::Vector2i(static_cast<int>(worldPos.x / tileSize.x), 
                       static_cast<int>(worldPos.y / tileSize.y));
}

sf::Vector2f TileMap::tileToWorld(const sf::Vector2i& tilePos) const {
    return sf::Vector2f(tilePos.x * tileSize.x, tilePos.y * tileSize.y);
}

sf::Vector2u TileMap::getTileSize() const {
    return tileSize;
}

sf::Vector2u TileMap::getMapSize() const {
    return mapSize;
}

sf::Vector2f TileMap::getMapPixelSize() const {
    return sf::Vector2f(mapSize.x * tileSize.x, mapSize.y * tileSize.y);
}

void TileMap::updateCollisionRects() {
    collisionRects.clear();
    
    for (unsigned int y = 0; y < mapSize.y; ++y) {
        for (unsigned int x = 0; x < mapSize.x; ++x) {
            int tile = tiles[y][x];
            if (tile == TILE_SOLID || tile == TILE_PLATFORM || tile == TILE_SPIKE) {
                collisionRects.push_back(getTileBounds(x, y));
            }
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply the transform
    states.transform *= getTransform();
    
    // Apply the tileset texture
    states.texture = &texture;
    
    // Draw the vertex array
    target.draw(vertices, states);
}

void TileMap::updateVertices() {
    vertices.clear();
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertices.resize(mapSize.x * mapSize.y * 6);
    for (unsigned int i = 0; i < mapSize.x; ++i) {
        for (unsigned int j = 0; j < mapSize.y; ++j) {
            int tileNumber = tiles[j][i];
            if (tileNumber == TILE_EMPTY) continue;
            int tu = tileNumber % (texture.getSize().x / tileSize.x);
            int tv = tileNumber / (texture.getSize().x / tileSize.x);
            sf::Vertex* tri = &vertices[(i + j * mapSize.x) * 6];
            tri[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            tri[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            tri[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            tri[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            tri[4].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            tri[5].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            tri[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            tri[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            tri[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            tri[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            tri[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            tri[5].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
} 