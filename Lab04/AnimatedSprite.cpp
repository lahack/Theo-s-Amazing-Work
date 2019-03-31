#include "AnimatedSprite.h"
#include "Actor.h"
#include "Game.h"

AnimatedSprite::AnimatedSprite(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{
}

void AnimatedSprite::Update(float deltaTime)
{
	// TODO: Implement
	if (mAnimName.empty())
		return;
	if (!mIsPaused) {
		mAnimTimer += mAnimFPS * deltaTime;
		while (mAnimTimer >= mAnims.find(mAnimName)->second.size()) {
			mAnimTimer -= mAnims.find(mAnimName)->second.size();
		}
	}
	SetTexture(mAnims.find(mAnimName)->second[mAnimTimer/1]);
}

void AnimatedSprite::SetAnimation(const std::string& name, bool resetTimer)
{
	if (mAnimName != name)
	{
		mAnimName = name;
	}
	
	if (resetTimer)
	{
		mAnimTimer = 0.0f;
	}
}

void AnimatedSprite::AddAnimation(const std::string& name,
								  const std::vector<SDL_Texture*>& images)
{
	mAnims.emplace(name, images);
}
