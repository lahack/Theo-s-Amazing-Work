#include "Teleport.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

Teleport::Teleport(Game* game, int level, int width, int height)
	:Actor(game)
{
	this->level = level;
	this->width = width;
	this->height = height;
}

void Teleport::setup() {
	new CollisionComponent(this);
	GetComponent<CollisionComponent>()->SetSize(width, height);

	new SpriteComponent(this);
	GetComponent<SpriteComponent>()->SetTexture(GetGame()->GetTexture("Assets/swirl.png"));
	created = true;
}