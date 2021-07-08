#include "QuadTree.h"
#include"Object.h"
Array<QuadTree*> QuadTree::Tree_Liner;

QuadTree::QuadTree(float x_, float y_, float w_, float h_, int level_, int maxLevel_) :
	x(x_),
	y(y_),
	width(w_),
	height(h_),
	level(level_),
	maxLevel(maxLevel_) ,
	parent(nullptr),
	font(Font(30)),
	shape(Rect(x_,y_,w_,h_)),
	mortnnum(0)
{
	Tree_Liner << this;
	if (level == maxLevel) {
		return;
	}

	this->NW = new QuadTree(x, y, width / 2.f, height / 2.f, level + 1, maxLevel);
	this->NE = new QuadTree(x + width /2.f, y, width / 2.f, height / 2.f, level + 1, maxLevel);
	this->SW = new QuadTree(x, y + height /2.f, width / 2.f, height / 2.f, level + 1, maxLevel);
	this->SE = new QuadTree(x + width /2.f, y + height/2.f,width / 2.f, height / 2.f, level + 1, maxLevel);
}

QuadTree::~QuadTree()
{
	if (level == maxLevel) {
		return;
	}
	delete NW;
	delete SW;
	delete NE;
	delete SE;
}

void QuadTree::AddObject(Object* o_)
{
	//この空間が分割最大レベルであれば子への処理は行わない
	if (this->level == maxLevel) {
		this->objects << o_;
		return;
	}

	//左上
	if (this->contains(NW, o_)) {
		this->NW->AddObject(o_);
		return;
	}
	//左下
	else if (this->contains(SW, o_)) {
		this->SW->AddObject(o_);
		return;
	}
	//右上
	else if (this->contains(NE, o_)) {
		this->NE->AddObject(o_);
		return;
	}
	else if (this->contains(SE, o_)) {
		this->SE->AddObject(o_);
		return;
	}
	
	if (this->contains(this, o_)) {
		this->objects << o_;
	}


}

Array<Object*> QuadTree::GetObjectsAt(float x_, float y_)
{
	//この最大空間であればそのオブジェクトを返す
	if (this->level == this->maxLevel) {
		return this->objects;
	}

	//返すための配列	保存用
	Array<Object*> ReturnObjects, ChildReturnObjects;

	//自配列用
	if (!this->objects.empty()) {
		ReturnObjects = this->objects;
	}

	//右側への処理
	if (x_ > x + width / 2.0f && y_ < x + width) {
		if (y_ > y + height / 2.0f && y_ < y + height) {
			ChildReturnObjects = SE->GetObjectsAt(x_, y_);
			ReturnObjects.insert(ReturnObjects.end(), ChildReturnObjects.begin(), ChildReturnObjects.end());
			return ReturnObjects;
		}
		else if (y_ > y && y_ <= y + height / 2.0f) {
			ChildReturnObjects = NE->GetObjectsAt(x_, y_);
			ReturnObjects.insert(ReturnObjects.end(), ChildReturnObjects.begin(), ChildReturnObjects.end());
			return ReturnObjects;
		}
	}
	else if (x_ > x && x_ <= x + width / 2.0f) {
		if (y_ > y + height / 2.0f && y_ < y + height) {
			ChildReturnObjects = SW->GetObjectsAt(x_, y_);
			ReturnObjects.insert(ReturnObjects.end(), ChildReturnObjects.begin(), ChildReturnObjects.end());
			return ReturnObjects;
		}
		else if (y_ > y && y_ <= y + height / 2.0f) {
			ChildReturnObjects = NW->GetObjectsAt(x_, y_);
			ReturnObjects.insert(ReturnObjects.end(), ChildReturnObjects.begin(), ChildReturnObjects.end());
			return ReturnObjects;
		}
	}
	return ReturnObjects;
}

void QuadTree::Clear()
{
	if (this->level == maxLevel) {
		this->objects.clear();
		return;
	}
	else {
		NW->Clear();
		NE->Clear();
		SW->Clear();
		SE->Clear();
	}
	if (!objects.empty()) {
		objects.clear();
	}
}

void QuadTree::Draw() const
{
	this->font(this->mortnnum).draw(this->x + width /2.f, this->y + height/2.f);
	this->shape.draw(ColorF(0.5f,0.2f,0.4f,0.5f));

	if (level != maxLevel) {
		this->NW->Draw();
		this->SE->Draw();
		this->NE->Draw();
		this->SW->Draw();
	}
}

bool QuadTree::contains(QuadTree* child, Object* object)
{
	return!(object->x < child->x ||
		object->y < child->y ||
		object->x > child->x + child->width ||
		object->y > child->y + child->height ||
		object->x + object->width < child->x ||
		object->y + object->height < child->y ||
		object->x + object->width > child->x + child->width ||
		object->y + object->height > child->y + child->height);
}
