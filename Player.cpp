#include "Player.h"

Player::Player(){
    body.setSize( {20, 20} );
    body.setOrigin( {body.getSize().x/2, body.getSize().y/2} );
    body.setPosition( {0, 0} );
    body.setFillColor(Color::Black);

    gun.setSize( {body.getSize().x, body.getSize().y/4} );
    gun.setOrigin( {0, gun.getSize().y/2} );
    gun.setPosition( body.getOrigin() );
    gun.setFillColor(Color::Red);
    
}

void Player::init(){
}

void Player::update(RenderWindow *window){
    if( isMovingLeft && velocity.x > -MAXSPEED )
        velocity.x -= SPEED;
    if( isMovingRight && velocity.x < MAXSPEED )
        velocity.x += SPEED;
    if( isMovingUp && velocity.y > -MAXSPEED)
        velocity.y -= SPEED;
    if( isMovingDown && velocity.y < MAXSPEED)
        velocity.y += SPEED;

    if( !isMovingLeft && !isMovingRight )
        velocity.x = lerp(velocity.x, 0, 0.1);
    if( !isMovingUp && !isMovingDown )
        velocity.y = lerp(velocity.y, 0, 0.1);
    

    body.move(velocity);
    body.setRotation(getAngleTowardPosition(window));
    gun.setRotation(body.getRotation());
    gun.setPosition(body.getPosition());
}

void Player::move(Vector2f direction){
    body.move(direction);
    gun.setPosition( {body.getPosition().x, body.getPosition().y} );
}

void Player::fire(){

}

RectangleShape Player::getBody(){
    return body;
}

RectangleShape Player::getGun(){
    return gun;
}


void Player::setDirection( char direction , bool isPressed){
    switch (direction){
        case 'A':
            if( isPressed)
                isMovingLeft = true;
            else
                isMovingLeft = false;
            break;
        case 'D':
            if( isPressed)
                isMovingRight = true;
            else
                isMovingRight = false;
            break;
        case 'W':
            if( isPressed)
                isMovingUp = true;
            else
                isMovingUp = false;
            break;
        case 'S':
            if( isPressed)
                isMovingDown = true;
            else
                isMovingDown = false;
            break;
        default:
            break;
    }
}

float Player::lerp(float x, float y, float z) {
    return ((1.0f - z) * x) + (z * y);      
}

float Player::getAngleTowardPosition(RenderWindow *window){
    float y, y1;
    float x, x1;
    float m;

    x = body.getPosition().x;
    y = body.getPosition().y;

    x1 = Mouse::getPosition(*window).x;
    y1 = Mouse::getPosition(*window).y;


    m = (y-y1) / (x-x1);
    m = atan(m);
    m = m * 180 / 3.14159265;
    if( x > x1) m += 180;
    return m;
}
