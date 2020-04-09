
#include "MultipleSpriteMap.h"

MultipleSpriteMap::MultipleSpriteMap()
{
     surface=NULL;
	 loaded = false;
}



MultipleSpriteMap::MultipleSpriteMap(std::string filename)
{
	//Temporary storage for the image that's loaded 
	SDL_Surface* loadedImage = NULL; 

	//Load the image 
	loadedImage = SDL_LoadBMP( filename.c_str() ); 
	//If nothing went wrong in loading the image 
	if( loadedImage != NULL ) 
	{ 
		//Create an optimized image 
		surface = SDL_DisplayFormat( loadedImage );
		//Free the old image 
		SDL_FreeSurface( loadedImage ); 
		loaded = true;
	}        
	else
		loaded = false;
 
}
   
                             
MultipleSpriteMap::~MultipleSpriteMap()
{
	if (loaded)
		SDL_FreeSurface( surface );
}


void MultipleSpriteMap::draw ( SDL_Surface* destination, int inx, int iny, int x1, int y1, int w, int h)
{	
	if (loaded)
	{
		//Make a temporary rectangle to hold the offsets 
		SDL_Rect destinyrect;
		SDL_Rect sourcerect;

		//Give the offsets to the rectangle 
		destinyrect.x = inx; 
	    destinyrect.y = iny; 

		sourcerect.x=x1;
		sourcerect.y=y1;
		sourcerect.w=w;
		sourcerect.h=h;

		//Blit the surface 
		SDL_BlitSurface( surface, &sourcerect, destination, &destinyrect ); 
	}    
}



// set the RGB color that's going to be transparent
void MultipleSpriteMap::setTransparentColor(  int red, int green, int blue )
{
	if (loaded)
		SDL_SetColorKey(surface,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(surface->format,red,green,blue));
}


// sets the alpha channel - surface transparency
void MultipleSpriteMap::setAlpha( int intensity )
{     
	if (loaded)
		SDL_SetAlpha(surface,SDL_SRCALPHA|SDL_RLEACCEL,intensity);
}


// too slow???????????????????????????
SDL_Surface* MultipleSpriteMap::getAreaSurface(int x, int y, int w, int h)
{
	if (loaded)
	{
		SDL_Rect sourcerect;
		// We acquire the settings in our return surface
		SDL_Surface *temp = SDL_GetVideoSurface();

		// create the new surface using the Right-To_Left principle
		temp = SDL_CreateRGBSurface ( temp->flags, w, h,
			temp->format->BitsPerPixel,
			temp->format->Rmask,
			temp->format->Gmask,
			temp->format->Bmask,
			temp->format->Amask);

		if(surface->flags & SDL_SRCCOLORKEY) 
		{
			SDL_SetColorKey(temp, SDL_RLEACCEL|SDL_SRCCOLORKEY, surface->format->colorkey );
		}

		sourcerect.x=x;
		sourcerect.y=y;
		sourcerect.w=w;
		sourcerect.h=h;
		SDL_BlitSurface(surface, &sourcerect, temp, NULL);
		return SDL_ConvertSurface(temp, temp->format, SDL_SWSURFACE);
	}
	return NULL;

/*		SDL_Surface* titlerect=SDL_CreateRGBSurface(SDL_SWSURFACE, w, h,32,0,0,0,0);
	SDL_Rect sourcerect;

	sourcerect.x=x;
	sourcerect.y=y;
	sourcerect.w=w;                    
	sourcerect.h=h;

	SDL_BlitSurface(surface, &sourcerect, titlerect, NULL);
    return titlerect;     
*/	
}

SDL_Rect MultipleSpriteMap::getAreaRect(int x, int y, int w, int h)
{
	SDL_Rect temp;
	temp.x = x;
	temp.y = y;
	temp.w = w;
	temp.h = h;
	return temp;
}