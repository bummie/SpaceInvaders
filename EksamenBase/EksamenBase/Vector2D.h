#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED

class Vector2D
{
	struct Point { float x; float y; };

public:
	Vector2D() : Position{ 0, 0 } {}
	template <typename x, typename y>
	Vector2D(x, y);

	~Vector2D();

	Point Position;
};

template<typename x, typename y>
inline Vector2D::Vector2D(x, y)
{
	Position.x = x;
	Position.y = y;
}


inline Vector2D::~Vector2D()
{
}

#endif
