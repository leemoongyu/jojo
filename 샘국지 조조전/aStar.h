#pragma once
#include "gameNode.h"
#include "aStarTile.h"
#include "jojo.h"


#define TILEWIDTH 64
#define TILEHEIGHT 64

#define TILENUMX ((int)(WINSIZEX / TILEWIDTH))
#define TILENUMY ((int)(WINSIZEX / TILEHEIGHT))

class aStar : public gameNode
{
private:

	int _maxWidthIndex, _maxHeightIndex;
	// ��üŸ�Ϻ���
	vector<aStarTile*> _vTotalList;
	// �����ִ±� �־�� ����
	vector<aStarTile*> _vOpenList;
	// �������±� �־�� ����
	vector<aStarTile*> _vCloseList;

	aStarTile* _startTile;				// ����Ÿ��
	aStarTile* _endTile;				// ����Ÿ��
	aStarTile* _currentTile;			// ����Ÿ��

	//jojo * _jojoTile;

	bool _isStart;
	int _count;

public:

	HRESULT init(int maxWidthIndex, int maxHeightIndex);
	void release(void);
	void update(void);
	void render(void);
	
	void seting(POINT start, POINT end);
	void setting(int startX, int startY, int endX,int endY);
	HRESULT initNode();

	vector<POINT> startPathFind(POINT start, POINT end);
	vector<POINT> startPathFind(int startX, int startY, int endX, int endY);

	void addOpenList(aStarTile* currentTile);

	aStar(){}
	~aStar(){}
};

