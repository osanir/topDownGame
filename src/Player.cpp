#include "../include/Player.h"

Player::Player(){
    body.setSize( {32,32} );
    body.setOrigin( {body.getSize().x/2, body.getSize().y/2} );
    body.setPosition( {200, 200} );
    //body.setFillColor(Color::Black);

    gun.setSize( {body.getSize().x, body.getSize().y/4} );
    gun.setOrigin( {0, gun.getSize().y/2} );
    gun.setPosition( body.getOrigin() );
    gun.setFillColor(Color::Red);

    textures[0].loadFromFile("res/player.png");
    playerSprite.setScale({64/float(textures[0].getSize().x), 64/float(textures[0].getSize().y)});
    playerSprite.setTexture(textures[0]);
    playerSprite.setOrigin({float(textures[0].getSize().x)/2, float(textures[0].getSize().y)/2});

    textures[1].loadFromFile("res/bullet.png");

}

void Player::init(){
}

void Player::update(RenderWindow *window, View view){
    if( isMovingLeft && velocity.x > -MAXSPEED )
        velocity.x -= ACCELERATION;
    if( isMovingRight && velocity.x < MAXSPEED )
        velocity.x += ACCELERATION;
    if( isMovingUp && velocity.y > -MAXSPEED)
        velocity.y -= ACCELERATION;
    if( isMovingDown && velocity.y < MAXSPEED)
        velocity.y += ACCELERATION;

    if( !isMovingLeft && !isMovingRight )
        velocity.x = lerp(velocity.x, 0, 0.1);
    if( !isMovingUp && !isMovingDown )
        velocity.y = lerp(velocity.y, 0, 0.1);
    

    body.move(velocity);
   
    gun.setPosition(body.getPosition());
    gun.setRotation(getAngleTowardPosition(window, view));
    
    playerSprite.setPosition(body.getPosition());
    playerSprite.setRotation(getAngleTowardPosition(window, view));

    for( auto &bullet : bullets ){
        bullet.body.move(bullet.direction);
        // TODO: DESTROY BULLETS WHICH ARE OUTSIDE THE LAYOUT
        /*if( iter->body.getPosition().x > window->getSize().x || iter->body.getPosition().x < 0 || iter->body.getPosition().y > window->getSize().y || iter->body.getPosition().x < 0){
        }*/
    }
        
    // Every 0.2 Seconds
    if(clock.getElapsedTime().asMilliseconds() > fireRate*1000){
        canFire = true;
        clock.restart();
    }

    if( isFiring && canFire)
        fire();
    
}

void Player::setDirection( char direction , bool isPressed){
    switch (direction){
        case 'A':
            if( isPressed && canMoveLeft )
                isMovingLeft = true;
            else
                isMovingLeft = false;
            break;
        case 'D':
            if( isPressed && canMoveRight )
                isMovingRight = true;
            else
                isMovingRight = false;
            break;
        case 'W':
            if( isPressed && canMoveUp )
                isMovingUp = true;
            else
                isMovingUp = false;
            break;
        case 'S':
            if( isPressed && canMoveDown )
                isMovingDown = true;
            else
                isMovingDown = false;
            break;
        default:
            break;
    }
}

void Player::setFireStatement( bool isPressed ){
    isFiring = isPressed;
}

void Player::move(Vector2f direction){
    // TODO: FIX DIAGONAL MOVEMENT SPEED
    body.move(direction);
    gun.setPosition( {body.getPosition().x, body.getPosition().y} );
}

void Player::fire(){
    Bullet newBullet;
    newBullet.body.setPosition(gun.getTransform().transformPoint( {gun.getSize().x, gun.getSize().y} ));
    newBullet.body.setTexture(&textures[1]);
    newBullet.body.setRotation(gun.getRotation());

    float x1 = gun.getTransform().transformPoint( {gun.getSize().x, 0}).x;
    float y1 = gun.getTransform().transformPoint( {gun.getSize().x, 0}).y;
    float x  = gun.getTransform().transformPoint( {0, 0}).x;
    float y  = gun.getTransform().transformPoint( {0, 0}).y;
    float dirX = ((x1-x)/gun.getSize().x)*newBullet.speed;
    float dirY = ((y1-y)/gun.getSize().x)*newBullet.speed;

    newBullet.direction = Vector2f( dirX * newBullet.speed, dirY * newBullet.speed );
    bullets.push_back( newBullet );
    canFire = false;
}

void Player::collision(list<RectangleShape*> gameObjects){
    for( auto wall : gameObjects){
        // wall top, player bottom
        if( body.getGlobalBounds().intersects({ wall->getPosition().x, wall->getPosition().y+wall->getSize().y, wall->getSize().x, 2}) ){
            body.move({0, fabs(velocity.y)});
            canMoveUp = false;
            velocity.y = 0;
        }
        else 
            canMoveUp = true;

        // wall bottom, player top
        if( body.getGlobalBounds().intersects({ wall->getPosition().x, wall->getPosition().y-2, wall->getSize().x, 2}) ){
            body.move({0, -fabs(velocity.y)});
            canMoveDown = false;
            velocity.y = 0;
        }
        else
            canMoveDown = true;

        // wall left, player right
        if( body.getGlobalBounds().intersects({ wall->getPosition().x+wall->getSize().x, wall->getPosition().y, 2, wall->getSize().y}) ){
            body.move({fabs(velocity.x), 0});
            canMoveLeft = false;
            velocity.x = 0;
        }
        else
            canMoveLeft = true;

        // wall right, player left
        if( body.getGlobalBounds().intersects({ wall->getPosition().x-2, wall->getPosition().y, 2, wall->getSize().y}) ){
            body.move({-fabs(velocity.x), 0});
            canMoveRight = false;
            velocity.x = 0;
        }
        else
            canMoveRight = true;
    }
}


// GET

RectangleShape Player::getBody(){
    return body;
}

RectangleShape Player::getGun(){
    return gun;
}

Sprite Player::getSprite(){
    return playerSprite;
}

list<Bullet> Player::getBullets(){
    return bullets;
}

// PRIVATE FUNCTIONS

float Player::lerp(float x, float y, float z) {
    return ((1.0f - z) * x) + (z * y);      
}

float Player::getAngleTowardPosition(RenderWindow *window, View view){
    float y, y1;
    float x, x1;
    float m;

    x = body.getPosition().x;
    y = body.getPosition().y;

    x1 = (view.getCenter().x - SCREEN_WIDTH/2)  + Mouse::getPosition(*window).x;
    y1 = (view.getCenter().y - SCREEN_HEIGHT/2) + Mouse::getPosition(*window).y;


    m = (y-y1) / (x-x1);
    m = atan(m);
    m = m * 180 / 3.14159265;
    if( x >= x1) m += 180;
    return m;
}
