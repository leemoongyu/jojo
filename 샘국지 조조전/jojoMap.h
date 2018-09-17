#pragma once
#include "gameNode.h"
#include "tileNode.h"

class jojoMap : public gameNode
{
private:
	image * _map;			// 맵 이미지
	
	tagTile _mapTile[TILEX * TILEY];

	RECT _camera;			// 카메라 이동렉트
	RECT _rcMouse;			// 마우스에 렉트 달아서 충돌처리할 렉트
	RECT _cursor;			// 커서 가두기용 렉트
	RECT _rcCamera[4];		// 맵 동서남북으로 깔아서 충돌처리할 렉트
	RECT _rcTemp;			

public:

	tagTile* getMapTile() { return _mapTile; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	jojoMap() {}
	~jojoMap() {}
};

