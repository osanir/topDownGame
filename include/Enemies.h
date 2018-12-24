#include "GameEngine.h"
#include <ctime>
#include <cmath>
#include <list>

struct EnemySpr{
    EnemySpr();
    Sprite getSprite() { return sprite; }
    Sprite sprite;
    Texture texture;
};

class Enemy{
public:
    Enemy();
    void update(list<RectangleShape*>);
    RectangleShape getBody();
    Sprite getSprite();
    RectangleShape body;
private:
    Sprite sprite;
    Texture texture;
    Vector2f direction;
    float rotation;
};

class Enemies{
public:
    Enemies();
    void createEnemy(int);
    list<Enemy*> getEnemies();
    list<Enemy*> enemies;
};