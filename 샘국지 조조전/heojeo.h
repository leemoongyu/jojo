#pragma once
#include "gameNode.h"
#include "tileNode.h"

class heojeo : public gameNode
{
private:

	RECT _rcHeojeo;
	RECT _heojeoRangeTop[MOVE_RANGE_TOP];
	RECT _heojeoRangeBottom[MOVE_RANGE_BOTTOM];

	float _x, _y;
	float _width, _height;

	int _index, _count;

	bool _isHeojeo;

	POINT _MouseCamera;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	heojeo(){}
	~heojeo(){}
};

