#include "../include/Camera.h"

Camera::Camera(){
    view.reset(FloatRect(0,0 , SCREEN_WIDTH , SCREEN_HEIGHT));
    view.setViewport(FloatRect(0 , 0 , 1.0f , 1.0f));

    position.x = SCREEN_WIDTH/2;
    position.y = SCREEN_HEIGHT/2;
}

void Camera::update(Vector2f playerPos, Vector2f layoutSize){
    if(playerPos.x < SCREEN_WIDTH/2)
        position.x = SCREEN_WIDTH/2;
    else if( playerPos.x > layoutSize.x - SCREEN_WIDTH/2) 
        position.x = layoutSize.x - SCREEN_WIDTH/2;
    else    
        position.x = playerPos.x;

    if(playerPos.y < SCREEN_HEIGHT/2)
        position.y = SCREEN_HEIGHT/2;
    else if( playerPos.y > layoutSize.y - SCREEN_HEIGHT/2)
        position.y = layoutSize.y - SCREEN_HEIGHT/2;
    else
        position.y = playerPos.y;
        
    view.setCenter(position);
}

View Camera::getView(){
    return view;
}
