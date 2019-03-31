#include "GoombaMove.h"
#include "Component.h"
#include "MoveComponent.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Math.h"
#include "Block.h"
#include "Goomba.h"
#include <iostream>

using namespace std;


GoombaMove::GoombaMove(Goomba* owner):MoveComponent(owner)
{
	this->SetForwardSpeed(-100.0f);
}


GoombaMove::~GoombaMove()
{
}

void GoombaMove::Update(float deltaTime) {
	Vector2 initial = mOwner->GetPosition();
	float newX = initial.x + this->GetForwardSpeed()*deltaTime;
	if (newX < 0) {
		newX = 0;
		this->SetForwardSpeed(-(this->GetForwardSpeed()));
	}
	if (newX > 600) {
		newX = 600;
		this->SetForwardSpeed(-(this->GetForwardSpeed()));
	}
	mOwner->SetPosition(Vector2(newX, initial.y + mYSpeed * deltaTime));


	if (mOwner->GetPosition().y >= 448 * level) {
		mOwner->SetState(ActorState::Destroy);
	}

	//check collision;
	CollisionComponent* goombaCC = mOwner->GetComponent<CollisionComponent>();
	for (int i = 0; i < mOwner->GetGame()->blocks.size(); i++) {
		Vector2 offset = Vector2(0, 0);
		CollisionComponent* blockCC = mOwner->GetGame()->blocks[i]->cc;
		if (goombaCC->GetMinOverlap(blockCC, offset) == CollSide::Top&&mYSpeed >= 0.0f) {
			//cout << "top collide" << endl;
			mYSpeed = 0.0f;
		}

		mOwner->SetPosition(mOwner->GetPosition() + offset);
	}
	for (int i = 0; i < mOwner->GetGame()->blocks.size(); i++) {
		Vector2 offset = Vector2(0, 0);
		CollisionComponent* blockCC = mOwner->GetGame()->blocks[i]->cc;
		if (goombaCC->GetMinOverlap(blockCC, offset) == CollSide::Left&&this->GetForwardSpeed() > 0) {
			//cout << "left" << endl;
			this->SetForwardSpeed(-(this->GetForwardSpeed()));
		}
		else if (goombaCC->GetMinOverlap(blockCC, offset) == CollSide::Right&&this->GetForwardSpeed() < 0) {
			this->SetForwardSpeed(-(this->GetForwardSpeed()));
			//cout << "right" << endl;
		}
		mOwner->SetPosition(mOwner->GetPosition() + offset);
	}

	for (int i = 0; i < mOwner->GetGame()->goombas.size(); i++) {
		if (!dynamic_cast<Goomba*>(mOwner)->dead) {
			Vector2 offset = Vector2(0, 0);
			if (mOwner->GetGame()->goombas[i] != this->mOwner)
			{
				if (!mOwner->GetGame()->goombas[i]->dead)
				{
					CollisionComponent* anotherGoombaCC = mOwner->GetGame()->goombas[i]->cc;
					if (goombaCC->GetMinOverlap(anotherGoombaCC, offset) == CollSide::None) {
						continue;
					}
					if (goombaCC->GetMinOverlap(anotherGoombaCC, offset) == CollSide::Top&&mYSpeed >= 0.0f) {
						//cout << "top collide" << endl;
						mYSpeed = 0.0f;
						mInAir = false;
					}
					else if (goombaCC->GetMinOverlap(anotherGoombaCC, offset) == CollSide::Left) {
						this->SetForwardSpeed(-(this->GetForwardSpeed()));
					}
					else if (goombaCC->GetMinOverlap(anotherGoombaCC, offset) == CollSide::Right) {
						this->SetForwardSpeed(-(this->GetForwardSpeed()));
					}
					mOwner->SetPosition(mOwner->GetPosition() + offset);
				}

			}
		}
	}
	mYSpeed += 2000.0f*deltaTime;
}
