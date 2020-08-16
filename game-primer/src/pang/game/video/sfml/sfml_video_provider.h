// sfml_video_provider.h

#ifndef sfml_video_provider_h
#define sfml_video_provider_h

#include <string>
#include <SFML/Window.hpp>
#include "video/video_provider.h"

class SFMLVideoProvider: public VideoProvider {
public:
    SFMLVideoProvider(int width, int height, int hpp, const std::string& title);
    
    // render a visible object onto the main screen
    void render(VisibleGameObject& obj);
    
    // close the main screen
    void close();
    
private:
    // main window
    static sf::RenderWindow _mainWindow;
};

#endif /* sfml_video_provider_h */
