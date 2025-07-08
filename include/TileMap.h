#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp> // Added for sf::RenderWindow

// Struktura pojedynczego kafelka mapy
struct Tile {
    int id;           // Identyfikator typu kafelka
    bool isCollidable;// Czy kafelek jest kolizyjny
};

// Klasa obsługująca mapę kafelkową i kolizje z kafelkami
class TileMap {
    int width, height;           // Liczba kafelków w poziomie i pionie
    int tileSize;                // Rozmiar pojedynczego kafelka (np. 32x32 px)
    std::vector<std::vector<Tile>> tiles; // Dwuwymiarowa tablica przechowująca ID i kolizje kafelków

public:
    // Tworzy mapę o zadanych wymiarach i rozmiarze kafelka
    TileMap(int width, int height, int tileSize);
    ~TileMap();

    // Ustawia typ i kolizyjność kafelka na pozycji (x, y)
    void setTile(int x, int y, int tileID, bool collidable = false);
    // Zwraca kafelek na pozycji (x, y)
    Tile getTile(int x, int y) const;
    // Sprawdza czy kafelek na pozycji (x, y) jest kolizyjny
    bool isCollidable(int x, int y) const;

    // Wczytuje mapę z pliku tekstowego
    void loadFromFile(const std::string& filename);
    // Zapisuje mapę do pliku tekstowego
    void saveToFile(const std::string& filename) const;

    // Renderuje mapę na ekranie
    void render(sf::RenderWindow* window);

    // Zwraca szerokość mapy (w kafelkach)
    int getWidth() const;
    // Zwraca wysokość mapy (w kafelkach)
    int getHeight() const;
    // Zwraca rozmiar pojedynczego kafelka
    int getTileSize() const;
};

#endif