#include "stdafx.h"
#include "SplashScreen.h"


void SplashScreen::Show(sf::RenderWindow& renderWindow) {
	sf::Image image;
	if(image.LoadFromFile("C:\\Users\\Alex\\Documents\\Visual Studio 2010\\Projects\\PANG\\Debug\\images\\SplashScreen.png") != true)
		return;
	sf::Sprite sprite(image);

	renderWindow.Draw(sprite);
	renderWindow.Display();

	sf::Event event;
	sf::Clock clock;
	clock.Reset();
	/*while(true) 
	{
		renderWindow.GetEvent(event);
		if(event.Type == sf::Event::KeyPressed
			|| event.Type == sf::Event::MouseButtonPressed
			|| event.Type == sf::Event::Closed)			
		{
			return;
		}
	} */
	while (true) {
		if (clock.GetElapsedTime() >= 2.0f)
			return;
	}
}

