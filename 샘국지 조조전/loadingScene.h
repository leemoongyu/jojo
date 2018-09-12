#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading * _loading;

	int index = 0;
	image * _img;
	int count = 0;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();
	//�ε����� �Լ�(�̰��� ���带 ���� �־��)
	void loadingSound();

	loadingScene() {}
	~loadingScene() {}
};

