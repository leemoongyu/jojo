#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT gameNode::init(void)
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
		RND->init();						//������� �ʱ�ȭ
		IMAGEMANAGER->init();				//�̹����Ŵ��� �ʱ�ȭ
		SAVEDATA->init();					//���̺굥���� �ʱ�ȭ
		TXTDATA->init();					//TXT������ �ʱ�ȭ
		SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
		INIDATA->init();					//INI������ �ʱ�ȭ
		TIMEMANAGER->init();				//Ÿ�ӸŴ��� �ʱ�ȭ
		SOUNDMANAGER->init();				//����Ŵ��� �ʱ�ȭ
		EFFECTMANAGER->init();				//����Ʈ�Ŵ��� �ʱ�ȭ
		CAMERAMANAGER->init();
	}

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//������� �̱��� ����
		RND->release();
		RND->releaseSingleton();
		//�̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//���̺굥���� �̱��� ����
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//TXT������ �̱��� ����
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		//���Ŵ��� �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//INI������ �̱��� ����
		INIDATA->release();
		INIDATA->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		//����Ŵ��� �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//����Ʈ�Ŵ��� �̱��� ����
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
	}

	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void gameNode::update(void)
{
}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void gameNode::render(void)
{
}

//=============================================================
//	## �������ν��� ##
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:		
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		
		switch (wParam)
		{
		case VK_ESCAPE:		
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
