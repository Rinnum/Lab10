#include "Game.h"

//Private function
void Game::initVariables()
{
	this->window = nullptr;
	this->level = 1;
	this->count = 0;

}

void Game::initWindow() //ย้ายไปmain
{
	this->bgTexture.loadFromFile("character/bg.png");
	this->bgSprite.setTexture(bgTexture);
}

void Game::initPlayer()
{
	this->playerTexture.loadFromFile("character/player1.png");
	this->bulletTexture.loadFromFile("character/bullet.png");
	this->player.push_back(Player(&this->playerTexture, &this->bulletTexture));
}

void Game::initEnemies()
{
	this->enemyTexture.loadFromFile("character/enemy1.png");
	this->bossTexture.loadFromFile("character/enemy2.png");
	this->spawmTimerMax = 50.f;
	this->spawmTimer = this->spawmTimerMax;
	this->maxEnemies = 10;
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initEnemies();

}

Game::~Game()
{

}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}


//Function

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		if (ev.Event::type == Event::Closed)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == Keyboard::Escape)
			this->window->close();
	}
}



void Game::updateEnemies(int playerIndex)
{
		if (this->spawmTimer >= this->spawmTimerMax)
		{
			this->enemies.push_back(Enemy(rand() % this->window->getSize().x - 100.f, -100.f, &this->enemyTexture));
			this->spawmTimer = 0.f;
		}
		else
		{
			this->spawmTimer += 0.5f;
		}
		for (int x = 0; x < this->enemies.size(); x++)
		{
			this->enemies[x].update();

			if (enemies[x].getGlobalBounds().intersects(player[playerIndex].getGlobalBounds()))
			{
				int damage = enemies[x].getDamage(); //damage enemy
				int pointattrack = enemies[x].getDamage(); //-point player
				player[playerIndex].takeDamage(damage, pointattrack); //ส่งค่าคืนplayer
				this->enemies.erase(this->enemies.begin() + x);
				break;
			}
			//Remove enemy at bottom of screen
			if (this->enemies[x].getPos().y > this->window->getSize().y)
			{
				this->enemies.erase(this->enemies.begin() + x);
				break;
			}
		}
}

void Game::updateCombat(int playerIndex, float deltaTime)
{
	//ยิงหาย
	for (size_t k = 0; k < player[playerIndex].getBullets().size(); k++)
	{
		player[playerIndex].getBullets()[k].update(deltaTime);
		for (int j = 0; j < enemies.size(); j++)
		{
			if (player[playerIndex].getBullets()[k].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
			{
				int pointkill = enemies[j].takePoint(); //+point player
				player[playerIndex].getPoint(pointkill);
				player[playerIndex].getBullets().erase(player[playerIndex].getBullets().begin() + k);
				enemies.erase(enemies.begin() + j);
				count++;
				break;
			}
		}
	}

}

void Game::levelUp()
{
	this->level++ ;
	this->maxEnemies = maxEnemies*level;
	for (int h = 0; h < player.size(); h++)
	{
		player[h].setHp();

		cout << "Hp " << player[h].getHp() << endl;
	}
	if (level == 2)
	{
		this->bgTexture.loadFromFile("character/bg1.png");
		this->bgSprite.setTexture(bgTexture);
	}
	else if (level == 3)
	{
		this->bgTexture.loadFromFile("character/bg2.png");
		this->bgSprite.setTexture(bgTexture);
	}
	else if (level == 4)
	{
		this->bgTexture.loadFromFile("character/bg3.png");
		this->bgSprite.setTexture(bgTexture);
	}
}



void Game::update(float deltaTime)
{
	this->pollEvents();
	printf("level ");
	cout << this->level << endl;
	printf("maxenemies ");
	cout << this->maxEnemies << endl;
	cout << "count " << count << endl;

	if (count == this->maxEnemies)
	{
		levelUp();
	}

	for (size_t i = 0; i < this->player.size(); i++)
	{
		this->player[i].update(deltaTime);
		this->updateCombat(i, deltaTime);
		this->updateEnemies(i);

		printf("point");
		cout << this->player[i].getPoint() << endl;
		printf("Hp");
		cout << this->player[i].getHp() << endl;
		
	}

	// cout << deltaTime << endl;
}




void Game::render()
{
	/*
	   @return void

		-clear old frame
		-Render new object
		-display frame in Wiondow
		Render the game objects.
	*/

	this->window->clear();
	//Draw Game Objects
	this->window->draw(this->bgSprite);
	for (size_t i = 0; i < this->player.size(); i++)
	{
		this->player[i].render(*this->window);
	}
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].render(*this->window);
	}

	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies.at(i).render(this->window);
	}
	this->window->display();
}


