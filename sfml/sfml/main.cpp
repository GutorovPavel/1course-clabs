#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <stdlib.h>
#include "level.h"

using namespace sf;

class Entity
{
public:
	std::vector<Object> obj;
	float dx, dy, x, y, speed;
	int w, h, health, randomDir;
	bool life, isMove = false;
	Texture texture;
	Sprite sprite;
	String filename;
	Entity(Image& image, String File, float X, float Y, int W, int H)
	{
		x = X; y = Y; w = W; h = H; filename = File;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
	virtual void Update(float time) = 0;
	FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}
};
class Player : public Entity
{
public:
	enum { left, right, up, down } dir;
	bool isShoot = false;

	Player(Image& image, String File, Level & lvl, float X, float Y, float W, float H) : Entity(image, File, X, Y, W, H)
	{
		obj = lvl.GetAllObjects();
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	void InteractionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)
		{
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
				if (obj[i].name == "flower" && health < 100)
				{
					health += 100 - health;
					obj[i].name = "solid";
				}
			}
		}
	}
	void Movement()
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			dir = left; speed = 0.15;
			sprite.setTextureRect(IntRect(0, 0, 80, 80));
			isMove = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			dir = right; speed = 0.15;
			sprite.setTextureRect(IntRect(0, 80, 80, 80));
			isMove = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			dir = up; speed = 0.15;
			sprite.setTextureRect(IntRect(0, 160, 80, 80));
			isMove = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			dir = down; speed = 0.15;
			sprite.setTextureRect(IntRect(0, 240, 80, 80));
			isMove = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && isMove) 
		{
			isShoot = true; 
		}
	}
	void Update(float time)
	{
		Movement();
		switch (dir)
		{
		case right: dx = speed; dy = 0; break;
		case left: dx = -speed; dy = 0; break;
		case up: dx = 0; dy = -speed; break;
		case down: dx = 0; dy = speed; break;
		}

		
		x += dx * time;
		InteractionWithMap(dx, dy);
		
		y += dy * time;
		InteractionWithMap(dx, dy);

		speed = 0;

		if (health <= 0)
		{
			life = false;
			speed = 0;
			if (dir == right || dir == left)
				sprite.setTextureRect(IntRect(240, 0, 80, 80));
			else sprite.setTextureRect(IntRect(240, 160, 80, 80));
			sprite.setPosition(x, y);
		}
		else sprite.setPosition(x, y);
	}
	float GetPlayerCoordinateX()
	{
		return x;
	}
	float GetPlayerCoordinateY()
	{
		return y;
	}
};
class Bullet : public Entity
{
public:
	int dirForBullet;
	Bullet(Image& image, String File, Level & lvl, float X, float Y, int W, int H, int dir) : Entity(image, File, X, Y, W, H)
	{
		obj = lvl.GetObjects("solid");
		x = X; y = Y; dirForBullet = dir;
		speed = 0.4;
		w = h = 30;
		life = true;
	}
	
	void Update(float time)
	{
		switch (dirForBullet)
		{
		case 1:
		{
			dx = speed; dy = 0;
			sprite.setTextureRect(IntRect(0, 0, 30, 30));
			break;
		}
		case 0:
		{
			dx = -speed; dy = 0;
			sprite.setTextureRect(IntRect(0, 90, 30, 30));
			break;
		}
		case 2:
		{
			dx = 0; dy = -speed;
			sprite.setTextureRect(IntRect(0, 60, 30, 30));
			break;
		}
		case 3:
		{
			dx = 0; dy = speed;
			sprite.setTextureRect(IntRect(0, 30, 30, 30));
			break;
		}
		}

		x += dx * time;
		y += dy * time;

		for (int i = 0; i < obj.size(); i++)
		{
			if (getRect().intersects(obj[i].rect))
			{
				life = false;
			}
		}
		sprite.setPosition(x + w / 2 + 9, y + h / 2 + 10);
	}
};
class Enemy : public Entity
{
public:
	bool isShoot = false; 

