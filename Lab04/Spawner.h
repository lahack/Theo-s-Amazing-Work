#pragma once
#include "Actor.h"
class Spawner :
	public Actor
{
public:
	Spawner(class Game* game);
	~Spawner();
	void OnUpdate(float deltaTime) override;
	int level = 1;
};

