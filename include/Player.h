#include "GameEngine.h"
#include <string>
#include <list>
#include <cmath>


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
    void update(RenderWindow *window, View view);
    void setDirection( char direction , bool isPressed);
    void setFireStatement( bool isPressed );
    void move(Vector2f);
    void fire();
    void collision(list<RectangleShape*>);
    RectangleShape getBody();
    RectangleShape getGun();
    list<Bullet> getBullets();

private:
    float lerp(float x, float y, float z);
    float getAngleTowardPosition(RenderWindow *window, View view);

    RectangleShape body;
    RectangleShape gun;
    list<Bullet> bullets;
    float fireRate = 0.2;

    const float MAXSPEED = 5;
    const float ACCELERATION    = 0.5;
    Vector2f velocity;

    bool isMovingRight = false;
    bool isMovingLeft  = false;
    bool isMovingUp    = false;
    bool isMovingDown  = false;
    bool isFiring      = false;
    
    bool canMoveRight = true;
    bool canMoveLeft  = true;
    bool canMoveUp    = true;
    bool canMoveDown  = true;
    bool canFire      = false;

    Clock clock;

};