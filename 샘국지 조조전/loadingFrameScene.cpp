#include "stdafx.h"
#include "loadingFrameScene.h"

HRESULT loadingFrameScene::init(void)
{
	//this->loadingImage();
	_loadingFrame = new loadingFrame;
	_loadingFrame->init();
	return S_OK;
}

void loadingFrameScene::release(void)
{
	
}

void loadingFrameScene::update(void)
{
	_loadingFrame->update();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_loadingFrame->loadingDone())
		{
			SCENEMANAGER->loadScene("Á¶Á¶Àü¸ÊÅø");
		}
	}
}

void loadingFrameScene::render(void)
{
	_loadingFrame->render();
}

void loadingFrameScene::loadingImage()
{
	
}

