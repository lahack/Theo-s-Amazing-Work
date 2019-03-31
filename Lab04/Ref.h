#include "Actor.h"
#include "SDL/SDL.h"
class Ref :	public Actor
{
public:
	Ref(class Game* game);
	~Ref();
	class SpriteComponent* sc;
	class CollisionComponent* cc;
	int row;
	int col;
	int level;
};

