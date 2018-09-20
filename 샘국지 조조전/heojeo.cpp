#include "stdafx.h"
#include "heojeo.h"

HRESULT heojeo::init(void)
{
	_x = 1216.f;
	_y = 896.f;
	_width = TILESIZE;
	_height = TILESIZE;

	_rcHeojeo = RectMake(_x, _y, _width, _height);

	_isHeojeo = false;

	return S_OK;
}

void heojeo::release(void)
{

}

void heojeo::update(void)
{
	_rcHeojeo = RectMake(_x, _y, _width, _height);

	if (_isHeojeo)
	{
		int k = 0;				// 렉트 인덱스 돌려줄 변수
		for (int i = 0; i < 6; i++)						// 조조 움직일 범위 렉트 ( 탑 )
		{
			for (int j = 0; j < i * 2 + 1; j++)
			{
				_heojeoRangeTop[k] = RectMake(_x - (TILESIZE * i) + (TILESIZE * j), (_y - 320) + (i * TILESIZE), TILESIZE, TILESIZE);
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
				_heojeoRangeBottom[n] = RectMake((_x - 608) - (TILESIZE * j) + (_x - 288) + (TILESIZE * i), _y + TILESIZE + (i * TILESIZE), TILESIZE, TILESIZE);
				n++;
				if (n >= MOVE_RANGE_BOTTOM) break;
			}
			if (n >= MOVE_RANGE_BOTTOM) break;
		}
	}
}

void heojeo::render(void)
{
	if (_isHeojeo)
	{
		for (int i = 0; i < MOVE_RANGE_TOP; i++)
		{
			IMAGEMANAGER->render("jojo_moveRange", getMemDC(), _heojeoRangeTop[i].left - CAMERAMANAGER->getCamera().left, _heojeoRangeTop[i].top - CAMERAMANAGER->getCamera().top);
		}
		for (int i = 0; i < MOVE_RANGE_BOTTOM; i++)
		{
			IMAGEMANAGER->render("jojo_moveRange", getMemDC(), _heojeoRangeBottom[i].left - CAMERAMANAGER->getCamera().left, _heojeoRangeBottom[i].top - CAMERAMANAGER->getCamera().top);
		}
	}

	//char str[64];
	//sprintf_s(str, "%d", _MouseCamera);
	//TextOut(getMemDC(), 100, 100, str, strlen(str));

	RectangleMake(getMemDC(), _rcHeojeo.left - CAMERAMANAGER->getCamera().left, _rcHeojeo.top - CAMERAMANAGER->getCamera().top, TILESIZE, TILESIZE);
}
