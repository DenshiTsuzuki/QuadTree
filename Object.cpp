#include "Object.h"
Object::Object(float x_, float y_, float width_, float height_) :
	x(x_),
	y(y_),
	width(width_),
	height(height_),
	shape(Rect(x_,y_,width_,height_))
{
	
}

void Object::Draw() const{
	this->shape.draw(ColorF(0.2f,1.f,0.4f,0.3f));
}