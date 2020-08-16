// service_manager
// the service manager such as audio, cameras, IO, graphics, etc.

#include "service_manager.h"

AudioProvider* ServiceManager::_audioProvider = NULL;
VideoProvider* ServiceManager::_videoProvider = NULL;
