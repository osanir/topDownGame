#include "SFML/Graphics.hpp"
#include <iostream>

#define MAX_ITEMS 3                     //menüdeki durum sayımız

using namespace std;
using namespace sf;

class Menu {

public:

    Menu();

    void drawMenu(RenderWindow &window);
    
    void MoveUp();                       //ok yönlerine göre menü adımlarını takip ediyoruz
    void MoveDown();    
    
    void setMenuState (bool menuState); //oyunun hangi durumuna geçeceğimizi belirliyoruz
    bool getMenuState();
    int getPressedItem();

private:

    bool menuState;
    int selectedItems;                  //hangi menü durumundayız onu tutuyoruz
    
    Font font;    
    Text menu[MAX_ITEMS];
};