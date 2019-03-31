#include "Actor.h"

class Game;

class Teleport : public Actor {
public:
	Teleport(Game* game, int level, int width, int height);
	void setup();
	int level;
	int width;
	int height;
	bool created = false;
};