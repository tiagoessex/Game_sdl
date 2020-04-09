/*
*********************************************

	GAME-SDL-001
	2009

*********************************************
*/


#include "main.h"


// frames per second 
const int FRAMES_PER_SECOND = 100; 

// players keys
Uint8 *keys;
// keys events
SDL_Event keyevent;


// visible world
SDL_Surface* screen;


// sprites

Player* player;

Enemy* enemigos;


Sprite* start;



// ************ background
Sprite* background;
int posx=0;

// ************ FPS 
 int frame;
 int fpsmax;
//Timer used to update the caption
Timer update;		
Timer fps;
Timer fpscontrol;


// fonts
TFont* fonte1=NULL;

// sound related
// number max of chanel to reproduce the sounds
const int NUMBERCHANELS=5;


// sounds and music
TMusic* game_music=NULL;
int volumemusic=50;

  TSound* sound_enemy_explosion;


// others
bool running;


// game position
int game_position;

EnemyExplosions* enemy_explosions;

double points;


void LoadSprites() 
{
    start = new Sprite ("sprites/start.jpg");
    start->setPos(0,0);




	player = new Player("sprites/player.bmp",400,100,5);

	enemigos = new Enemy("sprites/enemy1.bmp");

	
	// ************ background tests
	background = new Sprite("sprites/starfield.jpg");
	background->setPos(0,0);
//	background->setTransparency(0,0,0);

	enemy_explosions = new EnemyExplosions("sprites/explosao.bmp",8,400);


}


void loadFonts()
{
	fonte1=new TFont("fonts/arial.ttf",20);
	fonte1->setColor(255,255,255,0,0,0);
}

void loadSounds()
{
    sound_enemy_explosion = new TSound("sounds/smal_exp.wav");
	sound_enemy_explosion->setVolume(50);
	sound_enemy_explosion->setChannel(1);
	
}

void loadMusics()
{
	game_music=new TMusic ("music/intro.mid");
	game_music->setVolume(30);
}


// frees mem from all entities
void clearMem() 
{
	delete fonte1;

	//delete sound_explosion;
	delete game_music;


	delete player;

	delete enemigos;
	
	
	delete background;




//	delete sound_player_shoot;

	delete enemy_explosions;

delete start;

delete sound_enemy_explosion;



}


// show only a portion  - rect - of a suface
// used for background scroll
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}


void clearScreen() {
	// clear background to black, RGB(0,0,0)
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
}

// draw all entities
void drawWorld() 
{	
    // background
	background->draw(screen,0, posx);	
	background->draw(screen,0,posx - background->getSurface()->h);	
	posx++;
	background->setY(posx);
	if( posx >= background->getSurface()->h )
		posx=0;


	player->draw(screen);

	if (!enemigos->isEmpty())
	{
		enemigos->draw(screen, game_position);
		enemigos->moveall(game_position, player->getX(), player->getY());
	}



	if (!enemy_explosions->isEmpty())
	{
		enemy_explosions->drawAll(screen);
		enemy_explosions->animate();
	}

}

void printNumber(int n, int x, int y)
{
	char buffer1[5];	
	_itoa (n,buffer1,10);		// int do char*
	//_itoa_s(n,buffer1,10);
	fonte1->drawText(buffer1,screen,1,x,y);
}

void drawText()
{
	fonte1->drawText("Lives - ",screen,1,650,550);
    printNumber (player->getLives(),730,550);
    
    fonte1->drawText("Points - ",screen,1,650,575);
    printNumber ((int) points,730,575);
    
    fonte1->drawText("GPS - ",screen,1,10,10);
    printNumber (game_position,70,10);
    
    fonte1->drawText("FPS - ",screen,1,10,550);    
	printNumber (fpsmax,70,550);
}



void initSDL()
{
	//if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{
        printf( "Unable to init SDL: %s\n", SDL_GetError());
        running = false;
    }
    // ensure a clean exit
    atexit(SDL_Quit);
    // create a new window
    screen = SDL_SetVideoMode(800, 600, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption( "GAME ENGINE TEST 1", "GAME ENGINE TEST 1" );
    if ( !screen ) {
        printf("Unable to set 800X600 video: %s\n", SDL_GetError());
        running = false;
    }

}

// init SDL_tff - truetype fonts
void initSDL_tff()
{
	if(TTF_Init()==0)
	{
		atexit(TTF_Quit);
	}
}

// init audio system
int initSDL_mixer()
{
	Mix_AllocateChannels(NUMBERCHANELS);
	// 3~param => 1 -> mono | 2 -> stereo
	// MIX_DEFAULT_FREQUENCY -> 22050
	// MIX_DEFAULT_FORMAT -> AUDIO_S16SYS
	// MIX_DEFAULT_CHANNELS -> 2
	return Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

	// to check if all ok
	// int Mix_QuerySpec(int *frequency,Uint16 *format,int *channels);
}



bool checkCollision()
{
		
		return false;		

}


