// game_ball.h
// the game ball

#include "game_ball.h"
#include "player_paddle.h"
#include "global/game.h"
#include "managers/service_manager.h"
#include <cmath>
#if _WIN32
#include "assert.h"
#endif

GameBall::GameBall()
: _velocity(600.0f)
, _elapsedTimeSinceStart(0.0f)
, _isRunYet(false) {
    load("resources/ball.lh.png");
    assert(isLoaded());
    getSprite().setPosition(15, 15);
    // set a random angle
    _angle = (float) (std::rand() % 360 + 1);
}

GameBall::~GameBall() {
    
}

void GameBall::update(float elapsedTime) {
    if (!_isRunYet) {
        _isRunYet = true;
    } else {
        _elapsedTimeSinceStart += elapsedTime;
        
        // delay game from starting until 3 seconds have passed
        if (_elapsedTimeSinceStart < 3.0f) return;
        
        float moveAmount = _velocity  * elapsedTime;
        float moveByX = linearVelocityX(_angle) * moveAmount;
        float moveByY = linearVelocityY(_angle) * moveAmount;
        
        
        // collide with the left side of the screen
        if (getPosition().x + moveByX <= 0 + getWidth() / 2 ||
            getPosition().x + getHeight() / 2 + moveByX >= Game::SCREEN_WIDTH) {
            // ricochet!
            _angle = 360.0f - _angle;
            if((_angle > 260.0f && _angle < 280.0f) ||
               (_angle > 80.0f && _angle < 100.0f) ) {
                _angle += 20.0f;
            }
            moveByX = -moveByX;
        }
        
        // get the player A
        PlayerPaddle* playerA = dynamic_cast<PlayerPaddle *>
        (Game::getGameObjectManager().get("player_a"));
        
        if (playerA != NULL) {
            sf::Rect<float> p1BB = playerA->getBoundingRect();
            if (p1BB.intersects(getBoundingRect())) {
                _angle =  360.0f - (_angle - 180.0f);
                if (_angle > 360.0f) _angle -= 360.0f;
                
                moveByY = -moveByY;
                
                // make sure ball isn't inside paddle
                if (getBoundingRect().width > playerA->getBoundingRect().top) {
                    setPosition(getPosition().x,
                                playerA->getBoundingRect().top - getWidth() / 2 - 1);
                }
                
                // now add "English" based on the players velocity.
                float playerVelocity = playerA->getVelocity();
                if (playerVelocity < 0) {
                    // moving left
                    _angle -= 30.0f;
                    if (_angle < 0 ) _angle = 360.0f - _angle;
                }
                else if(playerVelocity > 0) {
                    _angle += 30.0f;
                    if(_angle > 360.0f) _angle = _angle - 360.0f;
                }
                
                // play a song indicating that the ball hits the paddle
                ServiceManager::getAudio()->playSound("resources/kaboom.lh.ogg");
                _velocity += 5.0f;
            }
            
            if (getPosition().y - getHeight() / 2 <= 0) {
                _angle =  180 - _angle;
                moveByY = -moveByY;
            }
            
            if (getPosition().y + getHeight() / 2 + moveByY >=
                Game::SCREEN_HEIGHT) {
                // move to middle of the screen for now and randomize angle
                getSprite().setPosition(Game::SCREEN_WIDTH / 2,
                                        Game::SCREEN_HEIGHT / 2);
                
                _angle = (float) (std::rand() % 360 + 1); // draw a random number between 1 and 360
                
                _velocity = 230.0f;
                _elapsedTimeSinceStart = 0.0f;
            }
            
            getSprite().move(moveByX, moveByY);
        }
    }
}

float GameBall::linearVelocityX(float angle) {
    if ((angle -= 90) < 0) angle = 360 + angle;
    return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::linearVelocityY(float angle) {
    if ((angle -= 90) < 0) angle = 360 + angle;
    return (float)std::sin(angle * (3.1415926 / 180.0f));
}
