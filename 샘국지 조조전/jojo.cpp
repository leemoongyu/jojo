#include "stdafx.h"
#include "jojo.h"

HRESULT jojo::init(void)
{
	IMAGEMANAGER->addImage("jojo_test", "resource/jojo/jojo_test.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_moveRange", "resource/jojo/jojo_moveRange.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_attRange", "resource/jojo/jojo_attRange.bmp", 64, 64, true, RGB(255, 0, 255));

	_x = 896.f;
	_y = 512.f;
	_width = TILESIZE;
	_height = TILESIZE;

	_rcJojo = RectMake(_x, _y, _width, _height);

	_count = _index = 0;

	_isJojo = false;

	//_aStar = new aStar;
	//_aStar->init(TILEX, TILEY);

	return S_OK;
}

void jojo::release(void)
{

}

void jojo::update(void)
{
	_rcJojo = RectMake(_x, _y, _width, _height);

	_MouseCamera = { _ptMouse.x + CAMERAMANAGER->getCamera().left, _ptMouse.y + CAMERAMANAGER->getCamera().top };

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcJojo, _MouseCamera))
		{
			_isJojo = true;
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < MOVE_RANGE_TOP; i++)
			{
				if (PtInRect(&_jojoRangeTop[i].rc, _MouseCamera))
				{
					
				}
			}
		}
	}

	if (_isJojo)
	{
		int k = 0;				// 렉트 인덱스 돌려줄 변수
		for (int i = 0; i < 6; i++)						// 조조 움직일 범위 렉트 ( 탑 )
		{
			for (int j = 0; j < i * 2 + 1; j++)
			{
				//_rc[i + j / 3] = RectMake(500 - (TILESIZE * i) + (TILESIZE * j), 500 + (i * TILESIZE), TILESIZE, TILESIZE);
				_jojoRangeTop[k].rc = RectMake(_x - (TILESIZE * i) + (TILESIZE * j), (_y - 320) + (i * TILESIZE), TILESIZE, TILESIZE);
				k++;
				if (k >= MOVE_RANGE_TOP) break;
			}
			if (k >= MOVE_RANGE_TOP) break;
		}

		int n = 0;				// 렉트 인덱스 돌려줄 변수
		for (int i = 0; i < 5; i++)						// 조조 움직일 범위 렉트 ( 바텀 )
		{
			for (int j = 9; j > i * 2; j--)
			{
				_jojoRangeBottom[n].rc = RectMake((_x - 288) - (TILESIZE * j) + (_x - 288) + (TILESIZE * i), _y + TILESIZE + (i * TILESIZE), TILESIZE, TILESIZE);
				n++;
				if (n >= MOVE_RANGE_BOTTOM) break;
			}
			if (n >= MOVE_RANGE_BOTTOM) break;
		}
	}

}

void jojo::render(void)
{
	if (_isJojo)
	{
		for (int i = 0; i < MOVE_RANGE_TOP; i++)
		{
			IMAGEMANAGER->render("jojo_moveRange", getMemDC(), _jojoRangeTop[i].rc.left - CAMERAMANAGER->getCamera().left, _jojoRangeTop[i].rc.top - CAMERAMANAGER->getCamera().top);
		}

		for (int i = 0; i < MOVE_RANGE_BOTTOM; i++)
		{
			IMAGEMANAGER->render("jojo_moveRange", getMemDC(), _jojoRangeBottom[i].rc.left - CAMERAMANAGER->getCamera().left, _jojoRangeBottom[i].rc.top - CAMERAMANAGER->getCamera().top);
		}
	}
	
	IMAGEMANAGER->render("jojo_test", getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);

	RectangleMake(getMemDC(), _rcJojo.left - CAMERAMANAGER->getCamera().left, _rcJojo.top - CAMERAMANAGER->getCamera().top, TILESIZE, TILESIZE);

}
