#include "stdafx.h"
#include "jojoGameScene.h"

HRESULT jojoGameScene::init(void)
{
	_jojoMap = new jojoMap;
	_jojoMap->init();
	_jojo = new jojo;
	_jojo->init();
	_heojeo = new heojeo;
	_heojeo->init();

	return S_OK;
}

void jojoGameScene::release(void)
{
	_jojoMap->release();
	SAFE_DELETE(_jojoMap);
	_jojo->release();
	SAFE_DELETE(_jojo);
	_heojeo->release();
	SAFE_DELETE(_heojeo);
}

void jojoGameScene::update(void)
{
	_jojoMap->update();
	_jojo->update();
	_heojeo->update();
}

void jojoGameScene::render(void)
{
	_jojoMap->render();
	_jojo->render();
	_heojeo->render();
}
