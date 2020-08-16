// ai_paddle.cpp
// a stupid AI-managed paddle

#include "ai_paddle.h"
#include "game_ball.h"
#include "global/game.h"
#if _WIN32
#include "assert.h"
#endif

AIPaddle::AIPaddle()
: _velocity(0)
, _maxVelocity(600.0f) {
    load("resources/paddle.lh.png");
    assert(isLoaded());
    
    sf::FloatRect bounds = getSprite().getLocalBounds();
    getSprite().setOrigin(bounds.width / 2, bounds.height / 2);
}


AIPaddle::~AIPaddle() { }

void AIPaddle::draw(sf::RenderWindow & rw) {
    VisibleGameObject::draw(rw);
}

void AIPaddle::update(float elapsedTime) {
    const GameBall* gameBall = static_cast<GameBall*>
    (Game::getGameObjectManager().get("ball"));
    sf::Vector2f ballPosition = gameBall->getPosition();
    
    if (getPosition().x - 20 < ballPosition.x) {
        _velocity += 10.0f;
    } else if (getPosition().x + 20 > ballPosition.x) {
        _velocity -= 10.0f;
    } else {
        _velocity = 0.0f;
    }
    
    if(_velocity > _maxVelocity) {
        _velocity = _maxVelocity;
    } else if(_velocity < -_maxVelocity) {
        _velocity = -_maxVelocity;
    }
    
    sf::Vector2f pos = this->getPosition();
    sf::FloatRect bounds = getSprite().getLocalBounds();
    
    if (pos.x  <= bounds.width / 2 ||
        pos.x >= (Game::SCREEN_WIDTH - bounds.width / 2)) {
        _velocity = -_velocity; // Bounce by current velocity in opposite direction
    }
    
    getSprite().move(_velocity * elapsedTime, 0);
}
