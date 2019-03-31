#include "Tip.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "Collectible.h"
#include "Game.h"
#include "Player.h"


Tip::Tip(Game* game) :Actor(game)
{
	cc = new CollisionComponent(this);
	cc->SetSize(20, 20);
	collectible = new Collectible(this);
	collectible->setOnCollect([this, game] {
		this->SetState(ActorState::Destroy);
		game->player->SetState(ActorState::Paused);
		Mix_HaltChannel(game->backgroundMusicChannel);
		Mix_PlayChannel(-1, game->GetSound("Assets/Sounds/PowerUp.wav"), 0);
		game->player->SetState(ActorState::Active);
	});

	asc = new AnimatedSprite(this);
	std::vector<SDL_Texture*> triforce{
		GetGame()->GetTexture("Assets/Triforce0.png"),
		GetGame()->GetTexture("Assets/Triforce1.png"),
	};
	asc->AddAnimation("triforce", triforce);
	asc->SetAnimation("triforce");
}


Tip::~Tip()
{
}