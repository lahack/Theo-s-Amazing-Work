#include "Block.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"


Block::Block(Game* game) :Actor(game)
{
	Height = 32;
	Width = 32;
	sc = new SpriteComponent(this);
	sc->SetTexture(mGame->GetTexture("Assets/BlockA.png"));
	cc = new CollisionComponent(this);
	cc->SetSize(32, 32);
	game->blocks.push_back(this);
}


Block::~Block()
{
	mGame->blocks.erase(find(begin(mGame->blocks), end(mGame->blocks), this));
}

void Block::ChangeTexture(SDL_Texture* texture) {
	sc->SetTexture(texture);
}