	Enemy(Image& image, String File, Level & lvl, float X, float Y, float W, float H, int RandomDir) : Entity(image, File, X, Y, W, H)
	{
		obj = lvl.GetObjects("solid");
		if (filename == "Enemy1")
		{
			sprite.setTextureRect(IntRect(80, 0, w, h));
			speed = 0.09; health = 140;
			dx = speed;
			randomDir = RandomDir;
		}
		if (filename == "Enemy2")
		{
			sprite.setTextureRect(IntRect(160, 0, w, h));
			speed = 0.08; health = 240;
			dx = speed;
			randomDir = RandomDir;
		}
	}
	void InteractionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i < obj.size(); i++)
		{
			if (getRect().intersects(obj[i].rect))
			{
				if (Dy > 0) { y = obj[i].rect.top - h; randomDir = rand() % 4; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; randomDir = rand() % 4; }
				if (Dx > 0) { x = obj[i].rect.left - w; randomDir = rand() % 4; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; randomDir = rand() % 4; }
			}
		}
	}
	void Update(float time)
	{
		if (filename == "Enemy1")
		{
			switch (randomDir)
			{
			case 1: dx = speed; dy = 0; sprite.setTextureRect(IntRect(80, 80, 80, 80)); break;
			case 0: dx = -speed; dy = 0; sprite.setTextureRect(IntRect(80, 0, 80, 80)); break;
			case 2: dx = 0; dy = -speed; sprite.setTextureRect(IntRect(80, 160, 80, 80)); break;
			case 3: dx = 0; dy = speed; sprite.setTextureRect(IntRect(80, 240, 80, 80)); break;
			}
		}
		if (filename == "Enemy2")
		{
			switch (randomDir)
			{
			case 1: dx = speed; dy = 0; sprite.setTextureRect(IntRect(160, 80, 80, 80)); break;
			case 0: dx = -speed; dy = 0; sprite.setTextureRect(IntRect(160, 0, 80, 80)); break;
			case 2: dx = 0; dy = -speed; sprite.setTextureRect(IntRect(160, 160, 80, 80)); break;
			case 3: dx = 0; dy = speed; sprite.setTextureRect(IntRect(160, 240, 80, 80)); break;
			}
		}


		x += dx * time;
		InteractionWithMap(dx, dy);
		
		y += dy * time;
		InteractionWithMap(dx, dy);
		
		sprite.setPosition(x, y);
	}
};
class PrintText
{
public:
	String message;
	float x, y, scale;
	PrintText(RenderWindow& window, String M, float X, float Y, float Scale)
	{
		message = M; x = X; y = Y; scale = Scale;
		Font font;
		font.loadFromFile("Fallouty.ttf");
		Text text("", font, scale);
		text.setString(message);
		text.setPosition(x, y);
		window.draw(text);
	}
};

class Game
{
public:
	bool isMenu = true, menuStart = true;
	Music music;
	Music drive;

