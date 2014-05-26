#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "GameBall.h"


void Game::Start(void) {
	if( _gameState != Uninitialized )
		return;

	_mainWindow.Create(sf::VideoMode(1024,768,32), "Pang!");

	PlayerPaddle *player1 = new PlayerPaddle(true);
	player1->SetPosition((SCREEN_WIDTH/2)-45, 700);

	PlayerPaddle *player2 = new PlayerPaddle(false);
	player2->SetPosition((SCREEN_WIDTH/2)-45, 68);

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH/2), (SCREEN_HEIGHT/2 -15));

	_gameObjectManager.Add("GameBall", ball);
	_gameObjectManager.Add("Paddle1", player1);
	_gameObjectManager.Add("Paddle2", player2);

	_gameState = Game::Playing;
	 

	while(!IsExiting()) 
	{
		GameLoop();
	}
	_mainWindow.Close();
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Input& Game::GetInput() 
{
	return _mainWindow.GetInput();
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}


bool Game::IsExiting() {
	if( _gameState == Game::Exiting )
		return true;
	else
		return false;
}

void Game::GameLoop() {
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);

	switch(_gameState) 
	{
	case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
	case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
	case Game::Playing:
		{
			_mainWindow.Clear(sf::Color(0, 0, 0));

			_gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);

			_mainWindow.Display();
			if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.Type == sf::Event::KeyPressed) {
				if (currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
			}
			break;
		}
	}
}

void Game::ShowSplashScreen() {
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu() {
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result) {
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
