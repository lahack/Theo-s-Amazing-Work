#pragma once
#include "MoveComponent.h"
#include "Math.h"
class PlayerMove :
	public MoveComponent
{
public:
	PlayerMove(class Player* owner);
	~PlayerMove();
	//Vector2 velocity = Vector2(0, 0);
	void Update(float deltaTime) override;
	void ProcessInput(const Uint8* keyState) override;
	float mYSpeed = 0.0f;
	bool mSpacePressed = false;
	bool mInAir = false;
	void GoombaDead(class Goomba* currentGoomba);
	void PlayerDead(Player* p);
	void updateSprite();
	int level = 6;
	void go_to_level(int level, int row, int col);
	float time = 0.0f;
	void Show_Hide(class CollisionComponent* cc, class Teleport* tel, int row, int col);
	bool notColliding = true;
};