void checkEnemyCollisions()
{
	for (int i=0; i<enemigos->getNumberOfEnemies(); i++)
	{
		for (int k=0; k<player->getPlayerShoots()->getSize(); k++)
		{
			if (SDL_CollideBoundingBox(enemigos->getEnemyRect(i), player->getPlayerShoots()->getPlayerShootRect(k)))
			{
               sound_enemy_explosion->play(0);                                                                                                                                    
				enemy_explosions->add(enemigos->getX(i), enemigos->getY(i));
				enemigos->remove(i);
				player->getPlayerShoots()->remove(k);
				points += 10;
			}

		}
		

	}
}

void checkPlayerCollisions()
{
     if (!player->getShieldStatus())
     {
        // agains a enemy
        for (int i=0; i<enemigos->getNumberOfEnemies(); i++)
        {
            if (SDL_CollideBoundingBox(enemigos->getEnemyRect(i), player->getPlayerRect()))
		    {
               sound_enemy_explosion->play(0);                                                                   
               enemy_explosions->add(enemigos->getX(i), enemigos->getY(i));
			   enemigos->remove(i);
			   player->setExplosion(true);
			   points += 10;
            }    
         
         }
         
         // agaisnt a enemy shoot
        for (int i=0; i<enemigos->getEnemyShoots()->getSize(); i++)
        {
            if (SDL_CollideBoundingBox(enemigos->getEnemyShoots()->getEnemyShootRect(i), player->getPlayerRect()))
		    {
			   enemigos->getEnemyShoots()->remove(i);
			   player->setExplosion(true);
            }    
         
         }
         
         
     }
     
}


void initAll()
{
	initSDL();
	initSDL_tff();
	initSDL_mixer();


	LoadSprites();
	loadFonts();
	loadSounds();
	loadMusics();

	srand((unsigned)time(0));

	PI=3.14159265;
	
	
	frame = 0;
	game_position = 0;
	fpsmax = 0;
	
	points = 0;
	
	posx=0;   

	timer = SDL_GetTicks();
	update.start();
	fps.start();
}

void closeAll()
{    
	//Quit SDL_ttf 
	TTF_Quit(); 

	// quit SDL_mixer
	Mix_CloseAudio();

	//Quit SDL 
    SDL_Quit();  
}


void fpsCalc()
{
		
//	max FPS
        //Increment the frame counter
        frame++;
		//If a second has passed since the caption was last updated
        if( update.get_ticks() > 1000 )
        {
			fpsmax = (int) (frame / ( fps.get_ticks() / 1000.f));

            //Restart the update timer
            update.start();
			
        }
}


int startScreen()
{
    

	game_music->fadeIn(-1,10000);
	game_music->play(-1);
	
 bool exit =false;
         start->draw(screen);           

        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
        
     while (!exit)
     {



     SDL_PollEvent(&keyevent);
        switch(keyevent.type) 
		{
            case SDL_KEYDOWN:
                switch(keyevent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;                      
                        exit = true;
                        break;
                    case SDLK_SPACE:
                        running = true;                     
                        exit = true;
                        delete game_music;
                       	game_music=new TMusic ("music/music2.mid");
                       	game_music->setVolume(30);
                        game_music->play(-1);
                        break;                        
				    default:
                        break;                        
                }
            default:
                break;
		}
  }  
}




int main ( int argc, char* argv[] ) 
{

	initAll();

    startScreen();
    

    while(running && player->getStatus()) 
    {                   

	fpscontrol.start();

        timer = SDL_GetTicks(); // always update the timer
		

		clearScreen();

		drawWorld();
		drawText();

		game_position++;
        
        fpsCalc();   


		checkEnemyCollisions();
        checkPlayerCollisions();

			

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        
        // check keyboard - for independent threads treatment
		keys=SDL_GetKeyState(NULL);
		
		
		if (keys[SDLK_UP] && !checkCollision() && player->getY()>10)
			//if (!checkCollision() ) 
			{
				//player->setY(player->getY() - 5); //sprite2->move(90);
				player->move(90);
			}

		if (keys[SDLK_DOWN] && !checkCollision() && player->getY()<550)
			//if (!checkCollision() ) 
			{
				//player->setY(player->getY() + 5); //sprite2->move(270);
				player->move(270);
			}

		if (keys[SDLK_LEFT] && !checkCollision() && player->getX()>10)
		//	if (!checkCollision() ) 
			{
				//player->setX(player->getX() - 5); //sprite2->move(180);
				player->move(180);
			}

		if (keys[SDLK_RIGHT] && !checkCollision() && player->getX()<750)
		//	if (!checkCollision() ) 
			{	
				//player->setX(player->getX() + 5); //sprite2->move(0);
				player->move(0);
			}

		if (keys[SDLK_SPACE])
		{	
			//	sound_player_shoot->play(0);
				player->addShoot(6, 90);
		}


        SDL_PollEvent(&keyevent);
        switch(keyevent.type) 
		{
            case SDL_KEYDOWN:
                printf("key down\n");
                switch(keyevent.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
				    default:
                        break;                        
                }
            default:
                break;
		}


		//Cap the frame rate
      if( fpscontrol.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fpscontrol.get_ticks() );
        }


}

	clearMem();

	closeAll();
    return 0;

}





