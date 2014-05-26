#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject {
public:
	PlayerPaddle(bool isBot);
	~PlayerPaddle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	
	float GetVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
	bool _isBot;
};

