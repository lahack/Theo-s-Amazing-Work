#include "Collectible.h"
#include "Player.h"
#include "CollisionComponent.h"
#include "Game.h"

Collectible::Collectible(class Actor* owner):Component(owner)
{
}


Collectible::~Collectible()
{
}

void Collectible::setOnCollect(std::function<void()> onCollect) {
	mOnCollect = onCollect;
}

void Collectible::Update(float deltaTime) {
	CollisionComponent* playerCC = mOwner->GetGame()->player->cc;
	CollisionComponent* collectibleCC= mOwner->GetComponent<CollisionComponent>();
	//if collides
	if (playerCC->GetMinOverlap(collectibleCC, Vector2(0, 0)) != CollSide::None) {
		
		if (mOnCollect) {
			mOnCollect();
		}
	}
}
