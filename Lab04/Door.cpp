#include "Door.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Collectible.h"
#include "Game.h"
#include "Player.h"
#include "PlayerMove.h"
#include <iostream>
using namespace std;


Door::Door(Game* game, bool show) :Actor(game)
{
	cc = new CollisionComponent(this);
	cc->SetSize(20, 20);
	collectible = new Collectible(this);
	collectible->setOnCollect([this, game] {
		GetGame()->player->GetComponent<PlayerMove>()->go_to_level(6, 83, 2);
		game->player->SetState(ActorState::Paused);
		Mix_HaltChannel(game->backgroundMusicChannel);
		Mix_PlayChannel(-1, game->GetSound("Assets/Sounds/PowerUp.wav"), 0);
		game->player->SetState(ActorState::Active);

	});

	sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/door.png"));
	if (!show) {
		sc->SetIsVisible(false);
	}
	
	
}


Door::~Door()
{
}