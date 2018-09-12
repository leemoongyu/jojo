#include "stdafx.h"
#include "tileMap.h"

HRESULT tileMap::init(void)
{
	//타일맵 이미지 초기화
	IMAGEMANAGER->addFrameImage("jojo_tile", "jojo_tile.bmp", 256, 960, SAMPLETILEX, SAMPLETILEY * 3);
	//IMAGEMANAGER->addFrameImage("jojo_tile2", "jojo_tile2.bmp", 256, 320, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addImage("tileBg", "tileBg.bmp", 578, 1000, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_save1", "jojo_save1.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_save2", "jojo_save2.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_mouse", "jojo_mouse.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_arrowLeft", "jojo_arrowLeft.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_arrowRight", "jojo_arrowRight.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_edge2", "jojo_edge2.bmp", 70, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_rect2", "jojo_rect2.bmp", 1600, 1000);

	//맵툴셋팅
	this->maptoolSetup();

	_rcCamera = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	//지형그리기 버튼으로 초기화
	_ctrlSelect = CTRL_TERRAINDRAW;
	
	_page = PAGE_ONE;

	_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 20, 20);

	//왼쪽화면을 모두 물로 기본타일 설정하기
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJECT_NONE;
	}

	startX = startY = 0;
	endX = endY = 0;

	//렉트위치 초기화
	_rcSave = RectMake(660 + 580, 400 + 400, 100, 50);
	_rcLoad = RectMake(660 + 700, 400 + 400, 100, 50);
	_rcTerrain = RectMake(660 + 500, 400 + 500, 100, 50);
	_rcObject = RectMake(660 + 620, 400 + 500, 100, 50);
	_rcEraser = RectMake(660 + 740, 400 + 500, 100, 50);
	_rcArrowLeft = RectMake(1200, 660, 50, 50);
	_rcArrowRight = RectMake(1400, 660, 50, 50);
	_rcMouse = RectMake(_ptMouse.x - 10, _ptMouse.y + 25, 64, 64);
	_rcBg = RectMake(0, 0, 1024, WINSIZEY);
		
	for (int i = 0; i < BOX_Y; i++)				// 테두리 렉트
	{
		for (int j = 0; j < BOX_X; j++)
		{
			_rcEdge[i * BOX_X + j] = RectMake((_sampleTiles[i * BOX_X + j].rc.left - (EDGESIZE - TILESIZE) / 2), (_sampleTiles[i * BOX_X + j].rc.top - (EDGESIZE - TILESIZE) / 2), EDGESIZE, EDGESIZE);
		}
	}

	_click = false;
	_start = false;
	_isCollision = false;
	_isDrag = false;

	return S_OK;
	
}

void tileMap::release(void)
{
}

