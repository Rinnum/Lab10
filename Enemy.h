#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <iostream>

using namespace sf;

class Enemy
{
private:

	//Game logic
	//float enemySpawnTimer;
	//float enemySpawnTimerMax;
	//int maxEnemies;

	int hp;
	int hpMax;
	int damage;
	int pointattrack;
	int pointkill;
	//Game objects
	//enemy
	Texture* enemyTexture;
	Sprite enemySprite;

	Texture* bossTexture;
	Sprite bossSprite;

	void initenemySprite();
	void initVariable();




public:
	Enemy(float pos_x, float pos_y, Texture* enemyTexture);
	virtual ~Enemy();
	inline int getDamage() { return this->damage, this->pointattrack;}
	inline int takePoint() { return this->pointkill; }


	//Accessor
	inline Vector2f getPos()
	{
		return this->enemySprite.getPosition();
	}
	inline FloatRect getGlobalBounds() const {return this->enemySprite.getGlobalBounds();}
	

	//Function

	void update();
	void render(RenderTarget* target);

};


#endif //ENEMY_H