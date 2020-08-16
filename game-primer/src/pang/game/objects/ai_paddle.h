// ai_paddle.h
// a stupid AI-managed paddle

#ifndef ai_paddle_h
#define ai_paddle_h

#include "visible_game_object.h"

class AIPaddle: public VisibleGameObject {
public:
    AIPaddle(void);
    ~AIPaddle(void);
    
    void update(float elapsedTime);
    void draw(sf::RenderWindow& rw);
    
    inline float getVelocity() const { return _velocity; }
    
private:
    float _velocity;  // -- left ++ right
    float _maxVelocity;
};

#endif /* ai_paddle_h */
