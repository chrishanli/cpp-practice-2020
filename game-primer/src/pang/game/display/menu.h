// menu.h
// interfaces about menu

#ifndef menu_h
#define menu_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class MainMenu {
public:
    // indicates when a menu item is clicked
    enum MenuResult {
        nothing,
        exit,
        play
    };
    
    // menu item
    struct MenuItem {
        // the rectangle of this menu item
        sf::Rect<int> rect;
        // the result that will be lead to by clicking the item
        MenuResult action;
    };
    
    // shows this menu on a certain window
    MenuResult show(sf::RenderWindow& window);
    
private:
    MenuResult getMenuResponse(sf::RenderWindow& window);
    MenuResult handleClick(int x, int y);
    std::list<MenuItem> _menuItems;
};

#endif /* menu_h */
