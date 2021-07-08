#pragma once
#include"Object.h"
#include"QuadTree.h"
#include <Siv3D.hpp> // OpenSiv3D v0.4.3

//bitを1つ飛ばしにした値を返す
int BitSeparate16(int n)
{
	n = (n | (n << 4)) & 0xf0f;
	n = (n | (n << 2)) & 0x3333;
	return (n | (n << 1)) & 0x5555;
}

//モートン番号を返す
int MortonNum(int x, int y){
	
	return (BitSeparate16(x) | (BitSeparate16(y) << 1));
}

void Main()
{
	const int size_x = 800, size_y = 600;
	Window::Resize(size_x, size_y);
	Scene::Resize(size_x, size_y);

	QuadTree quadtree(0.f, 0.f, float(size_x), float(size_y), 0, 3);

	Array<Object*> objects;
	Object o(0.f, 0.f, 64.f, 64.f);
	while (System::Update()) {
		ClearPrint();
		//オブジェクトを登録
		if (MouseL.down()) {
			Object* ss = new Object(Cursor::Pos().x, Cursor::Pos().y, 32.f, 32.f);
			objects << ss;
			quadtree.AddObject(ss);
		}
		quadtree.Draw();
		
		for (auto& obj : objects) {
			obj->Draw();
		}

		Array<Object*> returnobjects = quadtree.GetObjectsAt(Cursor::PosF().x, Cursor::Pos().y);

		Print << returnobjects.size();

		if (KeyEscape.down()) {
			break;
		}
	}

	quadtree.Clear();
	for (auto& p : objects) {
		delete p;
	}
}
