#ifndef Enemy_h
#define Enemy_h

#include <vector>

#include "Sprite.h"
#include "EnemyShoots.h"

#include "SDL_collide.h"


extern double PI;

enum ENEMY_TYPES { TYPE_I, TYPE_II, TYPE_III, TYPE_IV, TYPE_V, TYPE_VI };


using std::vector;

class Enemy
{
public:
	Enemy(std::string filename);
	virtual ~Enemy();


	void moveall(int gps, int player_x, int player_y);		// player coord necessary for ai purposes
	void draw(SDL_Surface* buffer, int gps);



	bool isEmpty();			// returns true of no elements

	int getNumberOfEnemies();				// returns the number of enemies 

	SDL_Rect& getEnemyRect(int index);		// returns the rect of enemy index


	int getX(int index);
	int getY(int index);

	void remove(int index);
	
	EnemyShoots* getEnemyShoots();


private:

	//void add(int x, int y, double speed, int gps, ENEMY_TYPES type);
	void add(int gps, ENEMY_TYPES type);
	void checkBoundaries(int index);

	int getDirection(int x1, int y1, int x2, int y2);		// get direction from 1 to 2 in degrees


	Sprite* sprite;
	//double enemy_direction, enemy_speed;
	//double enemy_direction, enemy_speed;

	EnemyShoots* shoots;


	// each enemy's position
	struct Enemy_Collection
	{
		int enemy_x,enemy_y;		// enemy's position
		int gps;					// when will the enemy appear
		double speed;
		ENEMY_TYPES type;
		bool aux;
		double direction;
	} enemy;

	vector<Enemy_Collection> enemy_collection;

	bool temp_bool;
	SDL_Rect dstrect;
	int stepx, stepy;




};




#endif

