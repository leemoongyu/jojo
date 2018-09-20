#include "stdafx.h"
#include "jojo.h"

HRESULT jojo::init(void)
{
	IMAGEMANAGER->addImage("jojo_test", "resource/jojo/jojo_test.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_moveRange", "resource/jojo/jojo_moveRange.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_attRange", "resource/jojo/jojo_attRange.bmp", 64, 64, true, RGB(255, 0, 255));

	_jojo.x = 896.f;
	_jojo.y = 512.f;
	_jojo.width = TILESIZE;
	_jojo.height = TILESIZE;
	_jojo.index = 0;

	_jojo.rc = RectMake(_jojo.x, _jojo.y, _jojo.width, _jojo.height);

	_currentTile.x = 0;
	_currentTile.y = 0;

	_count = _index = 0;

	for (int i = 0; i < MOVE_RANGE; i++)
	{
		_jojoRange[i].indexX = 0;
		_jojoRange[i].indexY = 0;
	}

	indexX = indexY = 0;

	_isJojo = false;
	_isRange = false;

	_heojeo = new heojeo;
	_heojeo->init();

	_jojoMap = new jojoMap;
	_jojoMap->init();
	//_aStar = new aStar;
	//_aStar->init(TILEX, TILEY);

	return S_OK;
}

void jojo::release(void)
{
	_heojeo->release();
}

void jojo::update(void)
{
	_jojo.rc = RectMake(_jojo.x, _jojo.y, _jojo.width, _jojo.height);

	_heojeo->update();

	_MouseCamera = { _ptMouse.x + CAMERAMANAGER->getCamera().left, _ptMouse.y + CAMERAMANAGER->getCamera().top };

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_jojo.rc, _MouseCamera))
		{
			_isJojo = true;
			_jojo.indexX = 30;
			_jojo.indexY = 5;
		}

		if (PtInRect(&_heojeo->getRcHeojeo(), _MouseCamera))
		{
			_heojeo->setIsHeojeo(true);
		}
	}
	/*
	if (!_isRange)
	{
		if (_isJojo)
		{
			int k = 0;				// 렉트 인덱스 돌려줄 변수
			for (int i = 0; i < 6; i++)						// 조조 움직일 범위 렉트 ( 탑 )
			{
				for (int j = 0; j < i * 2 + 1; j++)
				{
					_jojoRangeTop[k].rc = RectMake(_jojo.x - (TILESIZE * i) + (TILESIZE * j), (_jojo.y - 320) + (i * TILESIZE), TILESIZE, TILESIZE);
					_jojoRangeTop[k].indexX = k;
					_jojoRangeTop[k].indexY = i;
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
					_jojoRangeBottom[n].rc = RectMake((_jojo.x - 288) - (TILESIZE * j) + (_jojo.x - 288) + (TILESIZE * i), _jojo.y + TILESIZE + (i * TILESIZE), TILESIZE, TILESIZE);
					_jojoRangeBottom[n].indexX = n;
					_jojoRangeBottom[n].indexY = i;
					n++;
					if (n >= MOVE_RANGE_BOTTOM) break;
				}
				if (n >= MOVE_RANGE_BOTTOM) break;
			}
		}
	}
	*/

	int moveRangeY = 1;			// 이동거리 렉트 Y
	int moveRangeX = 11;		// 이동거리 렉트 X
	int rangeIndex = 0;			// 인덱스 ++시켜줄 변수

	if (_isJojo)
	{
		for (int i = 0; i < moveRangeX; i++)
		{
			for (int j = 0; j < moveRangeY; j++)
			{
				if (i < 6)		// 캐릭터 위에 이동거리 렉트
				{
					_jojoRange[rangeIndex].rc = RectMake(_jojo.x + i * (-TILESIZE) + (j * TILESIZE), (_jojo.y - TILESIZE * 5) + (i * TILESIZE), TILESIZE, TILESIZE);
					_jojoRange[rangeIndex].indexX = rangeIndex;
					_jojoRange[rangeIndex].indexY = i;
				}
				else			// i가 6보다 커지면 캐릭터 아래 이동거리 렉트
				{
					_jojoRange[rangeIndex].rc = RectMake(_jojo.x + (moveRangeX - (i + 1)) * -TILESIZE + (j * TILESIZE), (_jojo.y - TILESIZE * 5) + i * TILESIZE, TILESIZE, TILESIZE);
					_jojoRange[rangeIndex].indexX = rangeIndex;
					_jojoRange[rangeIndex].indexY = i;
				}
				rangeIndex++;
			}
			if (i < 5)			// i가 5이하면 이동거리렉트 y값 증가
			{
				moveRangeY += 2;
			}
			else                // i가 6보다 커짐 이동거리렉트 y값 감소
			{
				moveRangeY -= 2;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < MOVE_RANGE; i++)
		{
			if (PtInRect(&_jojoRange[i].rc, _MouseCamera))
			{
				indexX = _jojoRange[i].indexX;
				indexY = _jojoRange[i].indexY;
				break;
			}
		}
	}

	for (int i = 0; i < MOVE_RANGE; i++)
	{
		if (indexX < _jojoRange[i].indexX && indexY == _jojoRange[i].indexY)
		{
				
		}
	}
	
}

void jojo::render(void)
{
	if (_isJojo)
	{
		for (int i = 0; i < MOVE_RANGE; i++)
		{
			IMAGEMANAGER->render("jojo_moveRange", getMemDC(), _jojoRange[i].rc.left - CAMERAMANAGER->getCamera().left, _jojoRange[i].rc.top - CAMERAMANAGER->getCamera().top);
		}
	}
	char str[64];
	sprintf_s(str, "%d",_jojo.indexX);
	TextOut(getMemDC(), 100, 100, str, strlen(str));

	char str1[64];
	sprintf_s(str1, "%d", _jojo.indexY);
	TextOut(getMemDC(), 100, 150, str1, strlen(str1));

	char str2[64];
	sprintf_s(str2, "%d", indexX);
	TextOut(getMemDC(), 200, 200, str2, strlen(str2));

	char str3[64];
	sprintf_s(str3, "%d", indexY);
	TextOut(getMemDC(), 200, 250, str3, strlen(str3));

	for (int i = 0; i < MOVE_RANGE; i++)
	{
		char str[64];
		sprintf_s(str, "%d", _jojoRange[i].indexX);
		TextOut(getMemDC(), (_jojoRange[i].rc.left + _jojoRange[i].rc.right) / 2, (_jojoRange[i].rc.top + _jojoRange[i].rc.bottom) / 2, str, strlen(str));

		char str1[64];
		sprintf_s(str1, "%d", _jojoRange[i].indexY);
		TextOut(getMemDC(), _jojoRange[i].rc.left, _jojoRange[i].rc.top, str1, strlen(str1));
	}

	_heojeo->render();

	IMAGEMANAGER->render("jojo_test", getMemDC(), _jojo.x - CAMERAMANAGER->getCamera().left, _jojo.y - CAMERAMANAGER->getCamera().top);

	RectangleMake(getMemDC(), _jojo.rc.left - CAMERAMANAGER->getCamera().left, _jojo.rc.top - CAMERAMANAGER->getCamera().top, TILESIZE, TILESIZE);

}
