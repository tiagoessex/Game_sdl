

/*

		USE THIS ONLY FOR CHANGING TEXT - IF OTHERWISE DO NOT - CAUSES UNECESSARY OVERHEAD

*/

#pragma once

#ifndef TFONT_H_
#define TFONT_H_

#include "SDL_ttf.h"
#include <string>

using namespace std;

class TFont
{
	public:
		// default - font:times.ttf size:10 colors:black/white
		TFont();
		// name and size
		TFont(string filename, int l);

		virtual ~TFont();

		// render text
		// str -> text to display
		// destination -> where to draw
		// type -> render type -> solid(1) /  blended(2) / shaded(other) /
		void drawText(string str, SDL_Surface* destination, int type, int x, int y);


		// set font color
		void setColor(SDL_Color fg, SDL_Color bg);
		void setColor(int fr, int fg, int fb, int br, int bg, int bb);

		// return font
		TTF_Font* getFont();

		// return surface where font has been rendered
		SDL_Surface* getSurface();

		// set font size
		void setSize(int l);

		// set font style:
		// TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_NORMAL
		void setFotStyle(int style);

		// get font size
		int getSize();

		// get height
		int getHeight();


	private:
		TTF_Font* font;
		SDL_Surface* surface;
		SDL_Rect rectangulo;
		SDL_Color foreground_color, background_color;
		int size;

		bool loaded;

};




#endif
