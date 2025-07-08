#include "TileMap.h"
#include <fstream>

TileMap::TileMap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize), layers(1) {
    tiles.resize(height, std::vector<Tile>(width, {0, false}));
}

TileMap::~TileMap() {}

void TileMap::setTile(int x, int y, int tileID, bool collidable) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x].id = tileID;
        tiles[y][x].isCollidable = collidable;
    }
}

Tile TileMap::getTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y][x];
    }
    return {0, false};
}

bool TileMap::isCollidable(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y][x].isCollidable;
    }
    return false;
}

void TileMap::loadFromFile(const std::string& filename) {
    // Szkic: wczytaj mapę z pliku tekstowego
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

void TileMap::saveToFile(const std::string& filename) const {
    // Szkic: zapisz mapę do pliku tekstowego
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

void TileMap::render() {
    // Tu powinno być rysowanie mapy
}

void TileMap::update(float dt) {
    // Tu można dodać logikę aktualizacji mapy
}

int TileMap::getWidth() const { return width; }
int TileMap::getHeight() const { return height; }
int TileMap::getTileSize() const { return tileSize; }