#include "GameEngine.h"
#include <string>
#include <list>
#include <cmath>


struct Bullet{
    RectangleShape body;
    Vector2f direction;
    float speed = 3;
    Bullet(){
        body.setSize({20,9});
        //body.setRadius(30);
        //body.setFillColor(Color::Black);
        body.setOrigin({0, body.getSize().y});
    };
};

/*
struct Gun{
    string name;
    int fireRate;
    int capasity;
};
*/
struct OtherPlayers{
    OtherPlayers();
    Texture texture;
    Sprite playerSprite;
    list<Bullet> bullets;
};

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
    Sprite getSprite();
    list<Bullet> getBullets();

    Texture textures[2];
        // texture[0]   :   player texture
        // texture[1]   :   bullet texture
private:
    float lerp(float x, float y, float z);
    float getAngleTowardPosition(RenderWindow *window, View view);

    RectangleShape body;
    Sprite playerSprite;

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
    bool canFire      = true;

    Clock clock;

};