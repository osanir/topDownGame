#include "../include/Menu.h"

Menu::Menu(){

    if(!font.loadFromFile("assets/BACKTO1982.TTF")) {

       while(true)
       cout<<"Dosya açılamadı"<<endl;
    }
    menu[0].setFont(font);
    menu[0].setFillColor(Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(Vector2f( 1024 / 2  , 720 / (MAX_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(Color::Blue);
    menu[1].setString("Options");
    menu[1].setPosition(Vector2f( 1024 / 2  , 720 / (MAX_ITEMS + 1) * 2));
    
    menu[2].setFont(font);
    menu[2].setFillColor(Color::Blue);
    menu[2].setString("Quit");
    menu[2].setPosition(Vector2f( 1024 / 2  , 720 / (MAX_ITEMS + 1) * 3));

    selectedItems = 0;
    
    menuState = true;
}


void Menu::drawMenu(RenderWindow &window){
    
       for(int i = 0 ; i<MAX_ITEMS ; i++){
            window.draw(menu[i]);
        }
}


void Menu::MoveUp(){
    
    if(selectedItems > 0 ){
        menu[selectedItems].setFillColor(Color::Blue);
        selectedItems -= 1; 
        menu[selectedItems].setFillColor(Color::Red);
    }
    else if(selectedItems == 0){
        menu[selectedItems].setFillColor(Color::Blue);
        selectedItems = 2; 
        menu[selectedItems].setFillColor(Color::Red);

    }

}

void Menu::MoveDown(){
    
    if(selectedItems < MAX_ITEMS - 1 ){

        menu[selectedItems].setFillColor(Color::Blue);
        selectedItems += 1; 
        menu[selectedItems].setFillColor(Color::Red);
    }
    else if(selectedItems == 2 ){
        menu[selectedItems].setFillColor(Color::Blue);
        selectedItems  = 0; 
        menu[selectedItems].setFillColor(Color::Red);
    }

}

void Menu::setMenuState (bool menuState) { this -> menuState = menuState ;}

bool Menu::getMenuState (){ return menuState ;}

int Menu::getPressedItem(){return selectedItems;}