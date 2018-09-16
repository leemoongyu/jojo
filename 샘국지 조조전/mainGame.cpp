#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�
	
	//������ ���ΰ��� Ŭ���� �ȿ����� ���鸸 �����Ѵ�
	//�׸��� ������ ������ ���ΰ��� ������ �ϸ� �ȴ�

	/*���߰�*/
	//SCENEMANAGER->addScene("�ȼ��浹", new pixelCollision);
	//SCENEMANAGER->addScene("�׽�Ʈ��", new sceneTest);
	//SCENEMANAGER->addScene("ini", new iniTestScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	//SCENEMANAGER->addScene("����", new soundTestScene);
	//SCENEMANAGER->addScene("�ִϸ��̼�", new aniTestScene);
	//SCENEMANAGER->addScene("����Ʈ", new effectTestScene);
	//SCENEMANAGER->addScene("������Ʈ", new rotateTestScene);
	SCENEMANAGER->addScene("����������", new tankGameScene);
	SCENEMANAGER->addScene("�������ε�", new loadingScene);
	SCENEMANAGER->addScene("����������", new jojoGameScene);

	/*����� ����*/
	SCENEMANAGER->loadScene("�������ε�");
	_img = IMAGEMANAGER->addImage("jojo_hand", "resource/jojo/jojo_hand.bmp", 50, 50, true, RGB(255, 0, 255));

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void mainGame::update(void)
{
	ShowCursor(false);
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();

	//����Ŵ��� ������Ʈ
	SOUNDMANAGER->update();

	//����Ʈ�Ŵ��� ������Ʈ
	EFFECTMANAGER->update();
}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ��(�̰͵� ������ �׳� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//���Ŵ��� ����
	SCENEMANAGER->render();

	//����Ʈ�Ŵ��� ����
	EFFECTMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());

	IMAGEMANAGER->render("jojo_hand", getMemDC(), _ptMouse.x, _ptMouse.y);

//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}
