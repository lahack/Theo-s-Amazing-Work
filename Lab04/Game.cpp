//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include <algorithm>
#include <SDL/SDL_image.h>
#include "Random.h"
#include <iostream>
#include<fstream>
#include "Block.h"
#include "Player.h"
#include "PlayerMove.h"
#include "Spawner.h"
#include "Goomba.h"
#include "Tip.h"
#include "Ref.h"
#include "CollisionComponent.h"
#include "Door.h"
#include "Teleport.h"
// TODO
const int maxHeight = 448;
const int maxLength = 600;
const int BlockHeight = 32;
const int BlockWidth = 32;

bool Game::Initialize() {
	Random::Init();

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
		return false;

	window = SDL_CreateWindow(
		"Ruilin Liu Lab 4",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		600,                               // width, in pixels
		448,                               // height, in pixels
		SDL_WINDOW_RESIZABLE
	);
	if (window == NULL) {
		return false;
	}

	renderer = SDL_CreateRenderer(window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		return false;

	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		// handle error
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	LoadData();

	previousTime= SDL_GetTicks();

	return true;
}

void Game::RunLoop() {
	while (!quit) {
		Game::ProcessInput();
		Game::UpdateGame();
		Game::GenerateOuput();
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		quit = true;

	vector<Actor*> actorsCopy = actors;
	for (int i = 0; i < actorsCopy.size(); i++) {
		actorsCopy[i]->ProcessInput(state);
	}
}

void Game::UpdateGame() {
	int currentTime = SDL_GetTicks();
	while (currentTime - previousTime <= 16) {
		currentTime = SDL_GetTicks();
	}
	float deltaTime = (currentTime - previousTime)*0.001;
	previousTime = currentTime;
	if (deltaTime > 0.033) {
		deltaTime = 0.033;
	}
	
	vector<Actor*> actorsCopy = actors;
	for (int i = 0; i < actorsCopy.size(); i++) {
		actorsCopy[i]->Update(deltaTime);
	}
	vector<Actor*> actorsDestroy;
	for (int i = 0; i < actors.size(); i++) {
		if (actors[i]->GetState() == ActorState::Destroy) {
			actorsDestroy.push_back(actors[i]);
		}
	}
	while (!actorsDestroy.empty()) {
		delete actorsDestroy.back();
		actorsDestroy.erase(actorsDestroy.begin()+actorsDestroy.size()-1);
	}
}

void Game::GenerateOuput() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	SDL_RenderClear(renderer);

	for (int i = 0; i < mSprites.size(); i++) {
		if (mSprites[i]->IsVisible()) {
			mSprites[i]->Draw(renderer);
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::Shutdown() {
	Mix_CloseAudio();
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::AddActor(class Actor* actor) {
	actors.push_back(actor);
}

void Game::RemoveActor(class Actor* actor) {
	actors.erase(find(begin(actors), end(actors), actor));
}



void Game::LoadData() {
	Actor* background = new Actor(this);
	background->SetPosition(Vector2(3392, 224));
	SpriteComponent* scBackground = new SpriteComponent(background, 60);
	scBackground->SetTexture(GetTexture("Assets/Background.png"));

	Actor* bedroom = new Actor(this);
	bedroom->SetScale(1.15);
	bedroom->SetPosition(Vector2(300, 2464));
	SpriteComponent* bedroomBackground = new SpriteComponent(bedroom, 60);
	bedroomBackground->SetTexture(GetTexture("Assets/bedroom.png"));

	ReadFile("Assets/Level3.txt", this);
	backgroundMusicChannel=Mix_PlayChannel(-1, GetSound("Assets/Sounds/Music.ogg"), -1);




	//hardcoding the invisible blocks in the home page

	blue_pic = new Actor(this);
	blue_pic->SetPosition(Vector2(256, 2320));
	CollisionComponent* cc1 = new CollisionComponent(blue_pic);
	cc1->SetSize(110, 32);
	door_1 = new Teleport(this, 5, 32, 32);
	door_1->SetPosition(Vector2(270, 2360));

	
	light = new Actor(this);
	light->SetPosition(Vector2(96, 2512));
	CollisionComponent* cc2 = new CollisionComponent(light);
	cc2->SetSize(58, 32);
	door_2 = new Teleport(this, 1, 32, 32);
	door_2->SetPosition(Vector2(72, 2488));

	red_pic = new Actor(this);
	red_pic->SetPosition(Vector2(368, 2320));
	CollisionComponent* cc3 = new CollisionComponent(red_pic);
	cc3->SetSize(32, 32);
	door_3 = new Teleport(this, 4, 32, 32);
	door_3->SetPosition(Vector2(388, 2360));

	bed = new Actor(this);
	bed->SetPosition(Vector2(304, 2544));
	CollisionComponent* cc4 = new CollisionComponent(bed);
	cc4->SetSize(224, 32);
	door_4 = new Teleport(this, 2, 32, 32);
	door_4->SetPosition(Vector2(334, 2424));

	shelf = new Actor(this);
	shelf->SetPosition(Vector2(512, 2384));
	CollisionComponent* cc5 = new CollisionComponent(shelf);
	cc5->SetSize(128, 32);
	door_5 = new Teleport(this, 3, 32, 32);
	door_5->SetPosition(Vector2(520, 2370));


}

void Game::UnloadData() {
	while (!actors.empty()) {
		delete actors.back();
		//actors.erase(actors.begin() + actors.size() - 1);
	}
	for (pair<string, SDL_Texture*> element : textureMap)
	{
		SDL_DestroyTexture(element.second);
	}
	textureMap.clear();

	for (pair<string, Mix_Chunk*> element : soundMap)
	{
		Mix_FreeChunk(element.second);
	}
	soundMap.clear();
}

SDL_Texture* Game::GetTexture(string name) {
	if (textureMap.find(name) != textureMap.end()) {
		return textureMap[name];
	}
	else {
		SDL_Surface *image;
		image = IMG_Load(name.c_str());
		if (!image) {
			printf("IMG_Load: %s\n", IMG_GetError());
			// handle error
		}
		SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
		textureMap[name] = imageTexture;
		return imageTexture;
	}
}

void Game::AddSprite(SpriteComponent* sc) {
	mSprites.push_back(sc);
	// mSprites is std::vector<SpriteComponent*>
	sort(mSprites.begin(), mSprites.end(),
		[](SpriteComponent* a, SpriteComponent* b) {
		return a->GetDrawOrder() < b->GetDrawOrder();
	});

}

void Game::RemoveSprite(SpriteComponent* sc) {
	mSprites.erase(find(begin(mSprites), end(mSprites), sc));
}

void Game::ReadFile(string filename,Game* g) {

	ifstream myReadFile;
	myReadFile.open(filename);
	if (myReadFile.is_open()) {
		string line;
		int centerX = 16;
		int centerY = 16;
		int level = 1;
		int rowCount = 1;
		while (getline(myReadFile, line)) {
			for (int i = 0; i < line.length(); i++) {
				string current = line.substr(i, 1);
				if (current == "A") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
				}
				else if (current == "B") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
					currentBlock->ChangeTexture(g->GetTexture("Assets/BlockB.png"));
				}
				else if (current == "C") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
					currentBlock->ChangeTexture(g->GetTexture("Assets/BlockC.png"));
				}
				else if (current == "D") {
					Door* door = new Door(this);
					door->SetPosition(Vector2(centerX, centerY));
				}
				else if (current == "E") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
					currentBlock->ChangeTexture(g->GetTexture("Assets/BlockE.png"));
				}
				else if (current == "F") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
					currentBlock->ChangeTexture(g->GetTexture("Assets/BlockF.png"));
				}
				else if (current == "G") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
					currentBlock->ChangeTexture(g->GetTexture("Assets/BlockG.png"));
				}
				else if (current == "H") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
					currentBlock->ChangeTexture(g->GetTexture("Assets/BlockH.png"));
				}
				else if (current == "I") {
					Block* currentBlock = new Block(g);
					currentBlock->SetPosition(Vector2(centerX, centerY));
					currentBlock->ChangeTexture(g->GetTexture("Assets/BlockI.png"));
				}
				else if (current == "T") {
					Tip* currentTip = new Tip(g);
					currentTip->SetPosition(Vector2(centerX, centerY));
					//currentBlock->ChangeTexture(g->GetTexture("Assets/BlockI.png"));
				}
				else if (current == "Y") {
					Spawner* currentSpawner = new Spawner(g);
					currentSpawner->SetPosition(Vector2(centerX, centerY));
					currentSpawner->level = level;
				}
				else if (current == "P") {
					player = new Player(g);
					player->SetPosition(Vector2(centerX, centerY));
					player->GetComponent<PlayerMove>()->level = level;
				}
				else if (current == "R") {
					refrigirator = new Ref(g);
					//std::cout << refrigirator->cc->GetWidth() << std::endl;
					refrigirator->SetPosition(Vector2(centerX - 12, centerY));
				}
				centerX += BlockWidth;
			}
			centerX = 16;
			centerY += BlockHeight;
			rowCount++;
			if (rowCount == 15) {
				rowCount = 1;
				level++;
			}
		}
	}
}

void Game::RemoveBlk(Block* BLK) {

}

Mix_Chunk* Game::GetSound(const std::string& filename) {
	if (soundMap.find(filename) != soundMap.end()) {
		return soundMap[filename];
	}
	else {
		Mix_Chunk *sound;
		sound = Mix_LoadWAV(filename.c_str());
		if (!sound) {
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
			// handle error
		}
		
		soundMap[filename] = sound;
		return sound;
	}
}

