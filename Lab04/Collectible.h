#pragma once
#include "Component.h"
#include <functional>
class Collectible :
	public Component
{
public:
	Collectible(class Actor* owner);
	~Collectible();
	std::function<void()> mOnCollect;
	void setOnCollect(std::function<void()> onCollect);
	void Update(float deltaTime) override;
};

