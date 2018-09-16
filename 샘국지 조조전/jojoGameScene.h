#pragma once
#include "gameNode.h"
#include "jojo.h"
#include "jojoMap.h"
#include "heojeo.h"

class jojoGameScene : public gameNode
{
private:

	jojo * _jojo;
	jojoMap * _jojoMap;
	heojeo * _heojeo;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	jojoGameScene() {}
	~jojoGameScene() {}
};

