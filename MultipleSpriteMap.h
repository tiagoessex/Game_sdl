#pragma once

/*
  sprite class for files with multiple sprites in one surface
  enables to chose wich part of the surface to display
*/

/* NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET
 NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET NOT DONE YET
  
	missing: getRect / getRectSurface for collision
  */
  
#ifndef MultipleSpriteMap_H_
#define MultipleSpriteMap_H_

#include <iostream>
#include "SDL.h"



 

class MultipleSpriteMap {
      public:
			 MultipleSpriteMap();
			 MultipleSpriteMap(std::string filename);

             // free mem
             ~MultipleSpriteMap();
             
             // draw sprite at destiny surface
			 // x1, y1 -> upper left corner | w, h -> width, height
			 // inx, iny -> coord to draw on destination
			 void draw (SDL_Surface* destination, int inx, int iny, int x1, int y1, int w, int h);
             
             // set the RGB color that's going to be transparent
             void setTransparentColor( int red, int green, int blue );

             // sets the alpha channel - surface transparency
             void setAlpha( int intensity );

			 SDL_Surface* getAreaSurface(int x, int y, int w, int h);	// too slow
			 SDL_Rect getAreaRect(int x, int y, int w, int h);

      protected:
		  SDL_Surface* surface;			// surfece where sprite is
		  bool loaded;		 
			
};



#endif
