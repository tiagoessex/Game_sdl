

#include "PlayerShoots.h"

PlayerShoots::PlayerShoots(std::string filename)
{
	/*
	SDL_Surface*  temp = IMG_Load( filename.c_str());
	if (temp != NULL)
	{
		sprite = SDL_DisplayFormat( temp );	
		SDL_FreeSurface( temp ); 		 
		loaded= true;
		n=0;
	}
	else
		loaded = false;
		*/

	sprite = Sprite(filename);
	sprite.setTransparency(0,0,0);
}

PlayerShoots::~PlayerShoots()
{
/*	if (loaded)
	{
		SDL_FreeSurface(sprite);
	}
	*/
//	sprite.destroy();
}


void PlayerShoots::add(int x, int y, double speed, double direction)
{
	shoot.shoot_direction = direction;
	shoot.shoot_posx = x;
	shoot.shoot_posy = y;
	shoot.shoot_speed = speed;	
	shoots_collection.push_back(shoot);	
	n++;
}

void PlayerShoots::remove(int index)
{	
	shoots_collection.erase(shoots_collection.begin()+index);
	n--;
}


int PlayerShoots::getSize()
{
	return shoots_collection.size();
}


void PlayerShoots::moveall()
{
	for ( unsigned int i=0; i<shoots_collection.size(); i++)
	{
		stepx = (int) (cos ((shoots_collection[i].shoot_direction*PI)/180) * shoots_collection[i].shoot_speed);
		stepy = (int) (sin ((-shoots_collection[i].shoot_direction*PI)/180) * shoots_collection[i].shoot_speed);
		
		shoots_collection[i].shoot_posx +=stepx;
		shoots_collection[i].shoot_posy +=stepy;
		
		// shoots life = f(space) extension
		if ((shoots_collection[i].shoot_posy<100))
		{
			shoots_collection.erase(shoots_collection.begin()+i);
			n--;
		}		

	}
}




void PlayerShoots::draw(SDL_Surface* buffer)
{
	for ( unsigned int i=0; i<shoots_collection.size(); i++)
	{
		dstrect.x = shoots_collection[i].shoot_posx;
		dstrect.y = shoots_collection[i].shoot_posy;
		SDL_BlitSurface(sprite.getSurface(), NULL, buffer,&dstrect);
	}
}

bool PlayerShoots::isEmpty()
{
	return shoots_collection.empty();
}




bool PlayerShoots::checkCollisions(SDL_Rect& rect)
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

bool PlayerShoots::checkCollisions(SDL_Surface* surface, int x, int y)
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

SDL_Rect& PlayerShoots::getPlayerShootRect(int index)
{
	dstrect.x=shoots_collection[index].shoot_posx;
	dstrect.y=shoots_collection[index].shoot_posy;
	dstrect.w=sprite.getSurface()->w;
	dstrect.h=sprite.getSurface()->h;
	return dstrect;
}


int PlayerShoots::getX(int index)
{
	return shoots_collection[index].shoot_posx;
}

int PlayerShoots::getY(int index)
{
	return shoots_collection[index].shoot_posy;
}
