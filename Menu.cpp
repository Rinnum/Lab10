#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Fonts/Cheeky_Rabbit.ttf"))
		printf("Can't load");


	window = nullptr;

	//Play
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("PLAY");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setCharacterSize(200);
	menu[0].setPosition(Vector2f(width / 2, height / (Max_menu + 1) * 1));

	//Score
	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("SCORE");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setCharacterSize(100);
	menu[1].setPosition(Vector2f(width / 2, height / (Max_menu + 1) * 2));

	//EXIT
	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("EXIT");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setCharacterSize(100);
	menu[2].setPosition(Vector2f(width / 2, height / (Max_menu + 1) * 3));

	mainMenuSelected = 0;
}

void Menu::update(float deltaTime)
{
	pollEvent();
	this->bgTexture.loadFromFile("character/bg.png");
	this->bgSprite.setTexture(bgTexture);

}

Menu::~Menu()
{

}

void Menu::pollEvent()
{
	Event ev;
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case Event::KeyReleased:
			switch (ev.key.code)
			{
			case Keyboard::Up:
				moveUp();
				break;
			case Keyboard::Down:
				moveDown();
				break;
			case Keyboard::Enter:
				select();
				break;
			}
			break;
		case  Event::Closed:
			window->close();
			break;
		}
	}
}


void Menu::render()
{
	for (int i = 0; i < 3; i++)
	{
		window->draw(menu[i]);
	}

}


void Menu::moveUp()
{
	if (mainMenuSelected - 1 >= -1)
	{
		menu[mainMenuSelected].setFillColor(Color::White);

		mainMenuSelected--;
		if (mainMenuSelected == -1)
		{
			mainMenuSelected = 2;
		}
		menu[mainMenuSelected].setFillColor(Color::Red);

	}
}

void Menu::moveDown()
{

	if (mainMenuSelected + 1 <= Max_menu)
	{
		menu[mainMenuSelected].setFillColor(Color::White);

		mainMenuSelected++;
		if (mainMenuSelected == 3)
		{
			mainMenuSelected = 0;
		}
		menu[mainMenuSelected].setFillColor(Color::Red);
	}
}

void Menu::select()
{
	if (mainMenuSelected = 0)
	{
		sceneIndex = 1;
	}
}