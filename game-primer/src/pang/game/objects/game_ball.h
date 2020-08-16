// game_ball.h
// the game ball

#ifndef game_ball_h
#define game_ball_h

#include "objects/visible_game_object.h"

class GameBall: public VisibleGameObject {
public:
    GameBall();
    virtual ~GameBall();
    void update(float);
    
private:
    float _velocity;
    float _angle;
    float _elapsedTimeSinceStart;
    bool _isRunYet;
    
    float linearVelocityX(float angle);
    float linearVelocityY(float angle);
};

#endif /* game_ball_h */
