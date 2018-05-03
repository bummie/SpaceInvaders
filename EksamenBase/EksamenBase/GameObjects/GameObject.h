#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "SDL.h"
#include <string>

class GameObject
{	
protected:

	struct Vector2D
	{
		float x;
		float y;
	};

	SDL_Texture* m_defTexture;
	SDL_Texture* m_secondaryTexture;
	SDL_Renderer* m_renderer;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	float m_deAcceleration;
	float m_accelerationValue;
	const float M_MAX_SPEED = .5f;
	int m_hp;

public:
	GameObject(SDL_Renderer* renderer);
	~GameObject();
	SDL_Rect position;
	std::string tag;
	int id;
	virtual void Logic();
	virtual void Draw();
	virtual void Input();
	int getHp() const;
	void setHp(int hp);
private:
	bool m_firstTexture = true;
	float m_currentTime = 0;
};

#endif 