#pragma once
#include "Actor.h"
#include "SDL/SDL.h"
class Block :
	public Actor
{
public:
	Block(class Game* game);
	~Block();
	class SpriteComponent* sc;
	class CollisionComponent* cc;
	void ChangeTexture(SDL_Texture* texture);
	
};

