#pragma once
#include "Actor.h"
class Player :
	public Actor
{
public:
	Player(class Game* game);
	~Player();
	class MoveComponent* mc;
	class AnimatedSprite* asc;
	class CollisionComponent* cc;
	bool touched_ref = false;
};

