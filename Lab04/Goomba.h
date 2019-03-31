#pragma once
#include "Actor.h"
class Goomba :
	public Actor
{
public:
	Goomba(class Game* game);
	~Goomba();
	class AnimatedSprite* asc;
	class CollisionComponent* cc;
	class GoombaMove* gm;
	bool dead = false;
	float deadTime = 0.0f;
	void OnUpdate(float deltaTime) override;
};

