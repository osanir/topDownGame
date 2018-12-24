#include "GameEngine.h"
#include "Map.h"
#include "Camera.h"
#include "Multiplayer.h"
#include <list>
using namespace std;
using namespace sf;

class Game{
public:
    Game();
    void run();
private:

    void processEvents();
    void update();
    void render();
    void handlePlayerInput(bool isPressed);
    
    bool gameFocus;

    Camera camera;
    Player player;
    OtherPlayers player2;
    RenderWindow window;
    Map map;
    Multiplayer multiplayer;
    Enemies enemies;
    list<EnemySpr*> otherEnemies;   
};