void tileMap::update(void)
{
	ShowCursor(false);
	//렉트위치 초기화
	_rcSave = RectMake(1200, 750, 100, 70);
	_rcLoad = RectMake(1370, 750, 100, 70);
	_rcTerrain = RectMake(660 + 500, 400 + 500, 100, 50);
	_rcObject = RectMake(660 + 620, 400 + 500, 100, 50);
	_rcEraser = RectMake(660 + 740, 400 + 500, 100, 50);
	_rcArrowLeft = RectMake(1200, 670, 50, 20);
	_rcArrowRight = RectMake(1400, 670, 50, 20);
	_rcMouse = RectMake(_ptMouse.x + 35, _ptMouse.y + 35, 64, 64);
	_rcBg = RectMake(0, 0, 1024, WINSIZEY);

	this->maptoolSetup();

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		this->setMap();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rcSave, _ptMouse))
		{
			_ctrlSelect = CTRL_SAVE;
			this->save();
		}

		if (PtInRect(&_rcLoad, _ptMouse))
		{
			_ctrlSelect = CTRL_LOAD;
			this->load();
		}

		if (PtInRect(&_rcTerrain, _ptMouse))
		{
			_ctrlSelect = CTRL_TERRAINDRAW;
		}

		if (PtInRect(&_rcObject, _ptMouse))
		{
			_ctrlSelect = CTRL_OBJDRAW;
		}

		if (PtInRect(&_rcEraser, _ptMouse))
		{
			_ctrlSelect = CTRL_ERASER;
		}

		if (PtInRect(&_rcArrowRight, _ptMouse))
		{
			if (_page == PAGE_TWO)
			{
				_page = PAGE_THREE;
			}
			if (_page == PAGE_ONE)
			{
				_page = PAGE_TWO;
			}
		}

		if (PtInRect(&_rcArrowLeft, _ptMouse))
		{
			if (_page == PAGE_TWO)
			{
				_page = PAGE_ONE;
			}
			if (_page == PAGE_THREE)
			{
				_page = PAGE_TWO;
			}
		}

		if (PtInRect(&_rcBg, _ptMouse))
		{
			_isCollision = true;
		}
		else
		{
			_isCollision = false;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LCONTROL))				// 드래그 하면 렉트 생성
	{
		if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
		{
			if (!_start)
			{
				startX = _ptMouse.x;
				startY = _ptMouse.y;
				_start = true;
			}
			endX = _ptMouse.x;
			endY = _ptMouse.y;
			_click = true;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
		{
			_start = false;
			for (int i = 0; i <TILEX * TILEY; i++)
			{
				if (IntersectRect(&temp, &_rcDrag, &_tiles[i].rc))		// 드래그한 렉트랑 타일이랑 충돌하면 타일 담아주기
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_click = false;
					_isDrag = true;
				}
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown('A'))		// 카메라이동
	{
		if (_rcCamera.left > 0 && _rcCamera.right > 0)
		{
			_rcCamera.left -= 10;
			_rcCamera.right -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_rcCamera.left < 2630 && _rcCamera.right < 2630)
		{
			_rcCamera.left += 10;
			_rcCamera.right += 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_rcCamera.top > -10 && _rcCamera.bottom > -10)
		{
			_rcCamera.top -= 10;
			_rcCamera.bottom -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if(_rcCamera.top < 2058 && _rcCamera.bottom < 2058)
		{
			_rcCamera.top += 10;
			_rcCamera.bottom += 10;
		}
		
	}
	
	CAMERAMANAGER->setCamera(_rcCamera);
	_rcDrag = RectMake(startX, startY, endX - startX, endY - startY);

	switch (_page)
	{
	case PAGE_ONE:
		break;
	case PAGE_TWO:
		break;
	case PAGE_THREE:
		break;
	default:
		break;
	}
}

void tileMap::render(void)
{
	//Rectangle(getMemDC(), _rcCamera);

	//타일맵 이미지 렌더

	//전체화면 왼쪽에 지형을 그린다
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("jojo_tile", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}
	
	////전체화면 왼쪽에 오브젝트를 그린다
	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (_tiles[i].obj == OBJECT_NONE) continue;
	//	IMAGEMANAGER->frameRender("jojo_tile", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	//}

	IMAGEMANAGER->render("tileBg", getMemDC(), 1023, 0);				// 타일 백그 이미지
	//Rectangle(getMemDC(), _rcBg);

	for (int i = 0; i < BOX_X * BOX_Y; i++)								// 타일 테두리 이미지
	{
		//Rectangle(getMemDC(), _rcEdge[i]);
		IMAGEMANAGER->render("jojo_edge2", getMemDC(), _rcEdge[i].left, _rcEdge[i].top);
	}

	switch (_page)
	{
	case PAGE_ONE:

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)					// 타일 이미지
		{
			IMAGEMANAGER->frameRender("jojo_tile", getMemDC(), _sampleTiles[i].rc.left, _sampleTiles[i].rc.top, _sampleTiles[i].terrainFrameX, _sampleTiles[i].terrainFrameY);
		}

		if (_isDrag)
		{
			for (int i = 0; i < TILEX*TILEY; i++)								// 드래그 
			{
				IMAGEMANAGER->frameRender("jojo_tile", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
			}
			_isDrag = false;
		}
		
		IMAGEMANAGER->alphaRender("jojo_tile", getMemDC(), _rcMouse.left, _rcMouse.top, _currentTile.x * TILESIZE, _currentTile.y * TILESIZE, TILESIZE, TILESIZE, 200);		// 타일 클릭시 알파렌더

		break;
	case PAGE_TWO:

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			IMAGEMANAGER->frameRender("jojo_tile", getMemDC(), _sampleTiles1[i].rc.left, _sampleTiles1[i].rc.top, _sampleTiles1[i].terrainFrameX, _sampleTiles1[i].terrainFrameY + SAMPLETILEY);
		}
		
		IMAGEMANAGER->alphaRender("jojo_tile", getMemDC(), _rcMouse.left, _rcMouse.top, _currentTile.x * TILESIZE, _currentTile.y * TILESIZE, TILESIZE, TILESIZE, 200);		// 타일 클릭시 알파렌더

		break;
	case PAGE_THREE:

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			IMAGEMANAGER->frameRender("jojo_tile", getMemDC(), _sampleTiles2[i].rc.left, _sampleTiles2[i].rc.top, _sampleTiles2[i].terrainFrameX, _sampleTiles2[i].terrainFrameY + SAMPLETILEY * 2);
		}

		IMAGEMANAGER->alphaRender("jojo_tile", getMemDC(), _rcMouse.left, _rcMouse.top, _currentTile.x * TILESIZE, _currentTile.y * TILESIZE, TILESIZE, TILESIZE, 200);

		break;
	default:
		break;
	}

	if (_click)
	{
		IMAGEMANAGER->alphaRender("jojo_rect2", getMemDC(), _rcDrag.left, _rcDrag.top, 0, 0, _rcDrag.right - _rcDrag.left, _rcDrag.bottom - _rcDrag.top, 200);
		HPEN pen = (HPEN)CreatePen(PS_SOLID, 1, RGB(163, 150, 80));
		HPEN open = (HPEN)SelectObject(getMemDC(), pen);
		//SelectObject(getMemDC(), GetStockObject(NULL_BRUSH));
		//HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(115, 85, 0));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		//Rectangle(getMemDC(), _rcDrag);
		SelectObject(getMemDC(), open);
		DeleteObject(pen);
	}

	//IMAGEMANAGER->frameRender("jojo_tile", getMemDC(), _rcMouse.left, _rcMouse.top, _currentTile.x, _currentTile.y);
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		//게임타일 렉트 렌더
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(getMemDC(), _tiles[i].rc);
			HPEN pen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN open = (HPEN)SelectObject(getMemDC(), pen);
			SelectObject(getMemDC(), GetStockObject(NULL_BRUSH));

			Rectangle(getMemDC(), _tiles[i].rc);

			SelectObject(getMemDC(), open);
			DeleteObject(pen);
		}
		//이미지타일 렉트 렌더
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			Rectangle(getMemDC(), _sampleTiles[i].rc);
		}
	}
	
	//버튼렉트 렌더
	//Rectangle(getMemDC(), _rcSave);
	//Rectangle(getMemDC(), _rcLoad);
	//Rectangle(getMemDC(), _rcTerrain);
	//Rectangle(getMemDC(), _rcObject);
	//Rectangle(getMemDC(), _rcEraser);
	//Rectangle(getMemDC(), _rcArrowLeft);
	//Rectangle(getMemDC(), _rcArrowRight);
	//Rectangle(getMemDC(), _rcMouse);
	
	IMAGEMANAGER->render("jojo_save1", getMemDC(), _rcSave.left, _rcSave.top - 10);
	IMAGEMANAGER->render("jojo_save2", getMemDC(), _rcLoad.left, _rcLoad.top - 10);
	IMAGEMANAGER->render("jojo_save1", getMemDC(), _rcTerrain.left - 30, _rcTerrain.top - 30);
	//IMAGEMANAGER->render("jojo_save", getMemDC(), _rcObject.left - 10, _rcObject.top - 30);
	//IMAGEMANAGER->render("jojo_save", getMemDC(), _rcEraser.left + 10, _rcEraser.top - 30);
	IMAGEMANAGER->render("jojo_arrowLeft", getMemDC(), _rcArrowLeft.left, _rcArrowLeft.top - 15);
	IMAGEMANAGER->render("jojo_arrowRight", getMemDC(), _rcArrowRight.left, _rcArrowRight.top - 15);

	//버튼렉트 글씨
	SetBkMode(getMemDC(), TRANSPARENT);
	//TextOut(getMemDC(), _rcSave.left + 40, _rcSave.top + 30, "저장", strlen("저장"));
	//TextOut(getMemDC(), _rcLoad.left + 20, _rcLoad.top + 30, "불러오기", strlen("불러오기"));
	//TextOut(getMemDC(), _rcTerrain.left, _rcTerrain.top + 10, "TERRAIN", strlen("TERRAIN"));
	//TextOut(getMemDC(), _rcObject.left + 10, _rcObject.top + 10, "OBJECT", strlen("OBJECT"));
	//TextOut(getMemDC(), _rcEraser.left + 30, _rcEraser.top + 10, "ERASER", strlen("ERASER"));

	IMAGEMANAGER->render("jojo_mouse", getMemDC(), _ptMouse.x, _ptMouse.y);			// 백학선
}

