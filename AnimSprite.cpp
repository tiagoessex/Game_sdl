
#include "AnimSprite.h"

#include <windows.h>

/*
AnimSprite::AnimSprite()
{
                        
                            Beep(523,100);
	system("PAUSE");
                        
	sprite = NULL;
	loaded = false;
	
	setX(0);
	setY(0);
	frames = 0;
	speed = 0;
	index = 0;
	run = false;

	framewidth = 0;
	frameheight = 0;

	temp = NULL;
	end_animation=false;
}
*/

AnimSprite::AnimSprite(std::string filename, int frames, int speed)
{
      /*                                 Beep(523,100);
	system("PAUSE");
        */
                                   
	temp = IMG_Load( filename.c_str());
	if (temp != NULL)
	{
		sprite = SDL_DisplayFormat( temp );	
	//	SDL_FreeSurface( temp ); 		 
		loaded= true;			
	}
	else
		loaded = false;

	setX(0);
	setY(0);

	if (loaded)
	{
		framewidth = (int) sprite->w/frames;
		frameheight = sprite->h;
		this->frames = frames;
		this->speed = speed;
		index = 0;	
		lastanimated = timer;
		run = true;

		temp = NULL;
	}
	else
	{
		framewidth = 0;
		frameheight = 0;
		this->frames = 0;
		this->speed = 0;
		index = 0;	
		lastanimated = timer;
		run = false;

		temp = NULL;
	}
	end_animation=false;

}

AnimSprite::AnimSprite(SDL_Surface* surface, int frames, int speed)
{
      /*                                  Beep(523,100);
	system("PAUSE");
        */                            
  if(surface == NULL) 
	{
        sprite = NULL;
        loaded = false;
    } 
	else 
	{
        sprite = NULL;
/* 
			// We acquire the settings in our return surface
		sprite = SDL_GetVideoSurface();
		
		// create the new surface using the Right-To_Left principle
		sprite = SDL_CreateRGBSurface ( sprite->flags, surface->w, surface->h,
			sprite->format->BitsPerPixel,
			sprite->format->Rmask,
			sprite->format->Gmask,
			sprite->format->Bmask,
			sprite->format->Amask);

        if(surface->flags & SDL_SRCCOLORKEY) 
		{
            SDL_SetColorKey(sprite, SDL_RLEACCEL|SDL_SRCCOLORKEY, surface->format->colorkey );
        }

		sprite = SDL_ConvertSurface(surface, surface->format, SDL_SWSURFACE);
*/

if(surface->flags & SDL_SRCCOLORKEY) {
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
        }
		else
		{
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
        }


        loaded = true;
    }
	
	setX(0);
	setY(0);

	if (loaded)
	{
		framewidth = (int) sprite->w/frames;
		frameheight = sprite->h;
		this->frames = frames;
		this->speed = speed;
		index = 0;	
		lastanimated = timer;
		run = true;

		temp = NULL;
	}
	else
	{
		framewidth = 0;
		frameheight = 0;
		this->frames = 0;
		this->speed = 0;
		index = 0;	
		lastanimated = timer;
		run = false;

		temp = NULL;
	}
	end_animation=false;
}



AnimSprite::AnimSprite(SDL_Surface* surface, int frames, int speed, int x, int y)
{
    /*Beep(523,100);
	system("PAUSE");
	*/
	
	if(surface == NULL) 
	{
        sprite = NULL;
        loaded = false;
    } 
	else 
	{
        sprite = NULL;
 
 /*
		sprite = SDL_GetVideoSurface();
	
		sprite = SDL_CreateRGBSurface ( sprite->flags, surface->w, surface->h,
			sprite->format->BitsPerPixel,
			sprite->format->Rmask,
			sprite->format->Gmask,
			sprite->format->Bmask,
			sprite->format->Amask);

        if(surface->flags & SDL_SRCCOLORKEY) 
		{
            SDL_SetColorKey(sprite, SDL_RLEACCEL|SDL_SRCCOLORKEY, surface->format->colorkey );
        }

		sprite = SDL_ConvertSurface(surface, surface->format, SDL_SWSURFACE);

*/
     if(surface->flags & SDL_SRCCOLORKEY) {
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
        }
		else
		{
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
        }

        loaded = true;
    }


	if (loaded)
	{
		framewidth = (int) sprite->w/frames;
		frameheight = sprite->h;
		this->frames = frames;
		this->speed = speed;
		index = 0;	
		lastanimated = timer;
		run = true;

		temp = NULL;
		setPos(x,y);
	}
	else
	{
		framewidth = 0;
		frameheight = 0;
		this->frames = 0;
		this->speed = 0;
		index = 0;	
		lastanimated = timer;
		run = false;

		temp = NULL;
		setPos(x,y);
	}
	end_animation=false;
}


AnimSprite::~AnimSprite()
{

	if (temp!=NULL)
		SDL_FreeSurface(temp);
    
    SDL_FreeSurface(sprite);
		
}


void AnimSprite::destroy()
{	
	if (temp!=NULL)
		SDL_FreeSurface(temp);
		SDL_FreeSurface(sprite);
}


void AnimSprite::animate()
{
	if(run)		
	{
		if(timer - lastanimated > speed)
		{
			lastanimated = timer;
			index++;
            if(index >= frames)
			{
				end_animation=true;
				index = 0;
			}
		}
	}    

}

void AnimSprite::draw(SDL_Surface* buffer)
{
	if (loaded)
	{
		SDL_Rect dstrect;
		dstrect.x = x;
		dstrect.y = y;
		
		// this blits the current frame from the sprite sheet
		SDL_Rect animRect;
		animRect.x = framewidth*index;
		animRect.y = 0;
		animRect.w = framewidth;
		animRect.h = frameheight;
		
		SDL_BlitSurface(sprite, &animRect, buffer,&dstrect);
	}
}

