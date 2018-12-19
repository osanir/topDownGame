
#include "Player.h"

using namespace std;
using namespace sf;

class Multiplayer{
public:
    Multiplayer();
    void setUpdateStatus(bool);
    void update(Player&, OtherPlayers&);
private:
    bool canUpdate;
    TcpSocket socket;
    IpAddress ip = IpAddress::getLocalAddress();
};