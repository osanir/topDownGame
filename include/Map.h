#include "GameEngine.h"
#include <list>
#include <fstream>
#include <vector>

class Map{
public:
    Map();
    void initMap();
    list<RectangleShape*> getSolidObjets();
    void readMap();
    void drawTile(RenderWindow &window);
private:
    /* void createRandomObjects(); */
    Texture tileset_texture ;
    Sprite tileset_spr;
    vector <vector<int> > map_tiles;
    list<RectangleShape*> solidObjects;

};