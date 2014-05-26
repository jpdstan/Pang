#pragma once
#include "GameBall.h"
#include "stdafx.h"

class ScoreBoard : public VisibleGameObject {
public:
	ScoreBoard();
	~ScoreBoard();
	void Score(bool IsBot);


private:
	int _p1Score;
	int _p2Score;
	sf::String _p1;
	sf::String _p2;

};