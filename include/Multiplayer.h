
#include "Player.h"

using namespace std;
using namespace sf;

class Multiplayer{
public:
    Multiplayer();
    void setUpdateStatus(bool);
    void update(Player&, OtherPlayers&);
    char getConnectionType();
    TcpSocket socket;
private:
    bool canUpdate;
    IpAddress ip = IpAddress::getLocalAddress();
    char connectionType;
};