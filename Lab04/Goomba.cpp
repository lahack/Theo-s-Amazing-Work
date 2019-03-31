#include "Goomba.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "PlayerMove.h"
#include "GoombaMove.h"
#include "AnimatedSprite.h"



Goomba::Goomba(Game* game) :Actor(game)
{
	/*sc = new SpriteComponent(this, 150);
	sc->SetTexture(mGame->GetTexture("Assets/Goomba/Walk0.png"));*/
	/*std::vector<SDL_Texture*> walkAnim = std::vector<SDL_Texture*>();
	walkAnim.push_back(GetGame()->GetTexture("Assets/Goomba/Walk0.png"));
	walkAnim.push_back(GetGame()->GetTexture("Assets/Goomba/Walk1.png"));*/

	asc = new AnimatedSprite(this);
	std::vector<SDL_Texture*> walkAnim{
		GetGame()->GetTexture("Assets/Goomba/Walk0.png"),
		GetGame()->GetTexture("Assets/Goomba/Walk1.png")
	};
	// This assumes "asc" is the animated sprite component
	asc->AddAnimation("walk", walkAnim);
	asc->SetAnimation("walk");

	std::vector<SDL_Texture*> deadAnim{
		GetGame()->GetTexture("Assets/Goomba/Dead.png")
	};
	asc->AddAnimation("dead", deadAnim);

	cc = new CollisionComponent(this);
	cc->SetSize(32, 32);
	gm = new GoombaMove(this);
	game->goombas.push_back(this);
}


Goomba::~Goomba()
{
	mGame->goombas.erase(find(begin(mGame->goombas), end(mGame->goombas), this));
}

void Goomba::OnUpdate(float deltaTime) {
	if (dead) {
		deadTime += deltaTime;
		if (deadTime >= 0.25) {
			SetState(ActorState::Destroy);
		}
	}
}