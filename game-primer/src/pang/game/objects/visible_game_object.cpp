// visible_game_object.cpp

#include "visible_game_object.h"

VisibleGameObject::VisibleGameObject() {
    _isLoaded = false;
}

void VisibleGameObject::load(std::string filename) {
    if (!_image.loadFromFile(filename)) {
        _filename = "";
        _isLoaded = false;
    } else {
        _filename = filename;
        _sprite.setTexture(_image);
        _isLoaded = true;
    }
}

void VisibleGameObject::draw(sf::RenderWindow & renderWindow) {
    if (_isLoaded) {
        renderWindow.draw(_sprite);
    }
}

void VisibleGameObject::update(float elapsedTime) { }

void VisibleGameObject::setPosition(float x, float y) {
    if (_isLoaded) {
        _sprite.setPosition(x,y);
    }
}
