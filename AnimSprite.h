
/* falta constructor and assibmenop*/

#ifndef AnimSprite_h
#define AnimSprite_h


#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


#ifdef __APPLE__
    #include "SDL/SDL.h"
#else
    #include "SDL.h"
#endif

#include "SDL_image.h"


extern long timer;			// ms since SDL has been initialized

class AnimSprite
{
public:
//	AnimSprite();	
	AnimSprite(std::string filename, int frames, int speed); //, double movdirection, double movspeed);
	AnimSprite(SDL_Surface*, int frames, int speed); //, double movdirection, double movspeed);
	AnimSprite(SDL_Surface*, int frames, int speed, int x, int y);
	virtual ~AnimSprite();
	void destroy();              // destructor 
	
//	AnimSprite(const AnimSprite& original);				// copy constructor
//	AnimSprite& operator=(const AnimSprite& original);	// assigment op		

	void animate();			// next frame

	// override Sprite draw
	virtual void draw(SDL_Surface*);				// draw current frame
	virtual void draw(SDL_Surface*, int, int);		// draw current frame at x,y


	int getWidth();
	int getHeight();

	int getIndex();							// returns curernt index
	

	SDL_Surface* getCurrentFrameSurface();	// returns copy of the current frame's surface - memory leak
	SDL_Rect& getCurrentFrameBox();
	
	bool isEndAnimation();
	

	/// ***********************

    void setTransparency(Uint32);
    void setTransparency(int,int,int);
	
	void setAlpha( int intensity );

	bool isLoaded();

	int getX();
	int getY();

	void setX(int);
	void setY(int);
	void setPos(int, int);
	
	void resetAnimation();

private:
	bool loaded;				// true if sprite loaded with sucess

	SDL_Surface* sprite;		// sprite surface
	SDL_Surface *temp;	// auxiliary - declared here to avoid memory leaks

	int frames;			// number of frames
	int	speed;			// animation speed in ms
	int index;			// current animation index
	bool run;			// if animation is running
	int lastanimated;	// time of the last frame change

	int framewidth;		// animation frame width
	int frameheight;	// animation frame height

	bool end_animation;			// only for 1º animation cycle

	SDL_Rect temprect;
	int x,y;					// current sprite pos

};


#endif
