
#include "Sprite.h"

Sprite::Sprite()
{
	sprite = NULL;
	loaded = false;
	
	setX(0);
	setY(0);
}


Sprite::Sprite(std::string filename)
{
/*	Beep(523,100);
	system("PAUSE");
*/

	SDL_Surface*  temp = IMG_Load( filename.c_str());
	if (temp != NULL)
	{
		sprite = SDL_DisplayFormat( temp );	
		SDL_FreeSurface( temp ); 		 
		loaded= true;			
	}
	else
		loaded = false;

	setX(0);
	setY(0);
}




// overload com um sem x,y
Sprite::Sprite(SDL_Surface* surface) 
{
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
}


/*
Sprite::Sprite(const Sprite& original)
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
*/	
/*

if(surface->flags & SDL_SRCCOLORKEY) {
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
        }
		else
		{
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
        }
*/
/*
	loaded=true;

}
*/

Sprite& Sprite::operator=(const Sprite& original)
{
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
	
/*
		if(surface->flags & SDL_SRCCOLORKEY) {
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
        }
		else
		{
            sprite = SDL_CreateRGBSurfaceFrom(surface->pixels, surface->w, surface->h, surface->format->BitsPerPixel, surface->pitch,
                surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
        }
*/

		loaded=true;
	}
	else
	{
		loaded=false;
	}

	return *this;
}



/*
SDL_Surface* Sprite::makeCopy()
{
	return SDL_ConvertSurface(sprite, sprite->format, SDL_SWSURFACE);
}

*/

SDL_Surface* Sprite::getSurface()
{
	return sprite;
}




Sprite::~Sprite()
{
	SDL_FreeSurface(sprite);
}


void Sprite::setTransparency(int r, int g, int b) {
    if(loaded)
		SDL_SetColorKey(sprite, SDL_SRCCOLORKEY,SDL_MapRGB(sprite->format, r, g, b));
}

void Sprite::setTransparency(Uint32 colorkey) {
	if (loaded)
		sprite->format->colorkey = colorkey;
}

bool Sprite::isLoaded()
{
	return loaded;
}


void Sprite::setAlpha( int intensity )
{     
     SDL_SetAlpha(sprite,SDL_SRCALPHA|SDL_RLEACCEL,intensity);
}

void Sprite::draw(SDL_Surface* buffer) 
{
	if (isLoaded())
	{
		SDL_Rect dstrect;
		dstrect.x = x;
		dstrect.y = y;
		SDL_BlitSurface(getSurface(), NULL, buffer,&dstrect);
	}
}


void Sprite::draw(SDL_Surface* buffer, int where_x, int where_y) 
{
	if (isLoaded())
	{
		SDL_Rect dstrect;
		dstrect.x = where_x;
		dstrect.y = where_y;
		SDL_BlitSurface(getSurface(), NULL, buffer,&dstrect);
	}
}


int Sprite::getX()
{
	return x;
}

int Sprite::getY()
{
	return y;
}


void Sprite::setX(int x)
{
	this->x = x;
}

void Sprite::setY(int y)
{
	this->y = y;
}

void Sprite::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}


SDL_Rect& Sprite::getBox()
{
	temprect.x=x;
	temprect.y=y;
	temprect.w=getSurface()->w;
	temprect.h=getSurface()->h;
	return temprect;
}
