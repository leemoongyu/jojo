#pragma once
#include "gameNode.h"
#include "tileNode.h"

class jojo : public gameNode
{
private:

	RECT _rcJojo;
	RECT _rcRange[11];

	RECT _rc[2];

	float _x, _y;
	float _winth, _height;

	int _count, _index;

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

