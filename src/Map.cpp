#include "../include/Map.h"

Map::Map(){
    pixelScale = 128;
    tileset_texture.loadFromFile("res/tiles.png");
    tileset_spr.setTexture(tileset_texture);
    tileset_spr.setScale(1.0f , 1.0f);
    importMap();
    initMap();
}

/* void Map::createRandomObjects(){
    for(int i=0; i<10; i++){
        RectangleShape* shape = new RectangleShape({20,20});
        shape->setFillColor(Color::Black);
        shape->setPosition({float(rand()%1024), float(rand()%768)});
        solidObjects.push_back(shape);
    }f
} */

void Map::importMap(){
    vector<int> tempMap;
    tempMap.clear();
    map_tiles.clear();

    ifstream openFile("res/map.txt");

    if(openFile.is_open()){

        int str;
        while(openFile >> str){
            if( str != -1){
                tempMap.push_back(str);
            }
            else{
                map_tiles.push_back(tempMap);
                tempMap.clear();
            }

        }
    }

}

void Map::drawTile(RenderWindow &window){
    for(int y = 0 ; y < map_tiles.size() ; y ++ ){
        for(int x =0 ; x< map_tiles[0].size() ; x++){
            //tek bir sprite ın boyutu kadar yer ayır
            tileset_spr.setPosition(x * pixelScale , y*pixelScale);
            //resimden parça parça seç
            tileset_spr.setTextureRect(IntRect(map_tiles[y][x] * pixelScale, 0 , pixelScale, pixelScale));
            window.draw(tileset_spr);
        }
    }
}

void Map::initMap(){
    for(int y = 0 ; y < map_tiles.size() ; y ++ ){
        for(int x =0 ; x< map_tiles[0].size() ; x++){
            //tek bir sprite ın boyutu kadar yer ayır
            tileset_spr.setPosition(x * pixelScale , y * pixelScale);
            //resimden parça parça seç
            tileset_spr.setTextureRect(IntRect(map_tiles[y][x] * pixelScale , 0, pixelScale, pixelScale));
            
            // if its wall
            if(map_tiles[y][x] == TILES::WALL){
                RectangleShape* shape = new RectangleShape({pixelScale, pixelScale});
                shape->setFillColor(Color::Black);
                shape->setPosition({x * pixelScale, y * pixelScale});
                solidObjects.push_back(shape);

            }
        }
    } 
    layoutSize.x = map_tiles[0].size() * pixelScale;
    layoutSize.y = map_tiles.size() * pixelScale;

}

list<RectangleShape*> Map::getSolidObjects(){
    return solidObjects;
}

Vector2f Map::getLayoutSize(){
    return layoutSize;
}