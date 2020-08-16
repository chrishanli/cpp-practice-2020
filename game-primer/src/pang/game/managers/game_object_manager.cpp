// game_object_manager.cpp
// the object manager

#include "global/game.h"
#include "game_object_manager.h"

GameObjectManager::GameObjectManager() { }

GameObjectManager::~GameObjectManager() {
    // deallocate all objects in the pool
    std::for_each(_gameObjects.begin(),
                  _gameObjects.end(),
                  GameObjectDeallocator());
}

void GameObjectManager::add(std::string name,
                            VisibleGameObject* gameObject) {
    // add an object to its juristiction
    _gameObjects
    .insert(ObjectMapItem(name, gameObject));
}

void GameObjectManager::remove(std::string name) {
    // find the object corresponds to the name given (if any)
    ObjectMap::iterator results = _gameObjects.find(name);
    if (results != _gameObjects.end()) {
        // only by an manager can the program deallocate an object
        delete results->second;
        _gameObjects.erase(results);
    }
}

VisibleGameObject* GameObjectManager::get(std::string name) const {
    // find the object corresponds to the name given (if any)
    ObjectMap::const_iterator results = _gameObjects.find(name);
    if (results == _gameObjects.end()) {
        return NULL;
    }
    return results->second;
    
}

size_t GameObjectManager::getObjectCount() const {
    return _gameObjects.size();
}

void GameObjectManager::drawAll(sf::RenderWindow& renderWindow) {
    ObjectMap::const_iterator itr = _gameObjects.begin();
    while (itr != _gameObjects.end()) {
        itr->second->draw(renderWindow);
        ++itr;
    }
}

void GameObjectManager::updateAll() {
    ObjectMap::const_iterator itr = _gameObjects.begin();
    float timeDelta = Game::getClock().restart().asSeconds();
    while (itr != _gameObjects.end()) {
        itr->second->update(timeDelta);
        ++itr;
    }
}