	void Menu(RenderWindow& window)
	{
		window.setMouseCursorVisible(true);

		drive.stop();
		music.setVolume(60);


		Texture background, name, start, exitImage;

		background.loadFromFile("images/back.png");
		start.loadFromFile("images/start.png");
		name.loadFromFile("images/name.png");
		exitImage.loadFromFile("images/exit.png");

		Sprite sBackground, sName, sStart, sExit;

		sBackground.setTexture(background);
		sBackground.setPosition(0, 0);

		sName.setTexture(name);
		sName.setPosition(0, 120);

		sStart.setTexture(start);
		sStart.setPosition(0, 400);

		sExit.setTexture(exitImage);
		sExit.setPosition(0, 460);

		int choice;

		while (isMenu, menuStart)
		{
			choice = 0;
			sStart.setColor(Color::White);
			sExit.setColor(Color::White);
			if (IntRect(0, 400, 1000, 50).contains(Mouse::getPosition(window)))
			{
				sStart.setColor(Color::Green);
				choice = 1;
			}
			if (IntRect(0, 460, 1000, 50).contains(Mouse::getPosition(window)))
			{
				sExit.setColor(Color::Green);
				choice = 2;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (choice)
				{
				case 1: { isMenu = false; menuStart = false; GameStart(window); break; }
				case 2: { exit(0); break; }
				default: { continue; }
				}
			}

			window.draw(sBackground);
			window.draw(sName);
			window.draw(sStart);
			window.draw(sExit);
			window.display();
		}
	}
	void MenuPause(RenderWindow& window)
	{
		Texture background, restart, exit;

		background.loadFromFile("images/back3.png");
		restart.loadFromFile("images/restart.png");
		exit.loadFromFile("images/exit2.png");

		Sprite sBackground, sRestart, sExit;

		sBackground.setTexture(background);
		sBackground.setPosition(200, 200);

		sRestart.setTexture(restart);
		sRestart.setPosition(200, 460);

		sExit.setTexture(exit);
		sExit.setPosition(200, 520);

		bool isMenu = true;
		int choice;

		while (isMenu)
		{
			window.setMouseCursorVisible(true);
			choice = 0;
			sRestart.setColor(Color::White);
			sExit.setColor(Color::White);
			if (IntRect(0, 0, 1000, 490).contains(Mouse::getPosition(window)))
			{
				sRestart.setColor(Color::Green);
				choice = 1;
			}
			if (IntRect(0, 520, 1000, 1000).contains(Mouse::getPosition(window)))
			{
				sExit.setColor(Color::Green);
				choice = 2;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (choice)
				{
				case 1: { isMenu = false; GameStart(window); window.setMouseCursorVisible(false); break; }
				case 2: { isMenu = false; menuStart = true;  Menu(window); break; }
				default: { continue; }
				}
			}

			window.draw(sBackground);
			window.draw(sRestart);
			window.draw(sExit);
			window.display();
		}
	}
	void MenuDeath(RenderWindow& window)
	{
		music.setVolume(60);
		Texture background, restart, exit;

		background.loadFromFile("images/back2.png");
		restart.loadFromFile("images/restart.png");
		exit.loadFromFile("images/exit2.png");

		Sprite sBackground, sRestart, sExit;

		sBackground.setTexture(background);
		sBackground.setPosition(200, 200);

		sRestart.setTexture(restart);
		sRestart.setPosition(200, 460);

		sExit.setTexture(exit);
		sExit.setPosition(200, 520);

		bool isMenu = true;
		int choice;

		while (isMenu)
		{
			window.setMouseCursorVisible(true);
			choice = 0;
			sRestart.setColor(Color::White);
			sExit.setColor(Color::White);
			if (IntRect(0, 0, 1000, 490).contains(Mouse::getPosition(window)))
			{
				sRestart.setColor(Color::Green);
				choice = 1;
			}
			if (IntRect(0, 520, 1000, 1000).contains(Mouse::getPosition(window)))
			{
				sExit.setColor(Color::Green);
				choice = 2;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (choice)
				{
				case 1: { isMenu = false; GameStart(window); window.setMouseCursorVisible(false); break; }
				case 2: { isMenu = false; menuStart = true;  Menu(window); break; }
				default: { continue; }
				}
			}
			window.draw(sBackground);
			window.draw(sRestart);
			window.draw(sExit);
			window.display();
		}
	}
	void MenuWin(RenderWindow& window)
	{
		music.setVolume(60);

		Texture background, restart, congratulation, exit;

		background.loadFromFile("images/back.png");
		congratulation.loadFromFile("images/congratulation.png");
		restart.loadFromFile("images/restart.png");
		exit.loadFromFile("images/exit2.png");

		Sprite sBackground, sRestart, sCongratulation, sExit;

		sBackground.setTexture(background);
		sBackground.setPosition(0, 0);

		sCongratulation.setTexture(congratulation);
		sCongratulation.setPosition(200, 200);

		sRestart.setTexture(restart);
		sRestart.setPosition(200, 460);

		sExit.setTexture(exit);
		sExit.setPosition(200, 520);

		bool isMenu = true;
		int choice;

		while (isMenu)
		{
			window.setMouseCursorVisible(true);			
			choice = 0;
			sRestart.setColor(Color::White);
			sExit.setColor(Color::White);
			if (IntRect(200, 460, 600, 50).contains(Mouse::getPosition(window)))
			{
				sRestart.setColor(Color::Green);
				choice = 1;
			}
			if (IntRect(200, 520, 600, 50).contains(Mouse::getPosition(window)))
			{
				sExit.setColor(Color::Green);
				choice = 2;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (choice)
				{
				case 1: { isMenu = false; GameStart(window); window.setMouseCursorVisible(false); break; }
				case 2: { isMenu = false; menuStart = true;  Menu(window); break; }
				default: { continue; }
				}
			}
			window.draw(sBackground);
			window.draw(sCongratulation);
			window.draw(sRestart);
			window.draw(sExit);
			window.display();
		}
	}
	String map(RenderWindow& window)
	{
		music.setVolume(60);
		Texture background, easy, medium, hard, extreme;

		background.loadFromFile("images/back.png");
		easy.loadFromFile("images/easy.png");
		medium.loadFromFile("images/medium.png");
		hard.loadFromFile("images/hard.png");
		extreme.loadFromFile("images/extreme.png");

		Sprite sBackground, sEasy, sMedium, sHard, sExtreme;

		sBackground.setTexture(background);
		sBackground.setPosition(0, 0);

		sEasy.setTexture(easy);
		sEasy.setPosition(0, 340);

		sMedium.setTexture(medium);
		sMedium.setPosition(0, 400);

		sHard.setTexture(hard);
		sHard.setPosition(0, 460);

		sExtreme.setTexture(extreme);
		sExtreme.setPosition(0, 520);
		
		bool isMenu = true;

		while (isMenu)
		{
			int Diff = 0;
			sEasy.setColor(Color::White);
			sMedium.setColor(Color::White);
			sHard.setColor(Color::White);
			sExtreme.setColor(Color::White);
			if (IntRect(0, 340, 1000, 50).contains(Mouse::getPosition(window)))
			{
				sEasy.setColor(Color::Green);
				Diff = 1;
			}
			if (IntRect(0, 400, 1000, 50).contains(Mouse::getPosition(window)))
			{
				sMedium.setColor(Color::Green);
				Diff = 2;
			}
			if (IntRect(0, 460, 1000, 50).contains(Mouse::getPosition(window)))
			{
				sHard.setColor(Color::Green);
				Diff = 3;
			}
			if (IntRect(0, 520, 1000, 50).contains(Mouse::getPosition(window)))
			{
				sExtreme.setColor(Color::Green);
				Diff = 4;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (Diff)
				{
				case 1: { isMenu = false; return "map1.tmx"; break; }
				case 2: { isMenu = false; return "map2.tmx"; break; }
				case 3: { isMenu = false; return "map3.tmx"; break; }
				case 4: { isMenu = false; return "map4.tmx"; break; }
				default: { continue; }
				}
			}
			window.draw(sBackground);
			window.draw(sEasy);
			window.draw(sMedium);
			window.draw(sHard);
			window.draw(sExtreme);
			window.display();
		}
	}
	
