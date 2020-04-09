
#include "SSprite.h"

SSprite::SSprite() : Sprite()
{
	setX(0);
	setY(0);
}


SSprite::SSprite(std::string filename) :  Sprite(filename)
{
	setX(0);
	setY(0);
}


// overload com um sem x,y
SSprite::SSprite(SDL_Surface* surface) : Sprite(surface)
{
    if(isLoaded()) 
	{
		setX(0);
		setY(0);
    }
}


// overload com um sem x,y
SSprite::SSprite(SDL_Surface* surface, int x, int y) : Sprite(surface)
{
    if(isLoaded()) 
	{
		setX(x);
		setY(y);
    } 
	else 
	{
		setX(0);
		setY(0);
    }
}

SSprite::~SSprite()
{
//	if (isLoaded())
//		destroy();
}


void SSprite::draw(SDL_Surface* buffer) 
{
	if (isLoaded())
	{
		SDL_Rect dstrect;
		dstrect.x = x;
		dstrect.y = y;
		SDL_BlitSurface(getSurface(), NULL, buffer,&dstrect);
	}
}


void SSprite::draw(SDL_Surface* buffer, int where_x, int where_y) 
{
	if (isLoaded())
	{
		SDL_Rect dstrect;
		dstrect.x = where_x;
		dstrect.y = where_y;
		SDL_BlitSurface(getSurface(), NULL, buffer,&dstrect);
	}
}


int SSprite::getX()
{
	return x;
}

int SSprite::getY()
{
	return y;
}


void SSprite::setX(int x)
{
	this->x = x;
}

void SSprite::setY(int y)
{
	this->y = y;
}

void SSprite::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}


SDL_Rect& SSprite::getBox()
{
	//SDL_Rect temprect;
	temprect.x=x;
	temprect.y=y;
	temprect.w=getSurface()->w;
	temprect.h=getSurface()->h;
	return temprect;
}