void AnimSprite::draw(SDL_Surface* buffer, int wherex, int wherey)
{
	if (loaded)
	{
		SDL_Rect dstrect;
		dstrect.x = wherex;
		dstrect.y = wherey;
		
		// this blits the current frame from the sprite sheet
		SDL_Rect animRect;
		animRect.x = framewidth*index;
		animRect.y = 0;
		animRect.w = framewidth;
		animRect.h = frameheight;
		
		SDL_BlitSurface(sprite, &animRect, buffer,&dstrect);
	}
}

int AnimSprite::getIndex()
{
	return index;
}



SDL_Surface* AnimSprite::getCurrentFrameSurface()
{
	if (loaded)
	{
		SDL_Rect sourcerect;

		temp = SDL_GetVideoSurface();
		temp = SDL_CreateRGBSurface ( temp->flags, framewidth, frameheight,
			temp->format->BitsPerPixel,
			temp->format->Rmask,
			temp->format->Gmask,
			temp->format->Bmask,
			temp->format->Amask);
//	*****************
		if(sprite->flags & SDL_SRCCOLORKEY) {
			SDL_SetColorKey(temp, SDL_RLEACCEL|SDL_SRCCOLORKEY, sprite->format->colorkey );
		}
//	*****************
		sourcerect.x=index*framewidth;
		sourcerect.y=0;
		sourcerect.w=framewidth;
		sourcerect.h=frameheight;
		SDL_BlitSurface(sprite, &sourcerect, temp, NULL);
		return SDL_ConvertSurface(temp, temp->format, SDL_SWSURFACE);
	}
	return 0;
}


SDL_Rect& AnimSprite::getCurrentFrameBox()
{
	
	temprect.x=x;
	temprect.y=y;
	temprect.w=framewidth;
	temprect.h=frameheight;
	return temprect;
}


bool AnimSprite::isEndAnimation()
{
	return end_animation;
}


void AnimSprite::setTransparency(int r, int g, int b) {
    if(loaded)
		SDL_SetColorKey(sprite, SDL_SRCCOLORKEY,SDL_MapRGB(sprite->format, r, g, b));
}

void AnimSprite::setTransparency(Uint32 colorkey) {
	if (loaded)
		sprite->format->colorkey = colorkey;
}

bool AnimSprite::isLoaded()
{
	return loaded;
}

void AnimSprite::setAlpha( int intensity )
{     
     SDL_SetAlpha(sprite,SDL_SRCALPHA|SDL_RLEACCEL,intensity);
}



int AnimSprite::getX()
{
	return x;
}

int AnimSprite::getY()
{
	return y;
}


void AnimSprite::setX(int x)
{
	this->x = x;
}

void AnimSprite::setY(int y)
{
	this->y = y;
}

void AnimSprite::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}


void AnimSprite::resetAnimation()
{
//     index = 0;    
     end_animation = false;
}

/*
AnimSprite::AnimSprite(const AnimSprite& original)
{
	
	sprite = NULL;

	sprite = SDL_GetVideoSurface();
		
		// create the new surface using the Right-To_Left principle
	sprite = SDL_CreateRGBSurface ( sprite->flags, original.sprite->w, original.sprite->h,
			sprite->format->BitsPerPixel,
			sprite->format->Rmask,
			sprite->format->Gmask,
			sprite->format->Bmask,
			sprite->format->Amask);

	if(original.sprite->flags & SDL_SRCCOLORKEY) 
	{
		SDL_SetColorKey(sprite, SDL_RLEACCEL|SDL_SRCCOLORKEY, original.sprite->format->colorkey );
	}

	sprite = SDL_ConvertSurface(original.sprite, original.sprite->format, SDL_SWSURFACE);

	loaded=true;
	
	
	framewidth = original.framewidth;
	frameheight = original.frameheight;
	frames = original.frames;
	speed = original.speed;
	index = original.index;	
	timer = original.lastanimated;
	run = original.run;
	temp = original.temp;
	end_animation=false;
	x = original.x;
	y = original.y;
		

}


AnimSprite& AnimSprite::operator=(const AnimSprite& original)
{
            
             Beep(523,100);
	system("PAUSE");
	
	
	if (this != &original)		// check if not self assigment
	{
		SDL_FreeSurface(sprite);


		sprite = SDL_GetVideoSurface();
		
		// create the new surface using the Right-To_Left principle
		sprite = SDL_CreateRGBSurface ( sprite->flags, original.sprite->w, original.sprite->h,
			sprite->format->BitsPerPixel,
			sprite->format->Rmask,
			sprite->format->Gmask,
			sprite->format->Bmask,
			sprite->format->Amask);

		if(original.sprite->flags & SDL_SRCCOLORKEY) 
		{
			SDL_SetColorKey(sprite, SDL_RLEACCEL|SDL_SRCCOLORKEY, original.sprite->format->colorkey );
		}

		sprite = SDL_ConvertSurface(original.sprite, original.sprite->format, SDL_SWSURFACE);
		
		loaded=true;
	}
	else
	{
		loaded=false;
	}
	
		
	framewidth = original.framewidth;
	frameheight = original.frameheight;
	frames = original.frames;
	speed = original.speed;
	index = original.index;	
	timer = original.lastanimated;
	run = original.run;
	temp = original.temp;
	end_animation=false;
	x = original.x;
	y = original.y;

	return *this;
}
*/
