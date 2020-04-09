#ifndef EnemyExplosions_h
#define EnemyExplosions_h

#include <vector>

#include "AnimSprite.h"
//#include "Sprite.h"


extern double PI;

using std::vector;

class EnemyExplosions
{
public:
	EnemyExplosions(std::string filename, int frames, int speed);
	virtual ~EnemyExplosions();

	void add(int x, int y);
	void remove(int index);
	void animate();
	void drawAll(SDL_Surface* buffer);

	bool isEmpty();
	
	int getn();
	
	int getSize();

private:

//	Sprite* animation;
	SDL_Surface* surface;

	vector<AnimSprite*> explosions_collection;

    vector<AnimSprite*>::iterator it;
    
  //  AnimSprite* tempanim;
    
    int n;
};



#endif
