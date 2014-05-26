#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window) {
	sf::Image image;
	image.LoadFromFile("C:\\Users\\Alex\\Documents\\Visual Studio 2010\\Projects\\PANG\\Debug\\images\\MenuButtons.png");
	sf::Sprite sprite(image);


	MenuItem playButton;
	playButton.rect.Top = 0;
	playButton.rect.Bottom = 364;
	playButton.rect.Left = 0;
	playButton.rect.Right = 1024;
	playButton.action = Play;

	MenuItem exitButton;
	exitButton.rect.Top = 372;
	exitButton.rect.Bottom = 768;
	exitButton.rect.Left=0;
	exitButton.rect.Right=1024;
	playButton.action = Exit;


	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.Draw(sprite);
	window.Display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y) {
	std::list<MenuItem>::iterator it;

	for( it = _menuItems.begin(); it != _menuItems.end(); it++) {
		sf::Rect<int> menuRect = (*it).rect;
		if(menuRect.Top < y &&
			menuRect.Bottom > y &&
			menuRect.Left < x &&
			menuRect.Right > x) 
		{
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window) {
	sf::Event menuEvent;
	
	while(true)
	{	
		window.GetEvent(menuEvent);
		if(menuEvent.Type==sf::Event::MouseButtonPressed)
			return HandleClick(menuEvent.MouseButton.X, menuEvent.MouseButton.Y);
			
		if(menuEvent.Type == sf::Event::Closed)
			return Exit;
		
	}
}

