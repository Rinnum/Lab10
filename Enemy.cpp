#include "Enemy.h"

void Enemy::initenemySprite()
{
	//Resize the enemy
	this->enemySprite.setScale(0.05f, 0.05f);
	this->bossSprite.setScale(0.1f, 0.1f);
}

void Enemy::initVariable()
{
	//this->enemySpawnTimer = 100.f;
	//this->enemySpawnTimer = this->enemySpawnTimerMax;
	//this->maxEnemies = 10;

	this->hpMax  = 100;
	this->hp     = this->hpMax;
	this->pointkill = 50;
	this->pointattrack = 20;
	this->damage = 10;
}

Enemy::Enemy(float pos_x,float pos_y,Texture* enemyTexture)
{

	this->initenemySprite();
	this->enemySprite.setPosition(pos_x, pos_y);
	this->enemySprite.setTexture(*enemyTexture);
	this->initVariable();
}

Enemy::~Enemy()
{

}



//Function

void Enemy::update()
{
	this->enemySprite.move(0.f, 2.f);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemySprite);
}

