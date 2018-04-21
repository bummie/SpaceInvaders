#include "TextRenderer.h"
#include <iostream>

TextRenderer::~TextRenderer()
{
}

/// <summary>
/// Retrieves a text with given key
/// </summary>
/// <param name="textKey"></param>
/// <returns></returns>
Text * TextRenderer::getText(std::string textKey)
{
	auto iterator = textMap.find(textKey);

	if (iterator != textMap.end())
	{
		return textMap[textKey];
	}

	return nullptr;
}

/// <summary>
/// Add a new text to the renderer
/// </summary>
/// <param name="textKey"></param>
/// <param name="text"></param>
void TextRenderer::addText(std::string textKey, Text * text)
{
	auto iterator = textMap.find(textKey);

	if (iterator == textMap.end())
	{
		textMap[textKey] = text;
		return;
	}

	delete(text);
	std::cout << "Key is already being used. Key: " << textKey << std::endl;
}

/// <summary>
/// Removes a text with given key
/// </summary>
/// <param name="textKey"></param>
void TextRenderer::removeText(std::string textKey)
{
	auto iterator = textMap.find(textKey);

	if (iterator != textMap.end())
	{
		textMap.erase(textKey);
	}
}

/// <summary>
/// Draws every text to the screen
/// </summary>
void TextRenderer::Draw()
{
	for (auto text : textMap)
	{
		text.second->Draw();
	}
}
