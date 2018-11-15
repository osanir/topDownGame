#include "Player.h"

Player::Player(){
    _body.setSize( {20, 20} );
    _body.setOrigin( {_body.getSize().x/2, _body.getSize().y/2} );
    _body.setPosition( {0, 0} );
    _body.setFillColor(Color::Black);

    _gun.setSize( {_body.getSize().x, _body.getSize().y/2} );
    _gun.setOrigin( {0, _gun.getSize().y/2} );
    _gun.setPosition( {_body.getPosition().x/2, _body.getPosition().y/2} );
    _gun.setFillColor(Color::Red);
}

void Player::init(){

}

void Player::update(){
}

void Player::move(Vector2f direction){
    _body.move(direction);
    _gun.setPosition( {_body.getPosition().x, _body.getPosition().y} );
}

void Player::fire(){

}

RectangleShape Player::getBody(){
    return _body;
}
