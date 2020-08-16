// sfml_sound_provider.h
// the SFML engine of sound provider

#ifndef sfml_sound_provider_h
#define sfml_sound_provider_h

#include "audio/audio_provider.h"
#include "sound_file_cache.h"

class SFMLSoundProvider: public AudioProvider {
public:
    SFMLSoundProvider();
    
    void playSound(std::string filename);
    void playSong(std::string filename, bool looping = false);
    void stopAllSounds();
    
    bool isSoundPlaying();
    bool isSongPlaying();
    
private:
    static const int MAX_SOUND_CHANNELS = 5;
    
    SoundFileCache _soundFileCache;
    sf::Sound   _currentSounds[MAX_SOUND_CHANNELS];
    std::string _currentSongName;
};

#endif /* sfml_sound_provider_h */