void tileMap::maptoolSetup(void)
{
	//왼쪽 게임화면 렉트 초기화
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tiles[i * TILEX + j].rc = RectMake(j * TILESIZE - CAMERAMANAGER->getCamera().left, i * TILESIZE - CAMERAMANAGER->getCamera().top, TILESIZE, TILESIZE);
		}
	}

	//오른쪽 샘플타일 렉트 초기화
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].rc = RectMake(1100 + j * TILESIZE * 2, 50 + i * TILESIZE * 2, TILESIZE, TILESIZE);

			//지형세팅
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;
		}
	}	

	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles1[i * SAMPLETILEX + j].rc = RectMake(1100 + j * TILESIZE * 2, 50 + i * TILESIZE * 2, TILESIZE, TILESIZE);

			_sampleTiles1[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles1[i * SAMPLETILEX + j].terrainFrameY = i;
		}
	}

	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles2[i * SAMPLETILEX + j].rc = RectMake(1100 + j * TILESIZE * 2, 50 + i * TILESIZE * 2, TILESIZE, TILESIZE);

			_sampleTiles2[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles2[i * SAMPLETILEX + j].terrainFrameY = i;
		}
	}
}

void tileMap::setMap(void)
{
	if (_page == PAGE_ONE)
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTiles[i].rc, _ptMouse))
			{
				_currentTile.x = _sampleTiles[i].terrainFrameX;
				_currentTile.y = _sampleTiles[i].terrainFrameY;
				break;
			}
		}
	}
	
	if (_page == PAGE_TWO)
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTiles1[i].rc, _ptMouse))
			{
				_currentTile.x = _sampleTiles1[i].terrainFrameX;
				_currentTile.y = _sampleTiles1[i].terrainFrameY + SAMPLETILEY;
				break;
			}
		}
	}

	if (_page == PAGE_THREE)
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			if (PtInRect(&_sampleTiles2[i].rc, _ptMouse))
			{
				_currentTile.x = _sampleTiles2[i].terrainFrameX;
				_currentTile.y = _sampleTiles2[i].terrainFrameY + SAMPLETILEY * 2;
				break;
			}
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (_isCollision)
			{
				//현재버튼이 지형이냐?
				if (_ctrlSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].x = _currentTile.x;
					_tiles[i].y = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//현재버튼이 오브젝트냐?
				if (_ctrlSelect == CTRL_OBJDRAW)
				{
					_tiles[i].objFrameX = _currentTile.x;
					_tiles[i].objFrameY = _currentTile.y;
					_tiles[i].obj = objectSelect(_currentTile.x, _currentTile.y);
				}
				//현재버튼이 지우개냐?
				if (_ctrlSelect == CTRL_ERASER)
				{
					_tiles[i].objFrameX = 0;
					_tiles[i].objFrameY = 0;
					_tiles[i].obj = OBJECT_NONE;
				}
			}
		}
	}
}

void tileMap::save(void)
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void tileMap::load(void)
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}


TERRAIN tileMap::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}
	if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	return TR_GROUND;
}

OBJECT tileMap::objectSelect(int frameX, int frameY)
{
	return OBJECT_BLOCK1;
}