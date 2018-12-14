#include <string>
#include <list>
#include <cmath>
#include "GameEngine.h"


struct Bullet{
    CircleShape body;
    Vector2f direction;
    float speed = 4;
};

/*
struct Gun{
    string name;
    int fireRate;
    int capasity;
};
*/

class Player{
public:
    Player();
    void init();
    void update(RenderWindow *window);
    void setDirection( char direction , bool isPressed);
    void move(Vector2f);
    void fire();
    void collision(list<RectangleShape*>);
    CircleShape getBody();
    RectangleShape getGun();
    list<Bullet> getBullets();

private:
    float lerp(float x, float y, float z);
    float getAngleTowardPosition(RenderWindow *window);

    CircleShape body;
    RectangleShape gun;
    list<Bullet> bullets;

    const float MAXSPEED = 5;
    const float SPEED    = 0.5;
    Vector2f velocity;

    bool isMovingRight = false;
    bool isMovingLeft  = false;
    bool isMovingUp    = false;
    bool isMovingDown  = false;

};