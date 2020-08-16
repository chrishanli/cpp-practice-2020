// menu.cpp
// implementations of interfaces about menu

#include "menu.h"

MainMenu::MenuResult MainMenu::show(sf::RenderWindow& window) {
    // load menu background image from file
    sf::Texture image;
    image.loadFromFile("resources/main_menu.lh.png");
    sf::Sprite sprite(image);
    
    // set up the Play menu item clickable coordinates
    MenuItem playButton;
    playButton.rect.top = 145;
    playButton.rect.height = 380 - playButton.rect.top;
    playButton.rect.left = 0;
    playButton.rect.width = 1023 - playButton.rect.left;
    playButton.action = MenuResult::play;
    
    // set up the Exit menu item clickable coordinates
    MenuItem exitButton;
    exitButton.rect.left = 0;
    exitButton.rect.width = 1023 - playButton.rect.left;
    exitButton.rect.top = 383;
    exitButton.rect.height = 560 - exitButton.rect.top;
    exitButton.action = MenuResult::exit;
    
    // add the above menu item to the menu list
    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);
    
    window.draw(sprite);
    window.display();
    
    return getMenuResponse(window);
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y) {
    std::list<MenuItem>::iterator it;
    // check whether the click point is within any item's region
    for (it = _menuItems.begin(); it != _menuItems.end(); it++) {
        sf::Rect<int> menuItemRect = (*it).rect;
        if (menuItemRect.top < y &&
            menuItemRect.height + menuItemRect.top > y &&
            menuItemRect.left < x &&
            menuItemRect.width + menuItemRect.left > x) {
            // found the item that the user is clicking
            return (*it).action;
        }
    }
    
    return nothing;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window) {
    sf::Event menuEvent;
    while (true) {
        if (window.pollEvent(menuEvent)) {
            switch (menuEvent.type) {
                // some place in the menu was clicked
                case sf::Event::MouseButtonPressed:
                    return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
                // the menu was closed
                case sf::Event::Closed:
                    return exit;
                default:
                    break;
            }
        }
    }
}
