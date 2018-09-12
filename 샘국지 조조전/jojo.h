#pragma once
#include "gameNode.h"

class jojo : public gameNode
{
private:
	image * _jojo;

	RECT _rc;

	float _x, _y;
	float _winth, _height;

	int _count, _index;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	jojo() {}
	~jojo() {}
};

