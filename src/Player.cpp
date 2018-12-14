#include "../include/Player.h"

Player::Player(){
    body.setRadius( 10 );
    body.setOrigin( {body.getRadius(), body.getRadius()} );
    body.setPosition( {100, 100} );
    body.setFillColor(Color::Black);

    gun.setSize( {body.getRadius()*2, body.getRadius()/2} );
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
    list<Bullet>::iterator iter = bullets.begin();
    while( iter != bullets.end() ){
        iter->body.move(iter->direction);
        // TODO: DESTROY BULLETS WHICH ARE OUTSIDE THE WINDOW
        /*if( iter->body.getPosition().x > window->getSize().x || iter->body.getPosition().x < 0 || iter->body.getPosition().y > window->getSize().y || iter->body.getPosition().x < 0){
            bullets.remove(iter);
        }*/
        iter++;
    }
    
    CircleShape shape(10);
    shape.setFillColor(Color::Cyan);
    
    window->draw( shape );
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

void Player::move(Vector2f direction){
    // TODO: FIX DIAGONAL MOVEMENT SPEED
    body.move(direction);
    gun.setPosition( {body.getPosition().x, body.getPosition().y} );
}

void Player::fire(){
    // TODO: SET FIRE RATE
    Bullet newBullet;
    newBullet.body.setRadius(5);
    newBullet.body.setFillColor(Color::Black);
    newBullet.body.setOrigin({newBullet.body.getRadius(), newBullet.body.getRadius()});
    newBullet.body.setPosition(gun.getTransform().transformPoint( {gun.getSize().x, newBullet.body.getRadius()/2} ));
    
    float x1 = gun.getTransform().transformPoint( {gun.getSize().x, 0}).x;
    float y1 = gun.getTransform().transformPoint( {gun.getSize().x, 0}).y;
    float x  = gun.getTransform().transformPoint( {0, 0}).x;
    float y  = gun.getTransform().transformPoint( {0, 0}).y;
    float dirX = ((x1-x)/gun.getSize().x)*newBullet.speed;
    float dirY = ((y1-y)/gun.getSize().x)*newBullet.speed;

    newBullet.direction = Vector2f( dirX, dirY );
    bullets.push_back( newBullet );
}

void Player::collision(list<RectangleShape*> gameObjects){
    for( auto iter : gameObjects){
        if( body.getGlobalBounds().intersects(iter->getGlobalBounds()))
            body.move({-velocity.x, -velocity.y});
    }
}


// GET

CircleShape Player::getBody(){
    return body;
}

RectangleShape Player::getGun(){
    return gun;
}

list<Bullet> Player::getBullets(){
    return bullets;
}

// PRIVATE FUNCTIONS

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
