#include <SFML/Graphics.hpp>

bool inventoryIsOpen = false;

void invent()
{
	
	sf::RenderWindow window2(sf::VideoMode(300, 300, 32), "Inventory", sf::Style::Close);
	window2.setFramerateLimit(60);
	while(inventoryIsOpen){
		
		sf::Event event;
		while(window2.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window2.close();
				return;
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				window2.close();
				sf::sleep(sf::milliseconds(500));
				return;
			}
		}

	}
}