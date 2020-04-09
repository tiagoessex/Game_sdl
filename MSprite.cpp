
#include "MSprite.h"


MSprite::MSprite() : SSprite()
{
	movspeed = 1.0;
	movdirection = 1.0;
}


MSprite::MSprite(std::string filename) : SSprite (filename)
{
	movspeed = 1.0;
	movdirection = 1.0;
}

MSprite::MSprite(SDL_Surface* surface) : SSprite (surface,0,0)
{
	movspeed = 1.0;
	movdirection = 1.0;
}

MSprite::MSprite(SDL_Surface* surface, int x, int y, double speed, double direction) : SSprite (surface, x,y)
{
	movspeed= speed;
	movdirection = direction;
}


MSprite::~MSprite()
{
	//destroy();
}




void MSprite::move()
{
	int stepx, stepy;
	double PI=3.14159265;

	stepx = (int) (cos ((movdirection*PI)/180) * movspeed);
	stepy = (int) (sin ((-movdirection*PI)/180) * movspeed);

	setX ( getX() + stepx );
	setY ( getY() + stepy );
}

void MSprite::move(double dir)
{
	int stepx, stepy;
	double PI=3.14159265;

	stepx = (int) (cos ((dir*PI)/180) * movspeed);
	stepy = (int) (sin ((-dir*PI)/180) * movspeed);

	setX ( getX() + stepx );
	setY ( getY() + stepy );
}

void MSprite::setMovSpeed(double movspeed)
{
	this->movspeed = movspeed;
}
	
void MSprite::setMovDirection(double movdirection)
{
	this->movdirection = movdirection;
}

double MSprite::getMovSpeed()
{
	return movspeed;
}

double MSprite::getMovDirection()
{
	return movdirection;
}

