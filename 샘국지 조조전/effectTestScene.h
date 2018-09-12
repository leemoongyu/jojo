#pragma once
#include "gameNode.h"
#include "effect.h"		//����Ʈ Ŭ���� �߰�

class effectTestScene : public gameNode
{
private:
	effect * _effect;	//����Ʈ Ŭ���� ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	effectTestScene() {}
	~effectTestScene() {}
};

