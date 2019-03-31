#pragma once
#include "Actor.h"
class Tip:
	public Actor
{
public:
	Tip(class Game* game);
	~Tip();
	class AnimatedSprite* asc;
	class CollisionComponent* cc;
	class Collectible* collectible;
};

