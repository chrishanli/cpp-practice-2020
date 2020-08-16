// player_paddle.cpp
// the paddle

#include "player_paddle.h"
#include "global/game.h"
#if _WIN32
#include "assert.h"
#endif

PlayerPaddle::PlayerPaddle()
: _velocity(0)
, _maxVelocity(500.0f) {
    load("resources/paddle.lh.png");
    assert(isLoaded());
    
    getSprite().setPosition(getSprite().getLocalBounds().width / 2,
                            getSprite().getLocalBounds().height / 2);
}

void PlayerPaddle::draw(sf::RenderWindow& rw) {
    VisibleGameObject::draw(rw);
}

void PlayerPaddle::update(float elapsedTime) {
    
    sf::Vector2f pos = this->getPosition();
    float width = getSprite().getLocalBounds().width;
    
    // bounce by current velocity in opposite direction
    // optimised by han at 9/7/2020
    if (pos.x < 0) {
        _velocity = -_velocity;
        setPosition(0, pos.y);
    } else if (pos.x > Game::SCREEN_WIDTH - width) {
        _velocity = -_velocity;
        setPosition(Game::SCREEN_WIDTH - width, pos.y);
    }
    
    getSprite().move(_velocity * elapsedTime, 0);
    
    // different api! han
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        _velocity -= 3.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        _velocity += 3.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        _velocity = 0.0f;
    }
    
    if (_velocity > _maxVelocity) {
        _velocity = _maxVelocity;
    } else if (_velocity < -_maxVelocity) {
        _velocity = -_maxVelocity;
    }
}


PlayerPaddle::~PlayerPaddle() { }

