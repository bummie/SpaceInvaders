#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "SDL.h"
#include <SDL_ttf.h>
#include <string>

class Text
{
private:
	SDL_Surface* textSurface;
	TTF_Font* font;
	SDL_Color textColor;
	int textSize;
	std::string text;
	SDL_Rect position;
	SDL_Renderer* renderer;

	void FreeSurface();
	void FreeTexture();

public:
	Text(SDL_Renderer* renderer, std::string text, SDL_Color color, int size, int x, int y, int w, int h);
	~Text();

	SDL_Texture* textTexture;

	void setText(std::string text);
	void setColor(SDL_Color color);
	void setPosition(int x, int y);

	void Draw();
};

#endif