#include "CollisionComponent.h"
#include "Actor.h"
#include <algorithm>
#include <iostream>


CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other) //return true if intersecting
{
	// TODO: Implement
	Vector2 AMax = this->GetMax();
	Vector2 BMax = other->GetMax();
	Vector2 AMin = this->GetMin();
	Vector2 BMin = other->GetMin();
	
	if (AMax.x < BMin.x)
		return false;
	if (BMax.x < AMin.x)
		return false;
	if (AMax.y < BMin.y)
		return false;
	if (BMax.y < AMin.y)
		return false;
	return true;
}

Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
	int x = mOwner->GetPosition().x - (this->mWidth*mOwner->GetScale()) / 2.0f;
	int y = mOwner->GetPosition().y - (this->mHeight*mOwner->GetScale()) / 2.0f;
	return Vector2(x,y);
}

Vector2 CollisionComponent::GetMax() const
{
	// TODO: Implement
	int x = mOwner->GetPosition().x + (this->mWidth*mOwner->GetScale()) / 2.0f;
	int y = mOwner->GetPosition().y + (this->mHeight*mOwner->GetScale()) / 2.0f;
	return Vector2(x, y);
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector2& offset)
{
	// TODO: Implement
	if(!this->Intersect(other))
		return CollSide::None;
	int dy1 = abs(other->GetMin().y - this->GetMax().y);
	int dy2 = abs(other->GetMax().y - this->GetMin().y);
	int dx1 = abs(other->GetMin().x - this->GetMax().x);
	int dx2 = abs(other->GetMax().x - this->GetMin().x);

	int min = std::min({ dy1,dy2,dx1,dx2 });
	if (min == dy1) {
		offset.y = -min;
		return CollSide::Top;
	}else if (min == dy2) {
		offset.y = min;	
		return CollSide::Bottom;
	}
	else if (min == dx1) {
		offset.x = -min;
		return CollSide::Left;
	}
	else if (min == dx2) {
		offset.x = min;	
		return CollSide::Right;
	}
		
}
