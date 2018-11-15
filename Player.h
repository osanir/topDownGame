#include <SFML/Graphics.hpp>
using namespace sf;

class Player{
public:
    Player();
    void init();
    void update();
    void move(Vector2f);
    void fire();
    RectangleShape getBody();

private:
    RectangleShape _body;
    RectangleShape _gun;
    const Vector2f SPEED = {2, 2};
};