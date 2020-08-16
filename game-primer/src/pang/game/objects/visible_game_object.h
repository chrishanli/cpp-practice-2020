// visible_game_object.h
// the base class from which all the visible objects in the game were extends

#ifndef visible_game_object_h
#define visible_game_object_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class VisibleGameObject {
    friend class SFMLVideoProvider;
    
public:
    VisibleGameObject();
    
    // load the object's texture from a local image file
    virtual void load(std::string filename);
    
    // put the object onto a window
    virtual void draw(sf::RenderWindow & window);
    
    // update the object's place
    virtual void update(float elapsedTime);
    
    // set the absolute position at which the object is placed on the window
    virtual void setPosition(float x, float y);
    
    // get the current set absolute position of the object
    virtual sf::Vector2f getPosition() const
    { return _isLoaded ? _sprite.getPosition() : sf::Vector2f(); }
    
    // return true if the object was loaded by a texture
    virtual inline bool isLoaded() const { return _isLoaded; }
    
    // gets the object's width
    virtual inline float getWidth() const { return _sprite.getLocalBounds().width; }
    
    // gets the object's height
    virtual inline float getHeight() const { return _sprite.getLocalBounds().height; }
    
    // gets the object's bounds
    virtual inline sf::Rect<float> getBoundingRect() const { return _sprite.getGlobalBounds(); }
    
protected:
    // get the object's sprite -- han
    inline sf::Sprite& getSprite() { return _sprite; }
    
private:
    sf::Sprite  _sprite;
    sf::Texture _image;
    std::string _filename;
    bool _isLoaded;
    
};


#endif /* visible_game_object_h */
