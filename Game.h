#pragma once
#include<iostream>
#include<vector>
#include"Player.h"
#include"Enemy.h"
#include "Bullet.h"
#include"Scene.h"
#include<ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
/*
	Class that acts the game engine
*/

class Game : public Scene
{
private:
	//Window
	RenderWindow* window;
	RectangleShape bg;
	Texture bgTexture;
	Sprite bgSprite;
	Event ev;

	//Bullet
	vector<Bullet> bullets;

	//Player
	Texture playerTexture;
	vector<Player> player;

	//Enemies
	float spawmTimer;
	float spawmTimerMax;
	int maxEnemies;


	vector<Enemy> enemies;
	Texture enemyTexture; 
	Texture bossTexture;
	Texture bulletTexture;

	int level;
	int count;


	//Private function
	void initVariables();
	void initWindow();

	void initPlayer();
	void initEnemies();

public:
	//Constructor/Destructors
	Game();
	virtual ~Game();
	inline void setWindow(RenderWindow* window) { this->window = window; }

	//Accessors
	const bool running() const;


	//Function 
	void pollEvents();
	void updateEnemies(int playerIndex);
	void updateCombat(int playerIndex, float deltaTime);
	void levelUp();
	void update(float deltaTime);
	void render();
};
