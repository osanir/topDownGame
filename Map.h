#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <fstream>
#include <vector>

using namespace sf;
using namespace std;


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