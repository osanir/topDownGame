#include "../include/Multiplayer.h"

Multiplayer::Multiplayer(){
    char connectionType;
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
    packet << player.getBody().getPosition().x << player.getBody().getPosition().y << player.getGun().getRotation();
    for( auto bullet : player.getBullets() )
        packet << bullet.body.getPosition().x << bullet.body.getPosition().y << bullet.body.getRotation();
    socket.send(packet);

    socket.receive(packet);
    float x, y, rot;
    if( packet >> x >> y >> rot ){
        player2.playerSprite.setPosition({x,y});
        player2.playerSprite.setRotation(rot);
        player2.bullets.clear();
        while(!packet.endOfPacket()){
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