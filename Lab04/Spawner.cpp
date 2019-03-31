#include "Spawner.h"
#include "Game.h"
#include "Actor.h"
#include "Player.h"
#include "Goomba.h"
#include "GoombaMove.h"
#include "PlayerMove.h"



Spawner::Spawner(Game* game):Actor(game)
{
}


Spawner::~Spawner()
{
}

void Spawner::OnUpdate(float deltaTime) {
	if (this->GetPosition().x - mGame->player->GetPosition().x < 600 && level == GetGame()->player->GetComponent<PlayerMove>()->level) {
		Goomba* goomba = new Goomba(mGame);
		goomba->SetPosition(this->GetPosition());
		goomba->GetComponent<GoombaMove>()->level = level;
		this->SetState(ActorState::Destroy);
	}
}
