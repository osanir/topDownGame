#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"

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
    
    Camera camera;

    Player player;
    RenderWindow window;
    Map map;
};