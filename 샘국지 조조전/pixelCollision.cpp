#include "stdafx.h"
#include "pixelCollision.h"


HRESULT pixelCollision::init(void)
{
	//��׶��� �̹���
	_mountain = IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//�� �̹���
	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//�� ��ġ �ʱ�ȭ
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//y������ Ž��(���� �ϴܿ� �簢�� �����)
	_probeY = _y + _ball->getHeight() / 2;

	return S_OK;
}

void pixelCollision::release(void)
{
}

void pixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;
	}
	//���� ��Ʈ�� ��������
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
	//y������ Ž��(���� �ϴ� ���� ��Ʈ)
	_probeY = _y + _ball->getHeight() / 2;

	/*�̺κ��� �ȼ��浹�� �ٽ�*/
	//Ž���� y���� ������ ���Ʒ��� ���ϴ� ��ŭ �˻縦 �Ѵ�
	for (int i = _probeY - 50; i < _probeY + 50; i++)
	{
		COLORREF color = GetPixel(_mountain->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->loadScene("�׽�Ʈ��");
	}


}

void pixelCollision::render(void)
{
	//��׶��� ����
	_mountain->render(getMemDC());
	//�� �̹��� ����
	_ball->render(getMemDC(), _rc.left, _rc.top);

	if (KEYMANAGER->isToggleKey('A'))
	{
		//���� �簢�� ����
		RECT rc = RectMakeCenter(_x, _probeY, 10, 10);
		Rectangle(getMemDC(), rc);
	}

}
