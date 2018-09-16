#pragma once
#include "gameNode.h"
#include "tileNode.h"

class jojo : public gameNode
{
private:

	RECT _rcJojo;

	RECT _jojoRangeTop[MOVE_RANGE_TOP];
	RECT _jojoRangeBottom[MOVE_RANGE_BOTTOM];
	RECT _rcTemp;

	float _x, _y;
	float _winth, _height;

	bool _isJojo;

	int _count, _index;

	POINT _MouseCamera;

public:

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	float getWinth() { return _winth; }
	void setWiinth(float winth) { _winth = winth; }
	float getHeight() { return _height; }
	void setHeight(float height) { _height = height; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	jojo() {}
	~jojo() {}
};

