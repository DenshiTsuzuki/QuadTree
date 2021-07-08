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

	//��Ԃɓo�^
	void	AddObject(Object* o_);


	//��ԏ����̃I�u�W�F�N�g
	Array<Object*>	GetObjectsAt(float x_, float y_);

	//0�N���A
	void Clear();
			
	void Draw()const;

private:
	float	x;
	float	y;
	float	width;
	float	height;
	int		level;
	int		maxLevel;

	//���[�g���ԍ�����U��
	int mortnnum;
	//�K�w�����̃I�u�W�F�N�g
	Array<Object*> objects;

	//�e���	�Ȃ���΃��[�g
	QuadTree*	parent;
	
	//����
	QuadTree* NW;
	//����
	QuadTree* SW;
	//�E��
	QuadTree* NE;
	//�E��
	QuadTree* SE;


	Rect shape;

	Font font;

	//��ԂȂ��ɂ͂��邩�o�Ă��邩�@�ہX�����Ă�����true��Ԃ�
	bool contains(QuadTree* child,Object* object);
};

