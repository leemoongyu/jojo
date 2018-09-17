#pragma once
#include "gameNode.h"
#include "tileNode.h"

class jojoMap : public gameNode
{
private:
	image * _map;			// �� �̹���
	
	tagTile _mapTile[TILEX * TILEY];

	RECT _camera;			// ī�޶� �̵���Ʈ
	RECT _rcMouse;			// ���콺�� ��Ʈ �޾Ƽ� �浹ó���� ��Ʈ
	RECT _cursor;			// Ŀ�� ���α�� ��Ʈ
	RECT _rcCamera[4];		// �� ������������ ��Ƽ� �浹ó���� ��Ʈ
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