	bool isGame(RenderWindow& window, String & diff)
	{
		Level lvl;
		lvl.LoadFromFile(diff);

		////////////////// SOUND DESIGN /////////////////

		music.setVolume(10);

		drive.openFromFile("game.ogg");
		drive.setVolume(40);
		drive.play();
		drive.setLoop(true);

		SoundBuffer shootBuffer;
		shootBuffer.loadFromFile("shoot.ogg");
		Sound shoot(shootBuffer);
		shoot.setVolume(60);

		SoundBuffer shootBuffer2;
		shootBuffer2.loadFromFile("hit.ogg");
		Sound hit(shootBuffer2);
		hit.setVolume(40);

		SoundBuffer shootBuffer3;
		shootBuffer3.loadFromFile("explosion.ogg");
		Sound explosion(shootBuffer3);
		explosion.setVolume(60);

		////////////////////// IMAGES ////////////////////// 

		Image playerImage;
		playerImage.loadFromFile("images/player.png");

		Image enemy1Image;
		enemy1Image.loadFromFile("images/player.png");

		Image bulletImage;
		bulletImage.loadFromFile("images/bullet.png");

		/////////////////////  PLAYERS /////////////////////

		Object player = lvl.GetObject("player");
		Player p(playerImage, "Player", lvl, player.rect.left, player.rect.top, 80, 80);

		std::list <Entity*> entities;
		std::list <Entity*> ::iterator it2;
		std::list <Entity*> ::iterator it;

		std::vector <Object> e = lvl.GetObjects("enemy1");
		std::vector <Object> e2 = lvl.GetObjects("enemy2");

		int randomDir = 0;

		for (int i = 0; i < e.size(); i++)
		{
			entities.push_back(new Enemy(enemy1Image, "Enemy1", lvl, e[i].rect.left, e[i].rect.top, 80.0, 80.0, randomDir));
		}
		for (int i = 0; i < e2.size(); i++)
		{
			entities.push_back(new Enemy(enemy1Image, "Enemy2", lvl, e2[i].rect.left, e2[i].rect.top, 80.0, 80.0, randomDir));
		}

		Clock clock;
		Clock gameTimeClock;

		int gameTime = 0; int temp = 0, temp1 = 0, tempForEnemy = 0;

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			gameTime = gameTimeClock.getElapsedTime().asSeconds();
			clock.restart();
			time /= 800;

			temp += time; temp1 += time, tempForEnemy += time;

			//////////////////// SOLUTIONS ////////////////////

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				for (it = entities.begin(); it != entities.end(); it++)
				{
					(*it)->dx = 0;
					(*it)->dy = 0;
				}
				MenuPause(window); 
			}
			if (p.life == false)
			{
				for (it = entities.begin(); it != entities.end(); it++)
				{
					(*it)->dx = 0;
					(*it)->dy = 0;
				}
				explosion.play();
				MenuDeath(window);
			}
			if (entities.empty())
			{
				for (it = entities.begin(); it != entities.end(); it++)
				{
					(*it)->dx = 0;
					(*it)->dy = 0;
				}
				MenuWin(window);
			}


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			////////////////////// SHOOTING METHODS ///////////////////////

