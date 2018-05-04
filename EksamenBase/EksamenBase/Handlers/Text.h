#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "SDL.h"
#include <SDL_ttf.h>
#include <string>

class Text
{
private:
	SDL_Surface* m_textSurface;
	TTF_Font* m_font;
	SDL_Color m_textColor;
	int m_textSize;
	std::string m_text;
	SDL_Rect m_position;
	SDL_Renderer* m_renderer;
	bool m_visible;
	bool m_blink;
	int m_blinkDelay;
	int m_blinkTimePassed;

	void FreeSurface();
	void FreeTexture();

public:
	Text(SDL_Renderer* renderer, std::string text, SDL_Color color, int size, int x, int y, int w, int h);
	~Text();

	SDL_Texture* textTexture;

	void setText(std::string text);
	void setColor(SDL_Color color);
	void setPosition(int x, int y);
	void setVisible(bool visible);
	void setBlink(bool shouldBlink);

	void Draw();
};

#endif