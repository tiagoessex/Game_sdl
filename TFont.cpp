

#include "TFont.h"

TFont::TFont()
{
	font= TTF_OpenFont("fonts\times.ttf", 10);
	setColor (255,255,255,0,0,0);
	loaded = false;
}

TFont::TFont(string filename, int l)
{
	font= TTF_OpenFont(filename.c_str(), l);
	setColor (255,255,255,0,0,0);
	loaded = false;
}

TFont::~TFont()
{
//	if (loaded)
	//	SDL_FreeSurface(surface);

	TTF_CloseFont(font);
}


void TFont::drawText(string str, SDL_Surface* destination, int type, int x, int y)
{
	switch (type)
	{
		case 1:	surface = TTF_RenderText_Solid(font,str.c_str(),foreground_color ); break;
		case 2: surface = TTF_RenderText_Blended(font,str.c_str(),foreground_color ); break;
		default: surface = TTF_RenderText_Shaded(font,str.c_str(),foreground_color, background_color ); break;			
	}

	rectangulo.y=y;
	rectangulo.x=x;
	rectangulo.w=surface->w;
	rectangulo.h=surface->h;

	loaded = true;

	SDL_BlitSurface(surface,NULL,destination,&rectangulo);
	SDL_FreeSurface(surface);
	
}

void TFont::setColor(SDL_Color fg, SDL_Color bg)
{
	foreground_color = fg;
	background_color = bg;
}


void TFont::setColor(int fr, int fg, int fb, int br, int bg, int bb)
{
	foreground_color.r=fr;
	foreground_color.g=fg;
	foreground_color.b=fb;
	background_color.r=br;
	background_color.g=bg;
	background_color.b=bb;
}
		
TTF_Font* TFont::getFont()
{
	return font;
}


void TFont::setSize(int l)
{
	size=l;
}

void TFont::setFotStyle(int style)
{
	TTF_SetFontStyle(font, style);
}

int TFont::getSize()
{
	return size;
}

int TFont::getHeight()
{
	return TTF_FontHeight(font);
}

SDL_Surface* TFont::getSurface()
{
	return surface;
}