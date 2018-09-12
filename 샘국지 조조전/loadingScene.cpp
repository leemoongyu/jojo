#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ������
	if (_loading->loadingDone()) //&& SCENEMANAGER->loadScene("�������ռ�"))
	{
		//SCENEMANAGER->loadScene("�ȼ��浹");
		SCENEMANAGER->loadScene("�������ռ�");
	}
	
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	float num = _loading->getLoadItem().size();
	//	float cur = _loading->getCurrnetGauge();
	//	float per = cur / num * 100;
	//	cout << "��ü ���ϰ��� : " << num << endl;
	//	cout << "���� �ε����� : " << cur << endl;
	//	cout << per << " %" << endl;
	//}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();

	//if (_loading->getCurrnetGauge() < _loading->getLoadItem().size())
	//{
	//	char str[128];
	//	sprintf_s(str, "%s.bmp", _loading->getLoadItem()[_loading->getCurrnetGauge()]->getImageResource().keyName.c_str());
	//	TextOut(getMemDC(), 120, 430, str, strlen(str));
	//}
	//
	//float num = _loading->getLoadItem().size();
	//float cur = _loading->getCurrnetGauge();
	//float per = cur / num * 100;
	//char str[128];
	//sprintf_s(str, "%.f %%", per);
	//TextOut(getMemDC(), 660, 430, str, strlen(str));

}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	SetBkMode(getMemDC(), TRANSPARENT);
	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	for (int i = 0; i < 570; i++)
	{
		char str[128];
		sprintf_s(str, "%s_%d", "testImage", i + 1);
		_loading->loadImage(str, WINSIZEX, WINSIZEY);
	}
	////IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	////��׶��� �̹���
	//for (int i = 0; i < 500; i++)
	//{
	//	char str[128];
	//	sprintf_s(str, "%s_%d", "mountain", i + 1);
	//	_loading->loadImage(str, "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//}
	//IMAGEMANAGER->addImage("jojo_loading00", "jojo_loading00.bmp", WINSIZEX, WINSIZEY);
	
	//for (int i = 0; i < 201; i++)
	//{
	//	string str;
	//	string str1;
	//	str = "resource/title_Resource/title (" + to_string(i + 1) + ").bmp";
	//	str1 = "title(" + to_string(i + 1) + ")";
	//	
	//	IMAGEMANAGER->addImage(str1.c_str(), str.c_str(), WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//}
	//for (int i = 0; i < 201; i++)
	//{
	//	str = "resource/title_Resource/title (" + to_string(i + 1) + ").bmp";
	//	_title[i] = new image;
	//	_title[i]->init(str.c_str(), WINSIZEX, WINSIZEY);
	//}

}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
	_loading->loadSound("����1", "���.mp3");
	_loading->loadSound("����2", "���1.mp3");
}
