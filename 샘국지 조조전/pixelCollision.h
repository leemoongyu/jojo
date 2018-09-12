#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:
	image* _mountain;		//��׶��� �̹���
	image* _ball;			//�� �̹���
	RECT _rc;				//�� ��Ʈ
	
	float _x, _y;			//��ġ��ǥ
	int _probeY;			//�ȼ��浹 Ž���� y��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollision() {}
	~pixelCollision() {}
};

