// game.h
// the game header

#ifndef game_h
#define game_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "managers/game_object_manager.h"
#include "managers/service_manager.h"

// *** classes define area ***

// the Game class
class Game {
private:
    // the game's main guard function, which is infinitely looped until the program exits
    static void gameLoop();
    // shows the splash screen
    static void showSplashScreen();
    // shows the main menu screen
    static void showMenu();
    
    // the game states
    enum GameState {
        uninitialised,
        showingSplash,
        paused,
        showingMenu,
        playing,
        existing
    };
    
	// the current game's main window
	static sf::RenderWindow* _mainWindow;
	// the main clock
	static sf::Clock _mainClock;
    // the current game's state
    static GameState _gameState;
    // the game's service manager
    static ServiceManager _serviceManager;
	// the object manager of the whole game
	static GameObjectManager* _gameObjectManager;

public:
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

	// starts the game
	static void start();
	// get the main window
	inline static sf::RenderWindow& getWindow() 
	{ return *_mainWindow; }
	// get the main clock
	static sf::Clock& getClock();
	// get the object manager
	inline static GameObjectManager& getGameObjectManager() 
	{ return *_gameObjectManager; }
};

#endif /* game_h */
