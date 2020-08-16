// video_provider.h
// the base interface of video engines

#ifndef video_provider_h
#define video_provider_h

#include "objects/visible_game_object.h"

// the base interface of video engines
class VideoProvider {
public:
    virtual ~VideoProvider() {}
    // render a visible object onto the main screen
    virtual void render(VisibleGameObject& obj) = 0;
    // close the main screen
    virtual void close() = 0;
};

#endif /* video_provider_h */
