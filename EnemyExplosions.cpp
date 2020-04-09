

#include "EnemyExplosions.h"

EnemyExplosions::EnemyExplosions(std::string filename, int frames, int speed)
{
//	animation = new Sprite(filename); //, frames, speed);
	//animation.setTransparency(0,0,0);
	
	SDL_Surface*  temp = IMG_Load( filename.c_str());
	if (temp != NULL)
	{
		surface = SDL_DisplayFormat( temp );	
		SDL_FreeSurface( temp ); 		 			
	}
	n=0;
	
//	explosions_collection.reserve(15);
	
}

EnemyExplosions::~EnemyExplosions()
{
//	animation.destroy();
	SDL_FreeSurface( surface ); 
	// delete collection	
	for ( unsigned int i=0; i<explosions_collection.size(); i++)
	{
		delete explosions_collection[i];		    
	//	explosions_collection.erase(explosions_collection.begin()+i);		
	}
	explosions_collection.clear();
	
	//delete tempanim;

}


void EnemyExplosions::add(int x, int y)
{
	//explosions_collection.push_back(new AnimSprite(surface,8,200,x,y));
//	tempanim = new AnimSprite(surface,8,200,x,y);
	explosions_collection.push_back(new AnimSprite(surface,8,150,x,y));
	explosions_collection[explosions_collection.size()-1]->setTransparency(0,0,0);

	n++;
}


void EnemyExplosions::remove(int index)
{	
//    AnimSprite* tempanim = explosions_collection[index];
//	delete tempanim;
delete explosions_collection[index];
	explosions_collection.erase(explosions_collection.begin()+index);
	n--;
	
}



void EnemyExplosions::animate()
{
	for ( unsigned int i=0; i<explosions_collection.size(); i++)
	{	
		explosions_collection[i]->animate();
		if (explosions_collection[i]->isEndAnimation())
		{
			remove(i);
		}
	}
	
/*	for ( it=explosions_collection.begin() ; it < explosions_collection.end(); it++)
	{
        (*it)->animate();
        if ((*it)->isEndAnimation())
        {
           delete (*it);
           explosions_collection.erase(it);
           n--;

        }      
     }
     */
}



void EnemyExplosions::drawAll(SDL_Surface* buffer)
{
	for ( unsigned int i=0; i<explosions_collection.size(); i++)
	{
		explosions_collection[i]->draw(buffer);
	}
}

bool EnemyExplosions::isEmpty()
{
	return explosions_collection.empty();
}


int EnemyExplosions::getn()
{
    return n;
}

int EnemyExplosions::getSize()
{
    return explosions_collection.size();
}
