// game.cpp
// the game program's location

#include "game.h"
#include "display/splash_screen.h"
#include "display/menu.h"
#include "objects/player_paddle.h"
#include "objects/ai_paddle.h"
#include "objects/game_ball.h"
#include "audio/sfml/sfml_sound_provider.h"

void Game::start() {
    if(_gameState != uninitialised)
        return;
	_mainWindow = new sf::RenderWindow();
	_mainWindow->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");
    
    // play background song
    SFMLSoundProvider soundProvider;
    _serviceManager.registerServiceProvider(&soundProvider);
    soundProvider.playSong("resources/sound_track.lh.ogg", true);
    
	_gameObjectManager = new GameObjectManager();
    // load the paddles and the ball initially
    GameBall *ball = new GameBall();
    ball->setPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);
    getGameObjectManager().add("ball", ball);
    
    PlayerPaddle *playerA = new PlayerPaddle;
    playerA->setPosition((SCREEN_WIDTH / 2) - 45, SCREEN_HEIGHT - 68);
	getGameObjectManager().add("player_a", playerA);
    
    AIPaddle *playerB = new AIPaddle;
    playerB->setPosition((SCREEN_WIDTH / 2), 40);
	getGameObjectManager().add("player_b", playerB);
    
    // the game is showing its initialise screen by now
    _gameState = Game::showingSplash;
    
    while(_gameState != Game::existing) {
        gameLoop();
    }
    
	getWindow().close();
	delete _mainWindow;
	delete _gameObjectManager;
}

void Game::gameLoop() {
    switch(_gameState) {
        case Game::showingMenu: {
            showMenu();
            break;
        }
        case Game::showingSplash: {
            showSplashScreen();
            break;
        }
        case Game::playing: {
            sf::Event currentEvent;
            // use if!! - debugged by han
            if (getWindow().pollEvent(currentEvent)) {
                switch (currentEvent.type) {
                    case sf::Event::Closed:
                        _gameState = Game::existing;
                        break;
                    case sf::Event::KeyPressed:
                        // if the user clicks the esc key, return to menu
                        if (currentEvent.key.code == sf::Keyboard::Escape) {
                            showMenu();
                        }
                        break;
                    default:
                        break;
                }
            }
            // debugged by han
            getGameObjectManager().updateAll();
            getWindow().clear(sf::Color(0, 0, 0)); // black
            // put all objects inside the manager onto the screen
            getGameObjectManager().drawAll(getWindow());
            getWindow().display();
            break;
        }
        default:
            break;
    }
}

void Game::showSplashScreen() {
    SplashScreen splash;
    splash.show(getWindow());
    // when the splash was closed, the menu comes
    _gameState = Game::showingMenu;
}

void Game::showMenu() {
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.show(getWindow());
    switch (result) {
        case MainMenu::exit:
            _gameState = Game::existing;
            break;
        case MainMenu::play:
            _gameState = Game::playing;
            break;
        default:
            break;
    }
}

sf::Clock& Game::getClock() {
    return _mainClock;
}

// *** static menbers initialise area ***
Game::GameState Game::_gameState = uninitialised;
ServiceManager Game::_serviceManager;
sf::RenderWindow* Game::_mainWindow = NULL;
GameObjectManager* Game::_gameObjectManager = NULL;
sf::Clock Game::_mainClock;