#include "Map.h"

Map::Map(){
    createRandomObjects();
}

void Map::createRandomObjects(){
    for(int i=0; i<10; i++){
        RectangleShape* shape = new RectangleShape({20,20});
        shape->setFillColor(Color::Black);
        shape->setPosition({float(rand()%1024), float(rand()%768)});
        solidObjects.push_back(shape);
    }
}


list<RectangleShape*> Map::getSolidObjets(){
    return solidObjects;
}
