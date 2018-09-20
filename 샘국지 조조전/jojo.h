#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "aStar.h"
#include "jojoMap.h"
#include "heojeo.h"

struct tagJojo
{
	RECT rc;
	float x, y;
	float width, height;
	int index, count;
	int indexX, indexY;

};

class jojo : public gameNode
{
private:

	//aStar * _aStar;
	jojoMap * _jojoMap;
	heojeo * _heojeo;

	tagSampleTile _jojoRange[MOVE_RANGE];
	tagCurrentTile _currentTile;
	tagCurrentTile _currentTile1;

	tagCurrentTile _current;

	tagJojo _jojo;

	RECT _rcTemp;

	int indexX;
	int indexY;

	int tempX;
	int tempY;

	bool _isJojo;
	bool _isRange;

	int _count, _index;

	POINT _MouseCamera;

public:

	tagJojo getJojo() { return _jojo; }
	void setJojo(tagJojo jojo) { _jojo = jojo; }
	bool getIsJojo() { return _isJojo; }
	void setIsJojo(bool isJojo) { _isJojo = isJojo; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	jojo() {}
	~jojo() {}
};

