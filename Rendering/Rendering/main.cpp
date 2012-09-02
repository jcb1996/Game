#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include "Collision.hpp"
#include <iostream>

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
		//Used to store the character's position if collision happens
		int x = sprite.getPosition().x;
		int y = sprite.getPosition().y;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			//saveMovement(sprite.getPosition().x, sprite.getPosition().y);
			//Check for collision
			if(collision(spritePosition, backVector, housePosition, houseVector) == false)
			{
				//Change to stepping sprite
				Sleep(250);
				sprite.setTextureRect(back);
				sprite.move(0, -24);
				footsteps.play();
			}
			else
			{
			bump.play();
			}
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			//Check for collision
			if(collision(spritePosition, frontVector, housePosition, houseVector) == false)
			{
				//Change to stepping sprite
				sprite.setTextureRect(frontLeft);
				sprite.move(0, 12);
				Sleep(125);
				sprite.setTextureRect(front);
				sprite.move(0, 12);
				footsteps.play();
				Sleep(125);
			}
			else
			{
			bump.play();
			}
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//Check for collision
			if(collision(spritePosition, rightVector, housePosition, houseVector) == false)
			{
				//Change to stepping sprite
				Sleep(250);
				sprite.setTextureRect(right);
				sprite.move(19, 0);
				footsteps.play();
			}
			else
			{
			bump.play();
			}
		}

		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//Check for collision
			if(collision(spritePosition, leftVector, housePosition, houseVector) == false)
			{
				//Change to stepping sprite
				Sleep(250);
				sprite.setTextureRect(left);
				sprite.move(-19, 0);
				footsteps.play();
			}
			else
			{
				bump.play();
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