#pragma once
#include "gameNode.h"
/*앞으로는 씬 헤더파일만 추가해준다*/
#include "pixelCollision.h"
#include "sceneTest.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"
#include "aniTestScene.h"
#include "effectTestScene.h"
#include "rotateTestScene.h"
#include "tankGameScene.h"
#include "jojoGameScene.h"

class mainGame : public gameNode
{
private:
	image * _img;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

