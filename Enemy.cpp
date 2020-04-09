
#include "Enemy.h"

Enemy::Enemy(std::string filename)
{
	sprite = new Sprite(filename);
	sprite->setTransparency(0,0,0);

	shoots = new EnemyShoots("sprites/bullet_ene.jpg");



    for (int i=0; i<10; i++)
    {
	    add(rand()%10000 + 200,TYPE_I);
	    add(rand()%10000 + 200,TYPE_II);
	    add(rand()%10000 + 200,TYPE_III);
	    add(rand()%10000 + 200,TYPE_VI);
	    add(rand()%10000 + 200,TYPE_V);
	    add(rand()%10000 + 200,TYPE_VI);           		
     }

	
}


Enemy::~Enemy()
{
               delete sprite;
	delete shoots;

}

void Enemy::moveall(int gps, int player_x, int player_y)
{
	for ( unsigned int i=0; i<enemy_collection.size(); i++)
	{
		if ( enemy_collection[i].gps < gps)
		{

			if (enemy_collection[i].type == TYPE_V)
			{
				if (enemy_collection[i].enemy_y>(rand()%200+200) && !enemy_collection[i].aux)
				{
					enemy_collection[i].aux = true;
					enemy_collection[i].direction = 45;
				}
				if (!enemy_collection[i].aux)
					enemy_collection[i].direction = 315;
				else 
					enemy_collection[i].direction = 45;
			}
			else if (enemy_collection[i].type == TYPE_VI)
			{
				if (enemy_collection[i].enemy_y>(rand()%200+200) && !enemy_collection[i].aux)
				{
					enemy_collection[i].aux = true;
					enemy_collection[i].direction = 135;
				}
				if (!enemy_collection[i].aux)
					enemy_collection[i].direction = 225;
				else 
					enemy_collection[i].direction = 135;
			}
			


			stepx = (int) (cos ((enemy_collection[i].direction*PI)/180) * enemy_collection[i].speed);
			stepy = (int) (sin ((-enemy_collection[i].direction*PI)/180) * enemy_collection[i].speed);
			
			enemy_collection[i].enemy_x +=stepx;
			enemy_collection[i].enemy_y +=stepy;


			// shoots life = f(space) extension
			checkBoundaries(i);

			// enemy shoots
			if (rand()%40 == 1)	// if = 1 then shoot (1/40 probability)
			{
				shoots->add(enemy_collection[i].enemy_x+33, enemy_collection[i].enemy_y+5,5,
					-getDirection(player_x, player_y, enemy_collection[i].enemy_x, enemy_collection[i].enemy_y));
			}

		}

	}
	
	// move enemies shoots
	shoots->moveall();

}


void Enemy::checkBoundaries(int index)
{
    if ((enemy_collection[index].enemy_y>610) || enemy_collection[index].enemy_y<-70
       || enemy_collection[index].enemy_x>810 || enemy_collection[index].enemy_x<-10)
			enemy_collection.erase(enemy_collection.begin()+index);		
	
}




void Enemy::draw(SDL_Surface* buffer, int gps)
{
	for ( unsigned int i=0; i<enemy_collection.size(); i++)
	{
		if ( enemy_collection[i].gps < gps)
		{
			dstrect.x = enemy_collection[i].enemy_x;
			dstrect.y = enemy_collection[i].enemy_y;
			SDL_BlitSurface(sprite->getSurface(), NULL, buffer,&dstrect);
		}
	}


	// draw enemies shoots
	shoots->draw(buffer);

}



//void Enemy::add(int x, int y, double speed, int gps, ENEMY_TYPES type)
void Enemy::add(int gps, ENEMY_TYPES type)
{
	int temp_x, temp_y;

	switch (type)
	{
	case TYPE_I: 
		enemy.enemy_x = (int) (rand()%700 + 50);
		enemy.enemy_y = 0;
		enemy.speed = (int) (rand()%3+2);	
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 270;
		enemy_collection.push_back(enemy);	
		break;
	case TYPE_II: 
		enemy.enemy_y = (int) (rand()%250+ 50);
		enemy.enemy_x = 0;
		enemy.speed = (int) (rand()%3+2);	
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 0;
		enemy_collection.push_back(enemy);	
		break;
	case TYPE_III: 
		temp_x = (int) (rand()%700+ 50);
		temp_y = 0;
		enemy.enemy_y = temp_y;
		enemy.enemy_x = temp_x;
		enemy.speed = 2;	
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 270;
		enemy_collection.push_back(enemy);	
		enemy.enemy_y = temp_y - 60;
		enemy.enemy_x = temp_x - 60;
		enemy.speed = 2;
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 270;
		enemy_collection.push_back(enemy);	
		enemy.enemy_y = temp_y - 60;
		enemy.enemy_x = temp_x + 60;
		enemy.speed = 2;
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 270;
		enemy_collection.push_back(enemy);	
		break;
	case TYPE_IV: 
		temp_x = (int) (rand()%700+ 50);
		temp_y = 0;
		enemy.enemy_y = temp_y;
		enemy.enemy_x = temp_x;
		enemy.speed = 2;	
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 270;
		enemy_collection.push_back(enemy);	
		enemy.enemy_y = temp_y - 30;
		enemy.enemy_x = temp_x - 45;
		enemy.speed = 2;
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 270;
		enemy_collection.push_back(enemy);	
		enemy.enemy_y = temp_y - 60;
		enemy.enemy_x = temp_x - 90;
		enemy.speed = 2;
		enemy.gps = gps;	
		enemy.type = type;
		enemy.direction = 270;
		enemy_collection.push_back(enemy);	
		break;
	case TYPE_V: 
		enemy.enemy_x = (int) (rand()%400);
		enemy.enemy_y = 0;
		enemy.speed = (int) (rand()%3+2);	
		enemy.gps = gps;	
		enemy.type = type;
		enemy.aux = false;
		enemy.direction = 45;
		enemy_collection.push_back(enemy);	
		break;
	case TYPE_VI: 
		enemy.enemy_x = (int) (rand()%200+500);
		enemy.enemy_y = 0;
		enemy.speed = (int) (rand()%3+2);	
		enemy.gps = gps;	
		enemy.type = type;
		enemy.aux = false;
		enemy.direction = 225;
		enemy_collection.push_back(enemy);	
		break;
	default: break;
	}


}

void Enemy::remove(int index)
{
	enemy_collection.erase(enemy_collection.begin()+index);
}

bool Enemy::isEmpty()
{
	return enemy_collection.empty();
}

int Enemy::getDirection(int x1, int y1, int x2, int y2)
{
	return (int) ( atan2((double)(y1-y2),(x1-x2)) * 180 / PI);
}

int Enemy::getNumberOfEnemies()
{
	return enemy_collection.size();
}

SDL_Rect& Enemy::getEnemyRect(int index)
{
		//SDL_Rect temprect;
	dstrect.x=enemy_collection[index].enemy_x;
	dstrect.y=enemy_collection[index].enemy_y;
	dstrect.w=sprite->getSurface()->w;
	dstrect.h=sprite->getSurface()->h;
	return dstrect;

}



int Enemy::getX(int index)
{
	return enemy_collection[index].enemy_x;
}

int Enemy::getY(int index)
{
	return enemy_collection[index].enemy_y;
}


EnemyShoots* Enemy::getEnemyShoots()
{
             return shoots;
}
