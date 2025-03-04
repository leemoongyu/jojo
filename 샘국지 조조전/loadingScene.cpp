#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();


	string str = "resource/title_Resource/title (" + to_string(1) + ").bmp";
	_img = new image;
	_img->init(str.c_str(), WINSIZEX, WINSIZEY);
	index = 1;

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 씬변경
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_loading->loadingDone()) 
		{
			//SCENEMANAGER->loadScene("픽셀충돌");
			SCENEMANAGER->loadScene("조조전맵툴");
		}
	}
	
	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	float num = _loading->getLoadItem().size();
	//	float cur = _loading->getCurrnetGauge();
	//	float per = cur / num * 100;
	//	cout << "전체 파일갯수 : " << num << endl;
	//	cout << "현재 로딩갯수 : " << cur << endl;
	//	cout << per << " %" << endl;
	//}
}

void loadingScene::render(void)
{
	count++;
	if (count % 7 == 0)
	{
		_img->release();
		SAFE_DELETE(_img);

		string str = "resource/title_Resource/title (" + to_string(index + 1) + ").bmp";
		_img = new image;
		_img->init(str.c_str(), WINSIZEX, WINSIZEY);
		index = index + 1;
	}
	_img->render(getMemDC());
	//로딩클래스 렌더
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
	//sprintf_s(str, "%.f", per);
	//TextOut(getMemDC(), 660, 430, str, strlen(str));

}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	SetBkMode(getMemDC(), TRANSPARENT);
	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	//for (int i = 0; i < 570; i++)
	//{
	//	char str[128];
	//	sprintf_s(str, "%s_%d", "testImage", i + 1);
	//	_loading->loadImage(str, WINSIZEX, WINSIZEY);
	//}

	IMAGEMANAGER->addImage("jojo_test", "resource/jojo/jojo_test.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_moveRange", "resource/jojo/jojo_moveRange.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jojo_attRange", "resource/jojo/jojo_attRange.bmp", 64, 64, true, RGB(255, 0, 255));

	////IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	////백그라운드 이미지
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

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
	_loading->loadSound("사운드1", "브금.mp3");
	_loading->loadSound("사운드2", "브금1.mp3");
}
