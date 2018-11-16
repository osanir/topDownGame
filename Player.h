#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;
using namespace std;

class Player{
public:
    Player();
    void init();
    void move(Vector2f);
    void update(RenderWindow *window);
    void fire();
    void setDirection( char direction , bool isPressed);
    RectangleShape getBody();
    RectangleShape getGun();

private:
    float lerp(float x, float y, float z);
    float getAngleTowardPosition(RenderWindow *window);

    RectangleShape body;
    RectangleShape gun;
    const float MAXSPEED = 5;
    const float SPEED    = 0.5;
    Vector2f velocity;

    bool isMovingRight = false;
    bool isMovingLeft  = false;
    bool isMovingUp    = false;
    bool isMovingDown  = false;
};