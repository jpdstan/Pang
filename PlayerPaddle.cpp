#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle(bool isBot) :
_velocity(0),
_maxVelocity(600.0f)
{
	Load("C:\\Users\\Alex\\Documents\\Visual Studio 2010\\Projects\\PANG\\Debug\\images\\paddle.png");


	GetSprite().SetCenter(GetSprite().GetSize().x/2, GetSprite().GetSize().y/2);

	_isBot = isBot;
}
PlayerPaddle::~PlayerPaddle() {}

void PlayerPaddle::Draw(sf::RenderWindow& rw) {
	VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const {
	return _velocity;
}

void PlayerPaddle::Update(float elapsedTime) {
	if(_isBot) 
	{
		if(Game::GetInput().IsKeyDown(sf::Key::Left))
			_velocity -= 3.0f;
		if(Game::GetInput().IsKeyDown(sf::Key::Right))
			_velocity +=3.0f;
		if(Game::GetInput().IsKeyDown(sf::Key::Down))
			_velocity= 0.0f;

		if(_velocity > _maxVelocity)
			_velocity = _maxVelocity;
		if(_velocity < -_maxVelocity)
			_velocity = -_maxVelocity;

		sf::Vector2f pos = this->GetPosition();

		if(pos.x < GetSprite().GetSize().x/2 || 
		   pos.x > (Game::SCREEN_WIDTH - GetSprite().GetSize().x/2))
		{
			_velocity = -_velocity;
		}

		GetSprite().Move(_velocity * elapsedTime, 0);
	}

	else if(!_isBot)
	{
		if(Game::GetInput().IsKeyDown(sf::Key::Z))
			_velocity -= 3.0f;
		if(Game::GetInput().IsKeyDown(sf::Key::C))
			_velocity +=3.0f;
		if(Game::GetInput().IsKeyDown(sf::Key::X))
			_velocity= 0.0f;

		if(_velocity > _maxVelocity) _velocity = _maxVelocity;
		if(_velocity < -_maxVelocity) _velocity = -_maxVelocity;

		sf::Vector2f pos = this->GetPosition();

		if(pos.x < GetSprite().GetSize().x/2 || 
		   pos.x > (Game::SCREEN_WIDTH - GetSprite().GetSize().x/2))
		{
			_velocity = -_velocity;
		}

		GetSprite().Move(_velocity * elapsedTime, 0);
	}
}