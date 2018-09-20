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

	RECT getRcHeojeo() { return _rcHeojeo; }
	void setRcHeojeo(RECT rcHeojeo) { _rcHeojeo = rcHeojeo; }
	bool getIsHeojeo() { return _isHeojeo; }
	void setIsHeojeo(bool isHeojeo) { _isHeojeo = isHeojeo; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	heojeo(){}
	~heojeo(){}
};

