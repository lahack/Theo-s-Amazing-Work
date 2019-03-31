#pragma once
#include "SDL/SDL.h"
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "Math.h"
#include "SDL/SDL_mixer.h"

using namespace std;

// TODO
class Game {
public:
	Game() {};
	bool Initialize();
	void Shutdown();
	void RunLoop();
	SDL_Window *window;
	SDL_Renderer *renderer;
	void ProcessInput();
	void UpdateGame();
	void GenerateOuput();
	bool quit = false;
	void AddActor(class Actor*);
	void RemoveActor(class Actor*);
	void RemoveBlk(class Block*);

	int previousTime;
	vector<class Actor*> actors;
	
	unordered_map<string, SDL_Texture*> textureMap;
	unordered_map<string, Mix_Chunk*> soundMap;

	SDL_Texture* GetTexture(string name);
	vector<class SpriteComponent*> mSprites;
	void AddSprite(class SpriteComponent* sc);
	void RemoveSprite(class SpriteComponent* sc);
	void ReadFile(string filename, Game* g);
	vector<class Block*> blocks;
	vector<class Goomba*> goombas;
	class Player* player;
	class Ref* refrigirator;
	Vector2 cameraPos = Vector2(0, 0);
	Mix_Chunk* GetSound(const std::string& filename);
	int backgroundMusicChannel;

	Actor* light;
	Actor* bed;
	Actor* blue_pic;
	Actor* red_pic;
	Actor* shelf;
	class Teleport* door_1;
	class Teleport* door_2;
	class Teleport* door_3;
	class Teleport* door_4;
	class Teleport* door_5;

private:
	void LoadData();
	void UnloadData();
};
