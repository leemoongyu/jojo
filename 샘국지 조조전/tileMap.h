#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tileMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	//왼쪽화면 타일(총 400개)
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//오른쪽화면 타일(총 20개)
	tagSampleTile _sampleTiles1[SAMPLETILEX * SAMPLETILEY];
	tagSampleTile _sampleTiles2[SAMPLETILEX * SAMPLETILEY];
	tagCurrentTile _currentTile;	//현재타일

									//버튼 5개(세이브, 로드, 지형, 오브젝트, 지우개)
	RECT _rcSave, _rcLoad, _rcTerrain, _rcObject, _rcEraser;

	CTRL _ctrlSelect;
	PAGE _page;

	RECT _rcCamera;					// 카메라 이동 렉트
	RECT _rcPlayer;
	RECT _rcArrowLeft;				// 화살표 왼쪽 렉트
	RECT _rcArrowRight;				// 화살표 오른쪽 렉트
	RECT _rcMouse;					// 타일 담을 렉트
	RECT _rcDrag;					// 드래그 렉트
	RECT _rcEdge[BOX_X * BOX_Y];	// 테두리 렉트
	RECT temp;
	RECT _rcBg;

	float startX, startY;			// 드래그 값 담을 스타트
	float endX, endY;				// 드래그 값 담을 엔드

	bool _start;					// 드래그 껏다킬 불변수
	bool _click;					
	bool _isCollision;				// 타일 터치하면 타일 안나오게할 불변수
	bool _isDrag;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//맵툴세팅
	void maptoolSetup(void); //초기화에 넣어두면 된다
							 //맵세팅
	void setMap(void);
	//세이브
	void save(void);
	//로드
	void load(void);

	//지형, 오브젝트 셋터
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	tileMap() {}
	~tileMap() {}
};