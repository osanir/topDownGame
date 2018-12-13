#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

using namespace std;
using namespace sf;

class Game
{
public:
    Game();
    void run();
    Vector2f position;
private:

    void processEvents();
    void update();
    void render();
    void handlePlayerInput(bool isPressed);
    
    View view;
    Player player;
    RenderWindow window;
    Map map;
};