#pragma once
#include "VisibleGameObject.h"

class GameBall : public VisibleGameObject {
public:
	GameBall();
	virtual ~GameBall();
	void Update(float elapsedTime);

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;

	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
	void Reset();

};

