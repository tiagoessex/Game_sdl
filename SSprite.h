#ifndef SSprite_h
#define SSprite_h


#include "Sprite.h"

class SSprite : public Sprite
{
public:
	SSprite();
	SSprite(std::string filename);
	SSprite(SDL_Surface*);
	SSprite(SDL_Surface*, int x, int y);
	
	virtual ~SSprite();

	virtual void draw(SDL_Surface*);
	virtual void draw(SDL_Surface*, int, int);		//draw surface at x,y on surface | doesn't change the x,y attributes

	int getX();
	int getY();

	void setX(int);
	void setY(int);
	void setPos(int, int);

	SDL_Surface* makeCopy();				// returns an independent surface copy

	SDL_Rect& getBox();

protected:
	int x,y;					// current sprite pos

	SDL_Rect temprect;
};


#endif