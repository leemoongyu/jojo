#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init(void)
{
	return S_OK;
}

void iniTestScene::release(void)
{
}

void iniTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//����, Ű, ���
		//[����]
		//���=99
		//����=70
		//[����]
		//�ѽǷ�=20
		//�ڵ���=80
		INIDATA->addData("����", "���", "99");
		INIDATA->addData("����", "����", "70");
		INIDATA->addData("����", "�ѽǷ�", "20");
		INIDATA->addData("����", "�ڵ���", "80");
		INIDATA->addData("����", "�Ǽ�", "15.8f");
		//�����̸����� ���̺�
		INIDATA->saveINI("ARVR");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//int num = INIDATA->loadDataInteger("ARVR", "����", "�ѽǷ�");
		float num = INIDATA->loadDataFloat("ARVR", "����", "�Ǽ�");
		cout << "������ �Ǽ���: " << num << endl;
	}
}

void iniTestScene::render(void)
{
}
