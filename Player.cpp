
#include "Player.h"

Player::Player(std::string filename, int x, int y, double speed)// : Sprite (filename)
{
    SDL_Surface*  temp = IMG_Load( filename.c_str());
	if (temp != NULL)
	{
		sprite = SDL_DisplayFormat( temp );	
		SDL_FreeSurface( temp ); 		 
		loaded= true;			
	}
	else
		loaded = false;
	this->speed = speed;

    setTransparency(0,0,0);
    //setTransparency(explosion,0,0,0);
	
    setPos(x,y);

	shoots = new PlayerShoots("sprites/shoots2.bmp");
	lastshoot = timer;

    explosion = new AnimSprite("sprites/explosao.bmp", 8,150);
    explosion->setTransparency(0,0,0);
    exploding = false;
		
	setLives(8);
	status = true;
	
	shield = false;
	
    sound_player_shoot = new TSound("sounds/player_fire_2.wav");
	sound_player_shoot->setVolume(50);
	sound_player_shoot->setChannel(0);
    
    sound_player_explosion = new TSound("sounds/medium_exp.wav");
	sound_player_explosion->setVolume(50);
	sound_player_explosion->setChannel(0);

}

Player::~Player()
{
    if (loaded)
               SDL_FreeSurface(sprite);
               
    delete explosion;
                   
	delete shoots;
	
	delete sound_player_shoot;
	
	delete sound_player_explosion;
}


void Player::move(double dir)
{
     // only moves if not exploding
    if (!exploding)
    { 
	   stepx = (int) (cos ((dir*PI)/180) * speed);
	   stepy = (int) (sin ((-dir*PI)/180) * speed);
	   setPos(	x + stepx,	y + stepy);	
    }
}


void Player::draw(SDL_Surface* buffer)
{
    // only show the player if not exploding
    if (!exploding)
    {     
	      if ( loaded)
	      {
		     SDL_Rect dstrect;
             dstrect.x = x;
		     dstrect.y = y;
		     SDL_BlitSurface(sprite, NULL, buffer,&dstrect);
	      }
   }
   else
   {
       explosion->draw(buffer);
       explosion->animate();
       if (explosion->isEndAnimation())
       {
	      exploding = false;
	      explosion->resetAnimation();
	      setPos(400,500);
       }
           
   }

      if (shield && timer-shieldstart>6000)
      {
         shield = false;
         setAlpha(255);
      }


	shoots->moveall();

	shoots->draw(buffer);	

}


void Player::addShoot(double speed, double direction)
{
    if (!exploding)
    {
	   if(timer - lastshoot > 150)
	   {
             sound_player_shoot->play(0);
		     shoots->add(x+33, y-5, speed, direction);
             lastshoot = timer;
       }
    }	
}

PlayerShoots* Player::getPlayerShoots()
{
	return shoots;
}


void Player::setTransparency(int r, int g, int b) {
    if(loaded)
		SDL_SetColorKey(sprite, SDL_SRCCOLORKEY,SDL_MapRGB(sprite->format, r, g, b));
}

void Player::setAlpha( int intensity )
{     
     SDL_SetAlpha(sprite,SDL_SRCALPHA|SDL_RLEACCEL,intensity);
}


int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}


void Player::setX(int x)
{
	this->x = x;
}

void Player::setY(int y)
{
	this->y = y;
}

void Player::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}


SDL_Rect& Player::getPlayerRect()
{
	temprect.x=x;
	temprect.y=y;
	temprect.w=sprite->w;
	temprect.h=sprite->h;
	return temprect;
}


void Player::setLives(int l)
{
     lives = l;
}

int Player::getLives()
{
    return lives;
}

bool Player::getStatus()
{
     if (lives<0)
          return false;
    else
          return true;
}

void Player::setExplosion(bool exp)
{
        sound_player_explosion->play(0);
        exploding = true;
        lives = lives - 1;
        explosion->setPos(x,y);
        shield = true;
        setAlpha(150);
        shieldstart = timer;
}

bool Player::getShieldStatus()
{
     return shield;     
}
