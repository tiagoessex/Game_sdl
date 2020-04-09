

/* falta constructor and assibmenop*/

#ifndef MSprite_h
#define MSprite_h

#include "SSprite.h"

class MSprite : public SSprite
{
public:
	MSprite();		
	MSprite(std::string filename);
	MSprite(SDL_Surface*);
	MSprite(SDL_Surface*, int x, int y, double speed, double direction);
	virtual ~MSprite();

	void move();
	void move(double dir);

	void setMovSpeed(double movspeed);
	void setMovDirection(double movdirection);
	double getMovSpeed();
	double getMovDirection();

private:
	double movspeed;
	double movdirection;			// angle of direction - [0, 360] - anti-clock dir

};


#endif