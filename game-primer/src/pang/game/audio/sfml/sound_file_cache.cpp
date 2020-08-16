// sound_file_cache.cpp

#include "sound_file_cache.h"
#include "exceptions/exceptions.h"

SoundFileCache::SoundFileCache(void) {}

SoundFileCache::~SoundFileCache(void) {
    std::for_each(_sounds.begin(),
                  _sounds.end(),
                  Deallocator<sf::SoundBuffer*>());
    
//    std::for_each(_music.begin(),
//                  _music.end(),
//                  Deallocator<sf::Music*>());
}


sf::Sound SoundFileCache::getSound(std::string soundName) const {
    // find the corresponding sound buffer
    SoundBufferMap::iterator itr = _sounds.find(soundName);
    if(itr == _sounds.end()) {
        // allocate a new cache block for the non-target sound
        sf::SoundBuffer *soundBuffer = new sf::SoundBuffer();
        if(!soundBuffer->loadFromFile(soundName)) {
            delete soundBuffer;
            throw SoundNotFoundExeception(soundName + " was not found in cache or disk.");
        } else {
            _sounds.insert(SoundBufferItem(soundName, soundBuffer));
            sf::Sound sound;
            sound.setBuffer(*soundBuffer);
            return sound;
        }
        
//        sf::Sound sound;
//        sound.setBuffer(*soundBuffer);
//        return sound;
    }
    else {
        sf::Sound sound;
        sound.setBuffer(*itr->second);
        return sound;
    }
}

sf::Music* SoundFileCache::getSong(std::string songName) const {
    MusicMap::iterator itr = _music.find(songName);
    if(itr == _music.end()) {
        sf::Music *song = new sf::Music();
        if(!song->openFromFile(songName)) {
            delete song;
            throw SoundNotFoundExeception(songName + " was not found in cache or disk.");
        } else {
            _music.insert(MusicItem(songName, song));
            return song;
        }
    }
    else {
        return itr->second;
    }
    
}

std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;
