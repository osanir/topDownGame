#include "GameEngine.h"
#include <list>
#include <fstream>
#include <vector>

enum TILES{
    WALL  = 0,
    GRASS = 1
};

class Map{
public:
    Map();
    void initMap();
    list<RectangleShape*> getSolidObjects();
    void importMap();
    void drawTile(RenderWindow &window);
    Vector2f getLayoutSize();
private:
    /* void createRandomObjects(); */
    Texture tileset_texture ;
    Sprite tileset_spr;
    vector <vector<int> > map_tiles;
    list<RectangleShape*> solidObjects;
    float pixelScale;
    Vector2f layoutSize;

};