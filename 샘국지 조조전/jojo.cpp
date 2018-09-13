#include "stdafx.h"
#include "jojo.h"

HRESULT jojo::init(void)
{
	IMAGEMANAGER->addImage("jojo_test", "resource/jojo/jojo_test.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_moveRange", "resource/jojo/jojo_moveRange", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_attRange", "resource/jojo/jojo_attRange", 64, 64, true, RGB(255, 0, 255));

	_x = 896.f;
	_y = 320.f;
	_winth = TILESIZE;
	_height = TILESIZE;

	_rcJojo = RectMake(_x, _y, _winth, _height);

	_count = _index = 0;

	return S_OK;
}

void jojo::release(void)
{

}

void jojo::update(void)
{
	_rcJojo = RectMake(_x, _y, _winth, _height);

	for (int i = 0; i < 1; i+2)
	{
		for (int j = 0; j < i; j++)
		{

		}
	}

	//for (int i = 0; i < 11; i++)
	//{
	//	int a = 5;
	//	int b = 6;
	//	if (i == 1)
	//	{
	//		a = 4;
	//		b = 7;
	//	}
	//	if (i == 2)
	//	{
	//		a = 3;
	//		b = 8;
	//	}
	//	if (i == 3)
	//	{
	//		a = 2;
	//		b = 9;
	//	}
	//	if (i == 4)
	//	{
	//		a = 1;
	//		b = 10;
	//	}
	//	if (i == 5)
	//	{
	//		a = 0;
	//		b = 12;
	//	}
	//	if (i == 6)
	//	{
	//		a = 1;
	//		b = 10;
	//	}
	//	if (i == 7)
	//	{
	//		a = 2;
	//		b = 9;
	//	}
	//	if (i == 8)
	//	{
	//		a = 3;
	//		b = 8;
	//	}
	//	if (i == 9)
	//	{
	//		a = 4; 
	//		b = 7;
	//	}
	//	if (i == 10)
	//	{
	//		a = 5;
	//		b = 6;
	//	}
	//	for (int j = a; j < b; j++)
	//	{
	//		_rcRange[i] = RectMake(300, 300 + i * TILESIZE, 64, 64);
	//	}
	//}
	
}

void jojo::render(void)
{
	IMAGEMANAGER->render("jojo_test", getMemDC(), _x, _y);

	Rectangle(getMemDC(), _rcJojo);

	//Rectangle(getMemDC(), _rcRange[11]);
}
