#include "../include/Enemies.h"

EnemySpr::EnemySpr(){
        if(!texture.loadFromFile("res/zombie.png"))
            cout << "Yüklenemedi" << endl;
        sprite.setTexture(texture);
        sprite.setOrigin({float(texture.getSize().x/2), float(texture.getSize().y/2)});
}

Enemy::Enemy(){
    texture.loadFromFile("res/zombie.png");
    body.setSize({20,20});
    body.setFillColor(Color::Blue);
    body.setOrigin({body.getSize().x/2, body.getSize().y/2});
    sprite.setTexture(texture);
    sprite.setOrigin({float(texture.getSize().x/2), float(texture.getSize().y/2)});

    rotation = rand()%360;
    sprite.setRotation(rotation);
    direction.x = cos(rotation*3.14159265/180);
    direction.y = sin(rotation*3.14159265/180);
    // TODO: set random position between layout width and height
    body.setPosition({float(rand()%1000+256), float(rand()%1000+256)});
}

void Enemy::update(list<RectangleShape*> walls){
    body.move(direction);
    sprite.setPosition(body.getPosition() );
    for( auto wall : walls )
        if( body.getGlobalBounds().intersects(wall->getGlobalBounds())){
            rotation += 45;
            sprite.setRotation(rotation);
            direction.x = cos(rotation*3.14159265/180);
            direction.y = sin(rotation*3.14159265/180);
        }
}

RectangleShape Enemy::getBody(){
    return body;
}

Sprite Enemy::getSprite(){
    return sprite;
}

Enemies::Enemies(){
    srand(time(NULL));
}

void Enemies::createEnemy(int count){
    for(int i=0; i<count; i++){
        Enemy *enemy = new Enemy;
        enemies.push_back(enemy);
    }
}

list<Enemy*> Enemies::getEnemies(){
    return enemies;
}