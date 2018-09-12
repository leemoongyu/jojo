#include "stdafx.h"
#include "jojo.h"

HRESULT jojo::init(void)
{
	_jojo = IMAGEMANAGER->addFrameImage("jojo_horseRight", "jojo_horseRight.bmp", 872, 99, 8, 1, true, RGB(255, 0, 255));
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
	_jojo->setFrameY(0);
	_count++;
	if (_count % 5 == 0)
	{
		_index++;
		if (_index >= _jojo->getMaxFrameX())
		{
			_index = 0;
		}
		_jojo->setFrameX(_index);
	}
	_rc = RectMake(_x, _y, _jojo->getWidth(), _jojo->getHeight());
}

void jojo::render(void)
{
	_jojo->frameRender(getMemDC(), _rc.left, _rc.top);
}
