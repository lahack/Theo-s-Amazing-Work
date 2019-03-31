#include "Player.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "PlayerMove.h"
#include "AnimatedSprite.h"


Player::Player(Game* game) :Actor(game)
{
	asc = new AnimatedSprite(this);
	std::vector<SDL_Texture*> idleAnim{
		GetGame()->GetTexture("Assets/Mario/Idle.png")
	};
	asc->AddAnimation("idle", idleAnim);
	asc->SetAnimation("idle");

	std::vector<SDL_Texture*> deadAnim{
		GetGame()->GetTexture("Assets/Mario/Dead.png")
	};
	asc->AddAnimation("dead", deadAnim);

	std::vector<SDL_Texture*> jumpLeftAnim{
		GetGame()->GetTexture("Assets/Mario/JumpLeft.png")
	};
	asc->AddAnimation("jumpLeft", jumpLeftAnim);

	std::vector<SDL_Texture*> jumpRightAnim{
		GetGame()->GetTexture("Assets/Mario/JumpRight.png")
	};
	asc->AddAnimation("jumpRight", jumpRightAnim);

	std::vector<SDL_Texture*> runLeftAnim{
		GetGame()->GetTexture("Assets/Mario/RunLeft0.png"),
		GetGame()->GetTexture("Assets/Mario/RunLeft1.png"),
		GetGame()->GetTexture("Assets/Mario/RunLeft2.png"),
	};
	asc->AddAnimation("runLeft", runLeftAnim);

	std::vector<SDL_Texture*> runRightAnim{
		GetGame()->GetTexture("Assets/Mario/RunRight0.png"),
		GetGame()->GetTexture("Assets/Mario/RunRight1.png"),
		GetGame()->GetTexture("Assets/Mario/RunRight2.png"),
	};
	asc->AddAnimation("runRight", runRightAnim);

	mc = new PlayerMove(this);
	cc = new CollisionComponent(this);
	cc->SetSize(32, 32);
}


Player::~Player()
{
}
