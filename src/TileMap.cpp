#include "TileMap.h"
#include <fstream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "DEFINITIONS.h"

TileMap::TileMap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize), layers(1) {
    tiles.resize(height, std::vector<Tile>(width, {TILE_EMPTY, false}));
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
    // Rysuj tylko kafelki różne od TILE_EMPTY
    sf::RenderWindow* window = nullptr;
    // Spróbuj znaleźć okno globalnie (przykładowo przez singleton lub przekazać przez parametr w przyszłości)
    // Tu uproszczone założenie:
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

void TileMap::update(float dt) {
    // Tu można dodać logikę aktualizacji mapy
}

int TileMap::getWidth() const { return width; }
int TileMap::getHeight() const { return height; }
int TileMap::getTileSize() const { return tileSize; }