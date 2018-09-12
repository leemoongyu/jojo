#include "stdafx.h"
#include "effectTestScene.h"

HRESULT effectTestScene::init(void)
{
	//�����̹���
	IMAGEMANAGER->addFrameImage("��������Ʈ", "explosion.bmp", 832, 62, 26, 1);

	//����Ʈ Ŭ���� �ʱ�ȭ
	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("��������Ʈ"), 0.3f);

	/*����Ʈ �Ŵ��� ����*/
	EFFECTMANAGER->addEffect("����", "��������Ʈ", 0.2f, 100);

	return S_OK;
}

void effectTestScene::release(void)
{
	//����Ʈ Ŭ���� ����
	_effect->release();
	SAFE_DELETE(_effect);

	/*����Ʈ �Ŵ��� ����*/
	//�̹����Ŵ��� ó�� ���� Ŭ���� �������� �ʿ� ����
}

void effectTestScene::update(void)
{
	//����Ʈ Ŭ���� ������Ʈ
	_effect->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//����Ʈ ��Ʈ�� ��ǥ
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}

	/*����Ʈ �Ŵ��� ����*/
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("����", _ptMouse.x, _ptMouse.y);
	}

}

void effectTestScene::render(void)
{
	//MY_UTIL �ȿ� �׳� �����ϰ� ����� �ξ���
	//������� ����� �� ���� ����
	showTitle(getMemDC(), "����Ʈ �׽�Ʈ");

	//����Ʈ Ŭ���� ����
	_effect->render();
}
