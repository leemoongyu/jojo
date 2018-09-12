#include "stdafx.h"
#include "rotateTestScene.h"

HRESULT rotateTestScene::init(void)
{
	_missile = IMAGEMANAGER->addImage("�̻���1", "missile1.bmp", 26, 124, true, RGB(255, 0, 255));
	_frameMissle = IMAGEMANAGER->addFrameImage("�̻���2", "missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
	
	_count = 0;

	return S_OK;
}

void rotateTestScene::release(void)
{
}

void rotateTestScene::update(void)
{
	//�̻��� �ִϸ��̼�
	_count++;
	if (_count % 5 == 0)
	{
		_frameMissle->setFrameX(_frameMissle->getFrameX() + 1);
		if (_frameMissle->getFrameX() >= _frameMissle->getMaxFrameX())
		{
			_frameMissle->setFrameX(0);
			_count = 0;
		}
	}

	//������ ȭ�� ������ ���콺 ��ǥ�� ���ϱ�
	_angle = getAngle(WINSIZEX / 2, WINSIZEY / 2, _ptMouse.x, _ptMouse.y);
}

void rotateTestScene::render(void)
{
	showTitle(getMemDC(), "������Ʈ �׽�Ʈ");

	//�̻��� ������Ʈ����
	_missile->rotateRender(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, _angle);
	//�̻��� ������Ʈ�����ӷ���
	_frameMissle->rotateFrameRender(getMemDC(), WINSIZEX / 2 + 200, WINSIZEY / 2, _angle);
}
