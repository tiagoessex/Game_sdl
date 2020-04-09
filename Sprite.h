#ifndef Sprite_h
#define Sprite_h

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

//#include <windows.h>

class Sprite
{
public:
	Sprite();
	Sprite(std::string filename);
	Sprite(SDL_Surface*);

	virtual ~Sprite();


//	Sprite(const Sprite& original);				// copy constructor - mem leak
	Sprite& operator=(const Sprite& original);	// assigment op		 - mem leak

	
	SDL_Surface* getSurface();

    void setTransparency(Uint32);
    void setTransparency(int,int,int);
	
	void setAlpha( int intensity );

//	SDL_Surface* makeCopy();				// returns an independent surface copy


	bool isLoaded();


	//***********************

	virtual void draw(SDL_Surface*);
	virtual void draw(SDL_Surface*, int, int);		//draw surface at x,y on surface | doesn't change the x,y attributes

	int getX();
	int getY();

	void setX(int);
	void setY(int);
	void setPos(int, int);

	

	SDL_Rect& getBox();


protected:

	SDL_Surface* sprite;		// sprite surface

	bool loaded;				// true if sprite loaded with sucess


	int x,y;					// current sprite pos

	SDL_Rect temprect;
};


#endif

