#pragma once
#include<Siv3D.hpp>

class Object;
class QuadTree;

class QuadTree
{
public: 
	//

	QuadTree(float x_, float y_, float w_, float h_, int level_, int maxLevel_);
	~QuadTree();

	//空間に登録
	void	AddObject(Object* o_);


	//空間所属のオブジェクト
	Array<Object*>	GetObjectsAt(float x_, float y_);

	//0クリア
	void Clear();
			
	void Draw()const;

private:
	float	x;
	float	y;
	float	width;
	float	height;
	int		level;
	int		maxLevel;

	//モートン番号割り振り
	int mortnnum;
	//階層所属のオブジェクト
	Array<Object*> objects;

	//親空間	なければルート
	QuadTree*	parent;
	
	//左上
	QuadTree* NW;
	//左下
	QuadTree* SW;
	//右上
	QuadTree* NE;
	//右下
	QuadTree* SE;


	Rect shape;

	Font font;

	//空間ないにはいるか出ているか　丸々入っていたらtrueを返す
	bool contains(QuadTree* child,Object* object);
};

