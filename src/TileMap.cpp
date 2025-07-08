#include "TileMap.h"
#include <fstream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "DEFINITIONS.h"

// Constructor: creates a map with given dimensions and tile size
TileMap::TileMap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize) {
    tiles.resize(height, std::vector<Tile>(width, {TILE_EMPTY, false}));
}

TileMap::~TileMap() {}

// Sets the type and collidability of the tile at position (x, y)
void TileMap::setTile(int x, int y, int tileID, bool collidable) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x].id = tileID;
        tiles[y][x].isCollidable = collidable;
    }
}

// Returns the tile at position (x, y)
Tile TileMap::getTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y][x];
    }
    return {0, false};
}

// Checks if the tile at position (x, y) is collidable
bool TileMap::isCollidable(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y][x].isCollidable;
    }
    return false;
}

// Loads the map from a text file (each tile: id and collidability)
void TileMap::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int id, coll;
            file >> id >> coll;
            tiles[y][x].id = id;
            tiles[y][x].isCollidable = (coll != 0);
        }
    }
    file.close();
}

// Saves the map to a text file (each tile: id and collidability)
void TileMap::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            file << tiles[y][x].id << " " << tiles[y][x].isCollidable << " ";
        }
        file << "\n";
    }
    file.close();
}

// Renders the map: draws rectangles for each non-empty tile
void TileMap::render() {
    sf::RenderWindow* window = nullptr;
    extern sf::RenderWindow* g_window;
    window = g_window;
    if (!window) return;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (tiles[y][x].id != TILE_EMPTY) {
                sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
                rect.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
                if (tiles[y][x].id == TILE_SOLID) rect.setFillColor(sf::Color::Red);
                else rect.setFillColor(sf::Color(200, 200, 200));
                window->draw(rect);
            }
        }
    }
}

// Returns the map width (in tiles)
int TileMap::getWidth() const { return width; }
// Returns the map height (in tiles)
int TileMap::getHeight() const { return height; }
// Returns the size of a single tile
int TileMap::getTileSize() const { return tileSize; }