#include "stdafx.h"
#include "jojoMap.h"

HRESULT jojoMap::init(void)
{
	_map = IMAGEMANAGER->addImage("jojo_tileMap", "resource/jojo/jojo_tileMap.bmp", 2048, 2048);

	_rcMouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 40, 40);
	_rcCamera[0] = RectMakeCenter(WINSIZEX / 2, 30, WINSIZEX, 60); 
	_rcCamera[1] = RectMakeCenter(WINSIZEX - 30, WINSIZEY / 2, 60, WINSIZEY);
	_rcCamera[2] = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 30, WINSIZEX, 60);
	_rcCamera[3] = RectMakeCenter(30, WINSIZEY / 2, 60, WINSIZEY);

	_camera = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_camera);

	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_mapTile[i * TILEX + j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}

	return S_OK;
}

void jojoMap::release(void)
{

}

void jojoMap::update(void)
{

	//ShowCursor(true);
	_rcMouse = RectMakeCenter(_ptMouse.x, _ptMouse.y, 40, 40);
	_rcCamera[0] = RectMakeCenter(WINSIZEX / 2, 30, WINSIZEX, 60);				// top
	_rcCamera[1] = RectMakeCenter(WINSIZEX - 30, WINSIZEY / 2, 60, WINSIZEY);	// right
	_rcCamera[2] = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 30, WINSIZEX, 60);	// bottom
	_rcCamera[3] = RectMakeCenter(30, WINSIZEY / 2, 60, WINSIZEY);				// left

	_cursor.top = 30;
	_cursor.bottom = WINSIZEY - 15;
	_cursor.left = 210;
	_cursor.right = WINSIZEX + 160;

	ClipCursor(&_cursor);														// 커서 가두기

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_mapTile[i * TILEX + j].rc = RectMake(j * TILESIZE - CAMERAMANAGER->getCamera().left, i * TILESIZE - CAMERAMANAGER->getCamera().top, TILESIZE, TILESIZE);
		}
	}

	if (IntersectRect(&_rcTemp, &_rcMouse, &_rcCamera[0]))						// top
	{
		if (_camera.top > -150 && _camera.bottom > -150)
		{
			_camera.top -= 7;
			_camera.bottom -= 7;
		}
	}

	if (IntersectRect(&_rcTemp, &_rcMouse, &_rcCamera[1]))						// right
	{
		if (_camera.left < 2248 && _camera.right < 2248)
		{
			_camera.left += 7;
			_camera.right += 7;
		}
	}

	if (IntersectRect(&_rcTemp, &_rcMouse, &_rcCamera[2]))						// bottom
	{
		if (_camera.top < 2198 && _camera.bottom < 2198)
		{
			_camera.top += 7;
			_camera.bottom += 7;
		}
	}

	if (IntersectRect(&_rcTemp, &_rcMouse, &_rcCamera[3]))						// left
	{
		if (_camera.left > -200 && _camera.right > -200)
		{
			_camera.left -= 7;
			_camera.right -= 7;
		}
	}

	

	CAMERAMANAGER->setCamera(_camera);
}

void jojoMap::render(void)
{
	IMAGEMANAGER->render("jojo_tileMap", getMemDC(), 0 - CAMERAMANAGER->getCamera().left, 0 - CAMERAMANAGER->getCamera().top);	

	//Rectangle(getMemDC(), _rcMouse);					// 마우스 렉트
	//for (int i = 0; i < 4; i++)						// 동서남북 렉트
	//{
	//	Rectangle(getMemDC(), _rcCamera[i]);
	//}
	//Rectangle(getMemDC(), _camera);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < TILEY * TILEX; i++)
		{
			Rectangle(getMemDC(), _mapTile[i].rc);
		}
	}
}
