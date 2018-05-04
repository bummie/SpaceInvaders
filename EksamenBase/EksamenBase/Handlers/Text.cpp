#include "Text.h"
#include <iostream>
#include "GameHandler.h"

Text::Text(SDL_Renderer* renderer, std::string text, SDL_Color color, int size, int x, int y, int w, int h)
{
	Text::m_renderer = renderer;
	Text::m_text = text;
	m_font = TTF_OpenFont("Resources/Fonts/ca.ttf", size);
	if (m_font == nullptr)
	{
		std::cout << "Font is null" << TTF_GetError() << std::endl;
	}
	m_textColor = color;
	m_textSurface = TTF_RenderText_Solid(m_font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, m_textSurface);
	m_visible = true;
	m_blink = false;
	m_blinkDelay = 300;
	m_blinkTimePassed = 0;

	m_position = SDL_Rect();
	m_position.x = x;
	m_position.y = y;
	m_position.w = w;
	m_position.h = h;

	FreeSurface();
}

Text::~Text()
{
	TTF_CloseFont(m_font);
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
	Text::m_text = text;
	m_textSurface = TTF_RenderText_Solid(m_font, text.c_str(), m_textColor);
	textTexture = SDL_CreateTextureFromSurface(m_renderer, m_textSurface);

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
	m_textColor = color;
	m_textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_textColor);
	textTexture = SDL_CreateTextureFromSurface(m_renderer, m_textSurface);

	FreeSurface();
}

/// <summary>
/// Changes the position of the text
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Text::setPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

/// <summary>
/// If text should be visible or not
/// </summary>
/// <param name="visible"></param>
void Text::setVisible(bool visible)
{
	m_visible = visible;
}

/// <summary>
/// Turn blinking on and off
/// </summary>
/// <param name="shouldBlink"></param>
void Text::setBlink(bool shouldBlink)
{
	m_blink = shouldBlink;
	setVisible(false);
}

/// <summary>
/// Draws the text onto the screen
/// </summary>
void Text::Draw()
{
	if(m_blink)
	{
		if(m_blinkTimePassed >= m_blinkDelay)
		{
			m_visible = m_visible ? false : true;
			m_blinkTimePassed = 0;
		}

		m_blinkTimePassed += GameHandler::getDeltaTime();
	}

	if(m_visible)
	{
		SDL_RenderCopy(m_renderer, textTexture, NULL, &m_position);
	}
}

/// <summary>
/// Free the text surface from memory
/// </summary>
void Text::FreeSurface()
{
	SDL_FreeSurface(m_textSurface);
	m_textSurface = nullptr;
}

/// <summary>
/// Frees the texture
/// </summary>
void Text::FreeTexture()
{
	SDL_DestroyTexture(textTexture);
	textTexture = nullptr;
}
