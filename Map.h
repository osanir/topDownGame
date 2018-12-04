#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;

class Map{
public:
    Map();
    list<RectangleShape*> getSolidObjets();
private:
    void createRandomObjects();
    list<RectangleShape*> solidObjects;

};