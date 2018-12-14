#include "../include/Camera.h"

Camera::Camera(){
    view.reset(FloatRect(0,0 , SCREEN_WIDTH , SCREEN_HEIGHT));
    view.setViewport(FloatRect(0 , 0 , 1.0f , 1.0f));

    position.x = SCREEN_WIDTH/2;
    position.y = SCREEN_HEIGHT/2;
}

void Camera::update(Vector2f pos){
    if(pos.x > SCREEN_WIDTH/2)
        position.x = pos.x;
    else 
        position.x = SCREEN_WIDTH/2;

    view.setCenter(position);
}

View Camera::getView(){
    return view;
}