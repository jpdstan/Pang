
#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"


GameBall::GameBall() :
_velocity(230.0f),
_elapsedTimeSinceStart(0.0f)
{
	Load("C:\\Users\\Alex\\Documents\\Visual Studio 2010\\Projects\\PANG\\Debug\\images\\ball.png");

	GetSprite().SetCenter(15,15);

	sf::Randomizer::SetSeed(std::clock());
	_angle = (float)sf::Randomizer::Random(0,360);

}

GameBall::~GameBall() {}

void GameBall::Update(float elapsedTime)
{
	
	_elapsedTimeSinceStart += elapsedTime;

	// Delay game from starting until 3 seconds have passed
	if(_elapsedTimeSinceStart < 3.0f)
		return;

	float moveAmount = _velocity  * elapsedTime;
	
	
	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;

	
	//collide with the left side of the screen
	if(GetPosition().x + moveByX + GetWidth()/2 <= 0|| 
	   GetPosition().x + GetHeight()/2 + moveByX >= Game::SCREEN_WIDTH)
	{
		//Ricochet!
		_angle = 360.0f - _angle;
		if(_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
		if(_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
		moveByX = -moveByX;
	}
	


	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
	PlayerPaddle* player2 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle2"));
	if(player1 != NULL || player2 != NULL)
	{
		sf::Rect<float> p1BB = player1->GetBoundingRect();
		sf::Rect<float> p2BB = player2->GetBoundingRect();
	
		if(p1BB.Intersects(GetBoundingRect()))       //(GetPosition().x + moveByX + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveByY))
		{ 
			_angle =  360.0f - (_angle - 180.0f);
			if(_angle > 360.0f) _angle -= 360.0f;
		 
			moveByY = -moveByY;

			// Make sure ball isn't inside paddle
			if(GetBoundingRect().Bottom > player1->GetBoundingRect().Top)
			{
				SetPosition(GetPosition().x,player1->GetBoundingRect().Top - GetWidth()/2 -1 );
			}
			
			// Now add "English" based on the players velocity.  
			float playerVelocity = player1->GetVelocity();
		
			if(playerVelocity < 0)
			{
				// moving left
				_angle -= 20.0f;
				if(_angle < 0 ) _angle = 360.0f - _angle;
			}
			else if(playerVelocity > 0)
			{
				_angle += 20.0f;
				if(_angle > 360.0f) _angle = _angle - 360.0f;
			}

			_velocity += 5.0f;
		}

		else if(p2BB.Intersects(GetBoundingRect())) 
		{ 
			_angle =  360.0f - (_angle - 180.0f);
			if(_angle > 360.0f) _angle -= 360.0f;
		 
			moveByY = -moveByY;

			// Make sure ball isn't inside paddle
			if(GetBoundingRect().Top > player2->GetBoundingRect().Bottom)
			{
				SetPosition(GetPosition().x,player2->GetBoundingRect().Bottom - GetWidth()/2 -1 );
			}

			// Now add "English" based on the players velocity.  
			float playerVelocity = player2->GetVelocity();
		
			if(playerVelocity < 0)
			{
				// moving left
				_angle -= 20.0f;
				if(_angle < 0 ) _angle = 360.0f - _angle;
			}
			else if(playerVelocity > 0)
			{
				_angle += 20.0f;
				if(_angle > 360.0f) _angle = _angle - 360.0f;
			}

			_velocity += 5.0f;
		}



	
		//if(GetPosition().y - GetSprite().GetSize().y/2 - moveByY <= 0 || GetPosition().y + GetSprite().GetSize().y/2 + moveByY >= Game::SCREEN_HEIGHT)
		if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT || GetPosition().y - GetHeight()/2 + moveByY<= 0)
		{
			// move to middle of the screen for now and randomize angle
			Reset();
		}

		
		GetSprite().Move(moveByX,moveByY);
	}
}

float GameBall::LinearVelocityX(float angle) {
	angle-=90;
	if(angle < 0) angle += 360;
	float xMovement = (float) (std::cos(angle * (3.1415 / 180.0f)));
	return xMovement;
}

float GameBall::LinearVelocityY(float angle) {
	angle -= 90;
	if(angle <0) angle += 360;
	float yMovement = (float) (std::sin(angle * (3.1415 /180.0f)));
	return yMovement;
}

void GameBall::Reset() {
	GetSprite().SetPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
	_angle = (float)sf::Randomizer::Random(0,360);
	_velocity = 220.0f;
	_elapsedTimeSinceStart = 0.0f;

}