			if (temp1 > 500)
			{
				if (p.isShoot)
				{
					p.isShoot = false;
					entities.push_back(new Bullet(bulletImage, "Bullet", lvl, p.x, p.y, 30, 30, p.dir));
					shoot.play();
					temp1 = 0;
				}
			}
			 
			for (it = entities.begin(); it != entities.end(); it++)
			{
				if ((*it)->filename == "Enemy1" || (*it)->filename == "Enemy2")
				if (tempForEnemy > 1000)
				{
					if (
						(*it)->dx < 0 && p.x < (*it)->x && ((*it)->y > p.y - 70 && (*it)->y < p.y + 70) ||
						(*it)->dx > 0 && p.x > (*it)->x && ((*it)->y > p.y - 70 && (*it)->y < p.y + 70) ||
						(*it)->dy < 0 && p.y < (*it)->y && ((*it)->x > p.x - 70 && (*it)->x < p.x + 70) ||
						(*it)->dy > 0 && p.y > (*it)->y && ((*it)->x > p.x - 70 && (*it)->x < p.x + 70)
						)
					{
						entities.push_back(new Bullet(bulletImage, "EnemyBullet", lvl, (*it)->x, (*it)->y, 30, 30, (*it)->randomDir));
						tempForEnemy = 0;
					}
				}
			}
			
			for (it = entities.begin(); it != entities.end(); it++)
				for (it2 = entities.begin(); it2 != entities.end(); it2++)
				{
					if
						(
							((*it)->filename == "Enemy1" ||
							(*it)->filename == "Enemy2") &&
							(*it2)->filename == "Bullet" &&
							(*it)->getRect().intersects((*it2)->getRect()) &&
							(*it)->health > 0 
						)
					{
						(*it2)->life = false;
						(*it)->health -= 20;

						hit.setVolume(20);
						hit.play();
\
						std::cout << "HP: " << (*it)->health << "\n";
					}
					if ((*it)->health == 20)   (*it)->sprite.setColor(Color::Red);
					else if ((*it)->health <= 0)   (*it)->life = false;
				}

			for (it = entities.begin(); it != entities.end(); it++)
			{
				if ((*it)->filename == "EnemyBullet" && p.health > 0 && (*it)->getRect().intersects(p.getRect()))
				{
					(*it)->life = false;
					p.health -= 20;

					hit.setVolume(50);
					hit.play();

					std::cout << "YOUR HP: " << p.health << "\n";
				}
				else if (p.health <= 0)   p.life = false;
			}

			///////////////////////// BUILDING MAP ////////////////////////////

			window.clear();

			lvl.Draw(window);

			std::ostringstream playerHealth, printGameTime;
			playerHealth << p.health;
			printGameTime << gameTime;
			PrintText healthMassege(window, "Health: " + playerHealth.str(), 250, 900, 50);
			PrintText gameTimeMessage(window, "Time: " + printGameTime.str(), 600, 900, 50);

			////////////////////////// UPDATE & REACT ///////////////////////////////

			for (it = entities.begin(); it != entities.end();)
			{
				Entity* b = *it;
				b->Update(time);
				if (b->life == false) { it = entities.erase(it); delete b; }
				else it++;
			}

			p.Update(time);
			

			for (it = entities.begin(); it != entities.end(); it++)
			{
				window.draw((*it)->sprite);
			}

			window.draw(p.sprite);
			window.display();
		}
	return true;
	}
	void GameStart(RenderWindow& window)
	{
		String diff = map(window);
		if (isGame(window, diff))
			GameStart(window);
	}
};


int main()
{
	Game game;
	game.music.openFromFile("menu.ogg");
	game.music.play();
	game.music.setLoop(true);
	if (game.menuStart)
	{
		RenderWindow window(VideoMode(1000, 1000), "TANKS 2021");
		game.Menu(window);
		game.menuStart = false;
	}
	return 0;
}