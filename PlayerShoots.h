#ifndef PlayerShoots_h
#define PlayerShoots_h

#include <vector>
#include <math.h>

#include "SDL_collide.h"

#include "Sprite.h"


extern double PI;

using std::vector;

class PlayerShoots
{
public:
	PlayerShoots(std::string filename);
	virtual ~PlayerShoots();

	void add(int x, int y, double speed, double direction);
	void remove(int index);
	void moveall();
	void draw(SDL_Surface* buffer);

	int getSize();			// returns number of elements
	bool isEmpty();			// returns true of no elements

	//SDL_Surface* getSurface();


	bool checkCollisions(SDL_Rect& rect);						// returns true if some shoot hit rect
	bool checkCollisions(SDL_Surface* surface, int x, int y);	// returns true if some shoot hit surface

	SDL_Rect& getPlayerShootRect(int index);				// returns the rect of shoot index

	int getX(int index);
	int getY(int index);

private:
//	SDL_Surface* sprite;
//	bool loaded;
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
