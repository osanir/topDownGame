#include "../include/Map.h"

Map::Map(){
    /* createRandomObjects(); */
    tileset_texture.loadFromFile("res/tilemap.jpeg");
    tileset_spr.setTexture(tileset_texture);
    tileset_spr.setScale(1.0f , (float)1024/tileset_texture.getSize().y);
    readMap();
    initMap();
}

/* void Map::createRandomObjects(){
    for(int i=0; i<10; i++){
        RectangleShape* shape = new RectangleShape({20,20});
        shape->setFillColor(Color::Black);
        shape->setPosition({float(rand()%1024), float(rand()%768)});
        solidObjects.push_back(shape);
    }
} */

void Map::readMap(){
    vector<int> tempMap;
    tempMap.clear();
    map_tiles.clear();

    ifstream openFile("res/map.txt");

    if(openFile.is_open()){

        int str;
        while(openFile >> str){
            if( str != -1){
                tempMap.push_back(str);
                cout << str;
            }
            else{
                map_tiles.push_back(tempMap);
                tempMap.clear();
                cout << endl;
            }

        }
    }

}

void Map::drawTile(RenderWindow &window){

    for(int y = 0 ; y < map_tiles.size() ; y ++ ){
        for(int x =0 ; x< map_tiles[1].size() ; x++){
            //tek bir sprite ın boyutu kadar yer ayır
            tileset_spr.setPosition(x * 42.f , y*42.f);
            //resimden parça parça seç
            tileset_spr.setTextureRect(IntRect(map_tiles[y][x]*42 , 0 ,42 , 42));
            window.draw(tileset_spr);
        }
    }
}
void Map::initMap(){

    for(int y = 0 ; y < map_tiles.size() ; y ++ ){
        for(int x =0 ; x< map_tiles[1].size() ; x++){
            //tek bir sprite ın boyutu kadar yer ayır
            tileset_spr.setPosition(x * 42.f , y*42.f);
            //resimden parça parça seç
            tileset_spr.setTextureRect(IntRect(map_tiles[y][x]*42 , 0 ,42 , 42));
            if(map_tiles[y][x] == 0){
                
                RectangleShape* shape = new RectangleShape({42,42});
                shape->setFillColor(Color::Black);
                shape->setPosition({x * 42.f  , y*42.f});
                solidObjects.push_back(shape);

            }
        }
    } 


}
list<RectangleShape*> Map::getSolidObjets(){
    return solidObjects;
}
