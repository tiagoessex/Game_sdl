

#include "EnemyShoots.h"

EnemyShoots::EnemyShoots(std::string filename)
{
	sprite = Sprite(filename);
	sprite.setTransparency(0,0,0);
}

EnemyShoots::~EnemyShoots()
{
//	sprite.destroy();
}


void EnemyShoots::add(int x, int y, double speed, double direction)
{
	shoot.shoot_direction = direction;
	shoot.shoot_posx = x;
	shoot.shoot_posy = y;
	shoot.shoot_speed = speed;	
	shoots_collection.push_back(shoot);	
	n++;
}

void EnemyShoots::remove(int index)
{	
	shoots_collection.erase(shoots_collection.begin()+index);
	n--;
}


int EnemyShoots::getSize()
{
	return shoots_collection.size();
}


void EnemyShoots::moveall()
{
	for ( unsigned int i=0; i<shoots_collection.size(); i++)
	{
		stepx = (int) (cos ((shoots_collection[i].shoot_direction*PI)/180) * shoots_collection[i].shoot_speed);
		stepy = (int) (sin ((-shoots_collection[i].shoot_direction*PI)/180) * shoots_collection[i].shoot_speed);
		
		shoots_collection[i].shoot_posx +=stepx;
		shoots_collection[i].shoot_posy +=stepy;

		// shoots life = f(space) extension
		checkBoundaries(i);
	
	}
}

void EnemyShoots::checkBoundaries(int index)
{
	if ((shoots_collection[index].shoot_posy>550))
		shoots_collection.erase(shoots_collection.begin()+index);
	else if ((shoots_collection[index].shoot_posy<50))
		shoots_collection.erase(shoots_collection.begin()+index);
	else if ((shoots_collection[index].shoot_posx>750))
		shoots_collection.erase(shoots_collection.begin()+index);
	else if ((shoots_collection[index].shoot_posx<50))
		shoots_collection.erase(shoots_collection.begin()+index);
}


void EnemyShoots::draw(SDL_Surface* buffer)
{
	for ( unsigned int i=0; i<shoots_collection.size(); i++)
	{
		dstrect.x = shoots_collection[i].shoot_posx;
		dstrect.y = shoots_collection[i].shoot_posy;
		SDL_BlitSurface(sprite.getSurface(), NULL, buffer,&dstrect);
	}
}

bool EnemyShoots::isEmpty()
{
	return shoots_collection.empty();
}


int EnemyShoots::getn()
{
	return n;
}


bool EnemyShoots::checkCollisions(SDL_Rect& rect)
{
	dstrect.w = sprite.getSurface()->w;
	dstrect.h = sprite.getSurface()->h;
	temp_bool = false;

	for ( unsigned int i=0; i<shoots_collection.size(); i++)
	{
		dstrect.x = shoots_collection[i].shoot_posx;
		dstrect.y = shoots_collection[i].shoot_posy;

		if (SDL_CollideBoundingBox(dstrect, rect))
		{
			shoots_collection.erase(shoots_collection.begin()+i);
			n--;
			temp_bool = true;
		}

	}
	return temp_bool;
}

bool EnemyShoots::checkCollisions(SDL_Surface* surface, int x, int y)
{
	temp_bool = false;
	for ( unsigned int i=0; i<shoots_collection.size(); i++)
	{
		if (SDL_CollidePixel(sprite.getSurface(),shoots_collection[i].shoot_posx, shoots_collection[i].shoot_posy, 
			surface, x, y))
		{
			shoots_collection.erase(shoots_collection.begin()+i);
			n--;
			temp_bool = true;
		}
	}
	return temp_bool;
}

SDL_Rect& EnemyShoots::getEnemyShootRect(int index)
{
 	dstrect.x=shoots_collection[index].shoot_posx;
	dstrect.y=shoots_collection[index].shoot_posy;
	dstrect.w=sprite.getSurface()->w;
	dstrect.h=sprite.getSurface()->h;
	return dstrect;         
}
