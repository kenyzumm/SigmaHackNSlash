#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>

struct Tile {
    int id;
    bool isCollidable;
};

class TileMap {
    int width, height;           // liczba kafelków w poziomie i pionie
    int tileSize;                // rozmiar pojedynczego kafelka (np. 32x32 px)
    std::vector<std::vector<Tile>> tiles; // dwuwymiarowa tablica przechowująca ID kafelków
    int layers;
    // Można dodać std::vector<std::vector<std::vector<Tile>>> dla wielu warstw

public:
    TileMap(int width, int height, int tileSize);
    ~TileMap();

    void setTile(int x, int y, int tileID, bool collidable = false);
    Tile getTile(int x, int y) const;
    bool isCollidable(int x, int y) const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    void render();
    void update(float dt);

    int getWidth() const;
    int getHeight() const;
    int getTileSize() const;
};

#endif