// game_object_manager.h
// the object manager

#ifndef game_object_manager_h
#define game_object_manager_h

#include "objects/visible_game_object.h"
#include <map>

typedef std::pair<std::string, VisibleGameObject*> ObjectMapItem;
typedef std::map<std::string, VisibleGameObject*> ObjectMap;

class GameObjectManager {
public:
    GameObjectManager();
    ~GameObjectManager();
    
    // add an visible object to the object pool
    void add(std::string name, VisibleGameObject* gameObject);
    // remove an visible object to the object pool
    void remove(std::string name);
    // derive the object count from the pool
    size_t getObjectCount() const;
    // select the corresponding object from the pool through its name
    VisibleGameObject* get(std::string name) const;
    // place all the object onto the window
    void drawAll(sf::RenderWindow& renderWindow);
    // notify all objects so they would update their actions
    void updateAll();
    
private:
    std::map<std::string, VisibleGameObject*> _gameObjects;
    
    struct GameObjectDeallocator {
        void operator()(const ObjectMapItem & p) const {
            delete p.second;
        }
    };
};

#endif /* game_object_manager_h */
