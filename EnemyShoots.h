#ifndef EnemyShoots_h
#define EnemyShoots_h

#include <vector>
#include <math.h>

#include "SDL_collide.h"

#include "Sprite.h"


extern double PI;

using std::vector;

class EnemyShoots
{
public:
	EnemyShoots(std::string filename);
	virtual ~EnemyShoots();

	void add(int x, int y, double speed, double direction);
	void remove(int index);
	void moveall();
	void draw(SDL_Surface* buffer);

	int getSize();			// returns number of elements
	bool isEmpty();			// returns true of no elements


	int getn();

	bool checkCollisions(SDL_Rect& rect);						// returns true if some shoot hit rect
	bool checkCollisions(SDL_Surface* surface, int x, int y);	// returns true if some shoot hit surface

   SDL_Rect& getEnemyShootRect(int index);				// returns the rect of shoot index

private:

	void checkBoundaries(int index);

	Sprite sprite;
	
	int n;
	SDL_Rect dstrect;
	int stepx, stepy;



	struct TShoot
	{
		int shoot_posx, shoot_posy;
		double shoot_direction, shoot_speed;
	} shoot;
	vector<TShoot> shoots_collection;
	

	bool temp_bool;

};



#endif
