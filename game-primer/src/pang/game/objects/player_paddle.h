// player_paddle.h

#ifndef player_paddle_h
#define player_paddle_h

#include "objects/visible_game_object.h"

class PlayerPaddle: public VisibleGameObject {
public:
    PlayerPaddle();
    ~PlayerPaddle();
    
    void update(float elapsedTime);
    void draw(sf::RenderWindow& rw);
    
    inline float getVelocity() const { return _velocity; }
    
private:
    float _velocity; // current moving velocity of the paddle
    float _maxVelocity; // the maximum moving velocity of the paddle
};


#endif /* player_paddle_h */
