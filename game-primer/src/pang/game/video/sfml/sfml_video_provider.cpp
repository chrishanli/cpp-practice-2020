//
//  sfml_video_provider.cpp
//  pang
//
//  Created by Han Li on 10/7/2020.
//  Copyright © 2020 Han Li. All rights reserved.
//

#include "sfml_video_provider.h"

SFMLVideoProvider::SFMLVideoProvider(int width, int height, int hpp, const std::string& title) {
    this->_mainWindow.create(sf::VideoMode(width, height, hpp), title);
}

void SFMLVideoProvider::render(VisibleGameObject& obj) {
    this->_mainWindow.draw(obj.getSprite());
}

void SFMLVideoProvider::close() {
    this->_mainWindow.close();
}

sf::RenderWindow SFMLVideoProvider::_mainWindow;
