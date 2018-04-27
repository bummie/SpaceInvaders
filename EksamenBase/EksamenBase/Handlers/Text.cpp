#include "Text.h"
#include <iostream>

Text::Text(SDL_Renderer* renderer, std::string text, SDL_Color color, int size, int x, int y, int w, int h)
{
	Text::renderer = renderer;
	Text::text = text;
	font = TTF_OpenFont("Resources/Fonts/OpenSans-Regular.ttf", size);
	if (font == nullptr) 
	{
		std::cout << "Font is null" << TTF_GetError() << std::endl;
	}
	textColor = color;
	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	position = SDL_Rect();
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;

	FreeSurface();
}

Text::~Text()
{
	TTF_CloseFont(font);
	FreeSurface();
	FreeTexture();
}

/// <summary>
/// Changes the text
/// </summary>
/// <param name="text"></param>
void Text::setText(std::string text)
{
	FreeTexture();
	Text::text = text;
	textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	FreeSurface();
}

/// <summary>
/// Changes the color of the text
/// </summary>
/// <param name="r"></param>
/// <param name="g"></param>
/// <param name="b"></param>
void Text::setColor(SDL_Color color)
{
	FreeTexture();
	textColor = color;
	textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	FreeSurface();
}

/// <summary>
/// Changes the position of the text
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Text::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

/// <summary>
/// Draws the text onto the screen
/// </summary>
void Text::Draw()
{
	SDL_RenderCopy(renderer, textTexture, NULL, &position);
}

/// <summary>
/// Free the text surface from memory
/// </summary>
void Text::FreeSurface()
{
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}

void Text::FreeTexture()
{
	SDL_DestroyTexture(textTexture);
	textTexture = nullptr;
}
