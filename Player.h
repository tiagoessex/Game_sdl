#ifndef Player_h
#define Player_h

#include "AnimSprite.h"
#include "PlayerShoots.h"

#include "TSound.h"

extern double PI;
extern long timer;


class Player      // : public Sprite
{
public:
	Player(std::string filename, int x, int y, double speed);
	virtual ~Player();


    void setTransparency(int r, int g, int b);
    void setAlpha( int intensity );

	void move(double dir);

	void addShoot(double speed, double direction);

	virtual void draw(SDL_Surface* buffer);		// draws and moves shoots
	
	PlayerShoots* getPlayerShoots();


	int getX();
	int getY();

	void setX(int);
	void setY(int);
	void setPos(int, int);

	

	SDL_Rect& getPlayerRect();
	
	void setLives(int l);
	int getLives();
	bool getStatus();                        // returns true if alive else false
	
	void setExplosion(bool exp);                // set on for player to explode - it reduces a live also

    bool getShieldStatus();

private:
	SDL_Surface* sprite;
	AnimSprite* explosion;
	TSound* sound_player_shoot;
	TSound* sound_player_explosion;
	
	double speed;

	int stepx;
	int stepy;
	
	int x,y;
	SDL_Rect temprect;
	

	PlayerShoots* shoots;

	long lastshoot;
	
    bool loaded;				// true if sprite loaded with sucess
    
    bool exploding;            // if it's currently exploding
    
    int lives;
    bool status;
    
    bool shield;                  // after dead 5 s as phantom
    long shieldstart;

};



#endif

