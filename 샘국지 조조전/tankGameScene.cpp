#include "stdafx.h"
#include "tankGameScene.h"

HRESULT tankGameScene::init(void)
{
	_tileMap = new tileMap;
	_tileMap->init();
	_jojo = new jojo;
	_jojo->init();

	return S_OK;
}

void tankGameScene::release(void)
{
	_tileMap->release();
	SAFE_DELETE(_tileMap);
	_jojo->release();
	SAFE_DELETE(_jojo);
}

void tankGameScene::update(void)
{
	_tileMap->update();
	_jojo->update();
}

void tankGameScene::render(void)
{
	_tileMap->render();
	_jojo->render();
}