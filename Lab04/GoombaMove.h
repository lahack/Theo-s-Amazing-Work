#pragma once
#include "MoveComponent.h"
#include "Math.h"
class GoombaMove :
	public MoveComponent
{
public:
	GoombaMove(class Goomba* owner);
	~GoombaMove();
	void Update(float deltaTime) override;
	float mYSpeed = 0.0f;
	bool mInAir = false;
	int level = 1;
};

