#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tileMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];	//����ȭ�� Ÿ��(�� 400��)
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];	//������ȭ�� Ÿ��(�� 20��)
	tagSampleTile _sampleTiles1[SAMPLETILEX * SAMPLETILEY];
	tagSampleTile _sampleTiles2[SAMPLETILEX * SAMPLETILEY];
	tagCurrentTile _currentTile;	//����Ÿ��

									//��ư 5��(���̺�, �ε�, ����, ������Ʈ, ���찳)
	RECT _rcSave, _rcLoad, _rcTerrain, _rcObject, _rcEraser;

	CTRL _ctrlSelect;
	PAGE _page;

	RECT _rcCamera;					// ī�޶� �̵� ��Ʈ
	RECT _rcPlayer;
	RECT _rcArrowLeft;				// ȭ��ǥ ���� ��Ʈ
	RECT _rcArrowRight;				// ȭ��ǥ ������ ��Ʈ
	RECT _rcMouse;					// Ÿ�� ���� ��Ʈ
	RECT _rcDrag;					// �巡�� ��Ʈ
	RECT _rcEdge[BOX_X * BOX_Y];	// �׵θ� ��Ʈ
	RECT temp;
	RECT _rcBg;

	float startX, startY;			// �巡�� �� ���� ��ŸƮ
	float endX, endY;				// �巡�� �� ���� ����

	bool _start;					// �巡�� ����ų �Һ���
	bool _click;					
	bool _isCollision;				// Ÿ�� ��ġ�ϸ� Ÿ�� �ȳ������� �Һ���
	bool _isDrag;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//��������
	void maptoolSetup(void); //�ʱ�ȭ�� �־�θ� �ȴ�
							 //�ʼ���
	void setMap(void);
	//���̺�
	void save(void);
	//�ε�
	void load(void);

	//����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	tileMap() {}
	~tileMap() {}
};