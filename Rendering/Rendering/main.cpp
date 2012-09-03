#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "Collision.hpp"
#include <iostream>

int x; //Used to store copies of sprite location if collision() == true
int y;

int main()
{
	//Create window, and limit frame rate
	sf::RenderWindow window (sf::VideoMode(800, 600, 32), "Game", sf::Style::Default);
	window.setFramerateLimit(60);

//------------------------TEXTURES------------------------------

	//Declare textures
	sf::Texture texture;
	sf::Texture texture1;
	sf::Texture texture2;
	//Load image
	if(!texture.loadFromFile("Sprites/main.png"))
	{
		return 1;
	}
	if(!texture1.loadFromFile("Sprites/background.png"))
	{
		return 1;
	}
	if(!texture2.loadFromFile("Sprites/house.png"))
	{
		return 1;
	}

//------------------------SPRITES--------------------------

	//Creates and places the sprites
	sf::Sprite sprite;
	sf::Sprite background;
	sf::Sprite house;
	sprite.setPosition(400, 300);
	background.setPosition(0, 0);
	house.setPosition(440, 300);

	//Loads texture into sprite
	sprite.setTexture(texture);
	background.setTexture(texture1);
	house.setTexture(texture2);

//-------------------------RECTANGLES--------------------------------

	//Declares the rectangles
	sf::IntRect front(1, 1, 18, 24);
	sf::IntRect back (20, 1, 18, 24);
	sf::IntRect left (20, 26, 18, 24);
	sf::IntRect right (1, 26, 18, 24);
	//Steps
	sf::IntRect frontLeft(39, 1, 18, 24);
	sf::IntRect frontRight(39, 26, 18, 24);
	sf::IntRect backLeft();
	sf::IntRect backRight();
	sf::IntRect leftLeft();
	sf::IntRect leftRight();
	sf::IntRect rightLeft();
	sf::IntRect rightRight();

	sf::IntRect backgroundRect (0, 0, 800, 600);

	sf::IntRect houseRect (0, 0, 17, 22);

	
	//Crop sprites using rectangles defined above
	sprite.setTextureRect(front);
	background.setTextureRect(backgroundRect);
	house.setTextureRect(houseRect);

//-----------------------SOUND------------------------------------------------------

	//Declare the Sound Buffer
	sf::SoundBuffer footstepsBuffer;
	sf::SoundBuffer bumpBuffer;
	//Loads the sound file
	if(!footstepsBuffer.loadFromFile("Sounds/footsteps.wav"))
	{
		return 1;
	}
	if(!bumpBuffer.loadFromFile("Sounds/bump.wav"))
	{
		return 1;
	}

	//Declare sound
	sf::Sound footsteps;
	sf::Sound bump;
	//Load Buffer into Sound
	footsteps.setBuffer(footstepsBuffer);
	bump.setBuffer(bumpBuffer);

//-------------------------------MAIN-----------------------------

	//Main window loop
	while(window.isOpen())
	{
		sf::Event event;

		//Vectors used for collision
		sf::Vector2i spritePosition(sprite.getPosition());
		sf::Vector2i backgroundPosition(background.getPosition());
		sf::Vector2i housePosition(house.getPosition());

		//Sprite Vectors
		sf::Vector2i backVector(back.width, back.height);
		sf::Vector2i frontVector(front.width, front.height);
		sf::Vector2i rightVector(right.width, right.height);
		sf::Vector2i leftVector(left.width, left.height);

		//House Vectors
		sf::Vector2i houseVector(houseRect.width, houseRect.height);

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}

			if(event.key.code == sf::Keyboard::Insert)
			{
				sf::Image screenshot = window.capture();
				screenshot.saveToFile("Screenshot.png");
			}
		}

//-----------------------------------MOVEMENT----------------------------------------

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			//Change to stepping sprite
			Sleep(250);
			sprite.setTextureRect(back);
			sprite.move(0, -24);
			//Redeclaring the collision textures
			sf::Vector2i spritePosition(sprite.getPosition());
			sf::Vector2i housePosition(house.getPosition());
			if(collision(spritePosition, backVector, housePosition, houseVector) == true)
			{
				sprite.move(0, 24);
				bump.play();
			}
			else
			{
				footsteps.play();
			}
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			//Change to stepping sprite
			Sleep(250);
			sprite.setTextureRect(front);
			sprite.move(0, 24);
			//Redeclaring the collision textures
			sf::Vector2i spritePosition(sprite.getPosition());
			sf::Vector2i housePosition(house.getPosition());
			if(collision(spritePosition, frontVector, housePosition, houseVector) == true)
			{
				sprite.move(0, -24);
				bump.play();
			}
			else
			{
				footsteps.play();
			}
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//Change to stepping sprite
			Sleep(250);
			sprite.setTextureRect(right);
			sprite.move(19, 0);
			//Redeclaring the collision textures
			sf::Vector2i spritePosition(sprite.getPosition());
			sf::Vector2i housePosition(house.getPosition());
			if(collision(spritePosition, leftVector, housePosition, houseVector) == true)
			{
				sprite.move(-19, 0);
				bump.play();
			}
			else
			{
				footsteps.play();
			}
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//Change to stepping sprite
			Sleep(250);
			sprite.setTextureRect(left);
			sprite.move(-19, 0);
			//Redeclaring the collision textures
			sf::Vector2i spritePosition(sprite.getPosition());
			sf::Vector2i housePosition(house.getPosition());
			if(collision(spritePosition, rightVector, housePosition, houseVector) == true)
			{
				sprite.move(19, 0);
				bump.play();
			}
			else
			{
				footsteps.play();
			}
		}

		//Draw sequence
		window.clear(); //(Red, Green, Blue, (optional) Alpha) Alpha is transperency

		//Draw....

		window.draw(background);

		window.draw(house);

		window.draw(sprite);

		window.display();

		std::cout << x << std::endl;
		std::cout << y << std::endl;
	}
	return 0;
}