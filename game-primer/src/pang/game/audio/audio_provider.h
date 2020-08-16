// audio_provider.h
// the base interface of audio engines

#ifndef audio_provider_h
#define audio_provider_h

#include <string>

// the base interface of audio engines
class AudioProvider {
public:
    virtual ~AudioProvider() {}
    // play a sound file
    virtual void playSound(std::string filename) = 0;
    // play a song file
    virtual void playSong(std::string filename, bool looping) = 0;
    // stop all songs that are playing
    virtual void stopAllSounds() = 0;
    
    // tells if any sound is playing
    virtual bool isSoundPlaying() = 0;
    // tells if any song is playing
    virtual bool isSongPlaying() = 0;
};

#endif /* audio_provider_h */
