/*
Variable Explanations:
	tempSpritePosition = Left and Top side of the Sprite
	tempSpriteWH = The Width and Height of the Sprite
	tempCollisionBoxPosition = Left and Top side of the Collision Box
	tempCollisionBoxWH = The Width and Height of the Collision Box
*/

#include <SFML/Graphics.hpp>

//Pass in top left cord of sprite + collisionbox, and both of their heights and widths
bool collision (sf::Vector2i tempSpritePosition, sf::Vector2i tempSpriteWH, 
	sf::Vector2i tempCollisionBoxPosition, sf::Vector2i tempCollisionBoxWH)
	
{
	if(tempSpritePosition.x + tempSpriteWH.x > tempCollisionBoxPosition.x && tempSpritePosition.x < tempCollisionBoxPosition.x + tempCollisionBoxWH.x)
	{
		if(tempSpritePosition.y + tempSpriteWH.y > tempCollisionBoxPosition.y && tempSpritePosition.y < tempCollisionBoxPosition.y + tempCollisionBoxWH.y)
			return true;
		else
			return false;
	}
	else
		return false;
}