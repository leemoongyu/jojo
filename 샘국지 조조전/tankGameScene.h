#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include "jojo.h"

class tankGameScene : public gameNode
{
private:
	tileMap * _tileMap;
	jojo * _jojo;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	tankGameScene() {}
	~tankGameScene() {}
};