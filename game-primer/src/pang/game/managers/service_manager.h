// service_manager.h
// the service manager such as audio, cameras, IO, graphics, etc.

#ifndef service_provider_h
#define service_provider_h

#include "audio/audio_provider.h"
#include "video/video_provider.h"

class ServiceManager {
public:
    static AudioProvider* getAudio() { return _audioProvider; } const
    static VideoProvider* getVideo() { return _videoProvider; } const
    
    // to record a provider of a certain audio service
    static void registerServiceProvider(AudioProvider *provider) {
        _audioProvider = provider;
    }
    
    // to record a provider of a certain video service
    static void registerServiceProvider(VideoProvider *provider) {
        _videoProvider = provider;
    }
    
private:
    static AudioProvider * _audioProvider;
    static VideoProvider * _videoProvider;
};

#endif /* service_provider_h */
