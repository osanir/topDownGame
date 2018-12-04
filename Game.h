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

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(bool isPressed);

    Player player;
    RenderWindow window;
    Map map;
};