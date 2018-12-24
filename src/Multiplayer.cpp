#include "../include/Multiplayer.h"

Multiplayer::Multiplayer(){
    cout << "Server (s) or Client (c)?" << endl;
    cin >> connectionType;
    if( connectionType == 's' ){
        TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);
    } 
    else if( connectionType == 'c'){
        socket.connect(ip, 2000);
    }

    socket.setBlocking(false);

    canUpdate = true;
}

void Multiplayer::setUpdateStatus(bool update){
    canUpdate = update;
}

void Multiplayer::update(Player& player, OtherPlayers& player2){
    Packet packet;
    packet << 1; // flag byte, 1 for second player position and bullets
    
    // player position, rotation is the first 3 parameters of packet:
    packet << player.getBody().getPosition().x << player.getBody().getPosition().y << player.getGun().getRotation();
    
    // other all blanks filled with bullets position and rotation
    for( auto bullet : player.getBullets() )
        packet << bullet.body.getPosition().x << bullet.body.getPosition().y << bullet.body.getRotation();
    
    socket.send(packet);


    socket.receive(packet);
    
    int type;
    packet >> type;
    if( type == 1 ){    // if type 1, it means this packet dedicated for player2 and player2's bullets
        float x, y, rot;
        if( packet >> x >> y >> rot ){  // first 3 parameter for player2
            player2.playerSprite.setPosition({x,y});
            player2.playerSprite.setRotation(rot);
            player2.bullets.clear();
            while(!packet.endOfPacket()){   // other all values for bullets
                Bullet newBullet;
                float x, y, rot;
                packet >> x >> y >> rot;
                newBullet.body.setPosition({x,y});
                newBullet.body.setTexture(&player.textures[1]);
                newBullet.body.setRotation(rot);
                player2.bullets.push_back(newBullet);
            }
        }
    }
}

char Multiplayer::getConnectionType(){
    return connectionType;
}
