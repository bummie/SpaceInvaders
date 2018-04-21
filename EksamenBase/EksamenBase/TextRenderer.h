#ifndef TEXTRENDERER_H_INCLUDED
#define TEXTRENDERER_H_INCLUDED

#include "Text.h"
#include <unordered_map>

class TextRenderer
{
public:
	static TextRenderer& getInstance()
	{
		static TextRenderer instance;
		return instance;
	}

private:
	TextRenderer() {}
	TextRenderer(TextRenderer const&);
	void operator=(TextRenderer const&);
	
	std::unordered_map<std::string, Text*> textMap;

public:
	~TextRenderer();

	Text* getText(std::string textKey);
	void addText(std::string textKey, Text* text);
	void removeText(std::string textKey);
	void Draw();
};

#endif