#pragma once
#include<Siv3D.hpp>

class Object
{
	Rect shape;
public:
	float	x;
	float	y;
	float	width;
	float	height;

	//-----------------------------------------------------------------------------------------
			Object(float x_, float y_, float width_,float height_);

	void	Draw()const;
};

