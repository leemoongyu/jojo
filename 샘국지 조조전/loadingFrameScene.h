#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingFrameScene : public gameNode
{
private:
	
	loadingFrame * _loadingFrame;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void loadingImage();

	loadingFrameScene() {}
	~loadingFrameScene() {}
};

