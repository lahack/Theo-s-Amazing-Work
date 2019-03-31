#include "Ref.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include <iostream>
using namespace std;

Ref::Ref(Game* game) 
	:Actor(game)
{
	sc = new SpriteComponent(this);
	cc = new CollisionComponent(this);
	cc->SetSize(32, 32);
	sc->SetTexture(game->GetTexture("Assets/ref.png"));
	row = 13;
	col = 2;
	level = 1;
}

Ref::~Ref() {

}