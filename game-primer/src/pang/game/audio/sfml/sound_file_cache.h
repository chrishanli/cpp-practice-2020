// sound_file_cache.h
// the SFML version of a sound file cache

#ifndef sound_file_cache_h
#define sound_file_cache_h

#include <SFML/Audio.hpp>
#include <map>

typedef std::pair<std::string, sf::SoundBuffer*> SoundBufferItem;
typedef std::map<std::string, sf::SoundBuffer*> SoundBufferMap;
typedef std::pair<std::string, sf::Music*> MusicItem;
typedef std::map<std::string, sf::Music*> MusicMap;

class SoundFileCache {
public:
    SoundFileCache(void);
    ~SoundFileCache(void);
    
    sf::Sound getSound(std::string) const;
    sf::Music* getSong(std::string) const;
    
private:
    // the sound tracks
    static SoundBufferMap _sounds;
    // the music tracks
    static MusicMap _music;
    
    // template Deallocator for both Sound and Music types
    template <typename T>
    struct Deallocator {
        void operator()(const std::pair<std::string, T> &p) {
            delete p.second;
        }
    };
};


#endif /* sound_file_cache_h */
