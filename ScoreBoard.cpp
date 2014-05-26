#include "ScoreBoard.h"
#include "Game.h"


ScoreBoard::ScoreBoard() {
	_p1(0, sf::Font.GetDefaultFont(), 30.0f);
	_p2(0, sf::Font.GetDefaultFont(), 30.0f);
	_p1.SetPosition(Game::SCREEN_WIDTH/2 - 30, Game::SCREEN_HEIGHT/2);
	_p2.SetPosition(Game::SCREEN_WIDTH/2 + 30, Game::SCREEN_HEIGHT/2);
	_p2.SetColor(sf::Color::White);
	_p1.SetColor(sf::Color::White);

	_p1.SetText(0);
	_p2.SetText(0);
}

ScoreBoard::~ScoreBoard() {}


void ScoreBoard::Score(bool isBot) {
	
	if(isBot) {
		_p2Score +=1;

		sf::Unicode::Text number = new sf::Unicode::Text(_p2Score);
		_p2.SetText(number);
	}

	else if(!isBot) {
		_p1Score +=1;
		_p1.SetText(_p1Score);
	}
}

int _p1Score = 0;

