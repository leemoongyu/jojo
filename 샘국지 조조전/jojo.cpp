#include "stdafx.h"
#include "jojo.h"

HRESULT jojo::init(void)
{
	_jojo = IMAGEMANAGER->addImage("jojo_test", "resource/jojo/jojo_test.bmp", 64, 64, true, RGB(255, 0, 255));
	_x = 100.f;
	_y = 100.f;

	_count = _index = 0;

	return S_OK;
}

void jojo::release(void)
{
}

void jojo::update(void)
{
	
}

void jojo::render(void)
{
	IMAGEMANAGER->render("jojo_test", getMemDC(), _x, _y);
}
