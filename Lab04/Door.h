#pragma once
#include "Actor.h"

//Door is solely responsible for going back to the original room
class Door :
	public Actor
{
public:
	Door(class Game* game, bool show = true);
	~Door();
	class SpriteComponent* sc;
	class CollisionComponent* cc;
	class Collectible* collectible;

};

