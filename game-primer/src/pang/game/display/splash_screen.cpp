// splash_screen.cpp
// the splash screen producer

#include "splash_screen.h"

void SplashScreen::show(sf::RenderWindow& renderWindow) {
    sf::Texture image;
    
    // load the splash_screen
    if (!image.loadFromFile("resources/splash_screen.lh.png")) {
        // TODO - do some notification
        return;
    }
    
    // set the screen to contain the picture
    sf::Sprite sprite(image);
    renderWindow.draw(sprite);
    renderWindow.display();
    
    // loop to detect events emitted
    sf::Event event;
    while (true) {
        if (renderWindow.pollEvent(event)) {
            // optimised by han at 8/7/2020
            switch (event.type) {
                case sf::Event::EventType::KeyPressed:
                case sf::Event::EventType::MouseButtonPressed:
                case sf::Event::EventType::Closed:
                    // TODO - 完善事件处理
                    return;
                default:
                    break;
            }
        }
    }
}
