#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "aStar.h"
#include "jojoMap.h"


class jojo : public gameNode
{
private:

	//aStar * _aStar;
	jojoMap * _jojoMap;

	RECT _rcJojo;

	tagSampleTile _jojoRangeTop[MOVE_RANGE_TOP];
	tagSampleTile _jojoRangeBottom[MOVE_RANGE_BOTTOM];
	RECT _rcTemp;
	
	float _x, _y;
	float _width, _height;

	bool _isJojo;

	int _count, _index;

	POINT _MouseCamera;

public:

	RECT getRcJojo() { return _rcJojo; }
	void setRcJojo(RECT rcJojo) { _rcJojo = rcJojo; }
	
	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	float getWidth() { return _width; }
	void setWidth(float winth) { _width = winth; }
	float getHeight() { return _height; }
	void setHeight(float height) { _height = height; }

	bool getIsJojo() { return _isJojo; }
	void setIsJojo(bool isJojo) { _isJojo = isJojo; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	jojo() {}
	~jojo() {}
};

