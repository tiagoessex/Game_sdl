#ifndef main_h
#define main_h

#include <ctime> 

#include "SDL_image.h"
#include "SDL_collide.h"

#include "timer.h"

#include "TFont.h"
#include "TSound.h"
#include "TMusic.h"

#include "Sprite.h"
#include "AnimSprite.h"
#include "PlayerShoots.h"

#include "Player.h"
#include "Enemy.h"
#include "EnemyExplosions.h"


#include <vector>


// ************************
// remove if no collide in main
//#define SPRITE_MAX(a,b)	((a > b) ? a : b)
//#define SPRITE_MIN(a,b)	((a < b) ? a : b)
// ************************

long timer; // this will be used as the global timer

double PI; //=3.14159265;



#endif
