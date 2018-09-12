#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (로드아이템 클래스)
//=============================================================
HRESULT loadItem::init(string keyName, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;
	//이미지 구조체 초기화
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

//사운드 초기화
HRESULT loadItem::initForSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_SOUND;
	//사운드 구조체 초기화
	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}

//=============================================================
//	## loading ## (로딩클래스)
//=============================================================
HRESULT loading::init(void)
{
	string str;
	
	for (int i = 0; i < 201; i++)
	{
		str = "resource/title_Resource/title (" + to_string(i + 1) + ").bmp";
		_vTitle.push_back(new image);
		_vTitle[i]->init(str.c_str(), WINSIZEX, WINSIZEY);
	}

	_count = 0.f;

	//로딩화면 백그라운드 이미지 초기화
	_background = IMAGEMANAGER->addImage("jojo_loading", "jojo_loading.bmp", WINSIZEX, WINSIZEY);
	//_loadingFrameScene = IMAGEMANAGER->addImage("jojo_loading00", "jojo_loading00.bmp", WINSIZEX, WINSIZEY);
	
	//로딩바 클래스 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack", 500, 750, 500, 20);
	_loadingBar->setGauge(0, 0);
	//현재 게이지 초기화
	_currentGauge = 0;

	return S_OK;
}

void loading::release(void)
{
	//로딩바 클래스 해제
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update(void)
{
	//로딩바 클래스 업데이트
	_loadingBar->update();

	_count+=0.2f;

	if (_count >= 201.f)
	{
		_count = 0.f;
	}
}

void loading::render(void)
{
	//백그라운드 렌더
	//ackground->render(getMemDC());
	//_loadingFrameScene->render(getMemDC());
	
	_vTitle[(int)_count]->render(getMemDC());

	//로딩바 클래스 렌더
	_loadingBar->render();
	
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	//로딩이 완료됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;
	case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		}
		break;
	case LOAD_KIND_IMAGE_2:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_0:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	case LOAD_KIND_FRAMEIMAGE_1:
		{	tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}	
		break;
	//곧 사운드 배우고 난후 알아서...
	case LOAD_KIND_SOUND:
		{
			tagSoundResource soundResource = item->getSoundResource();
			SOUNDMANAGER->addSound(soundResource.keyName, soundResource.fileName, soundResource.bgm, soundResource.loop);
		}
		break;
	}

	//현재게이지 증가
	_currentGauge++;

	//로딩바 이미지 변경
	//_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return 0;
}
//=============================================================
//	## loadingFrame ## (로딩프레임클래스)
//=============================================================
HRESULT loadingFrame::init(void)
{
	//로딩화면 백그라운드 이미지 초기화
	//_loadingFrameScene = IMAGEMANAGER->addImage("jojo_loading00", "jojo_loading00.bmp", WINSIZEX, WINSIZEY);
	//string str;
	//
	//for (int i = 0; i < 201; i++)
	//{
	//	str = "resource/title_Resource/title (" + to_string(i + 1) + ").bmp";
	//	_title[i] = new image;
	//	_title[i]->init(str.c_str(), WINSIZEX, WINSIZEY);
	//}


	/*
	{
		_title[0] = IMAGEMANAGER->addImage("title1", "resource/title_Resource/title (1).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[1] = IMAGEMANAGER->addImage("title2", "resource/title_Resource/title (2).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[2] = IMAGEMANAGER->addImage("title3", "resource/title_Resource/title (3).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[3] = IMAGEMANAGER->addImage("title4", "resource/title_Resource/title (4).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[4] = IMAGEMANAGER->addImage("title5", "resource/title_Resource/title (5).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[5] = IMAGEMANAGER->addImage("title6", "resource/title_Resource/title (6).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[6] = IMAGEMANAGER->addImage("title7", "resource/title_Resource/title (7).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[7] = IMAGEMANAGER->addImage("title8", "resource/title_Resource/title (8).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[8] = IMAGEMANAGER->addImage("title9", "resource/title_Resource/title (9).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[9] = IMAGEMANAGER->addImage("title10", "resource/title_Resource/title (10).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[10] = IMAGEMANAGER->addImage("title11", "resource/title_Resource/title (11).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[11] = IMAGEMANAGER->addImage("title12", "resource/title_Resource/title (12).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[12] = IMAGEMANAGER->addImage("title13", "resource/title_Resource/title (13).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[13] = IMAGEMANAGER->addImage("title14", "resource/title_Resource/title (14).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[14] = IMAGEMANAGER->addImage("title15", "resource/title_Resource/title (15).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[15] = IMAGEMANAGER->addImage("title16", "resource/title_Resource/title (16).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[16] = IMAGEMANAGER->addImage("title17", "resource/title_Resource/title (17).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[17] = IMAGEMANAGER->addImage("title18", "resource/title_Resource/title (18).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[18] = IMAGEMANAGER->addImage("title19", "resource/title_Resource/title (19).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[19] = IMAGEMANAGER->addImage("title20", "resource/title_Resource/title (20).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[20] = IMAGEMANAGER->addImage("title21", "resource/title_Resource/title (21).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[21] = IMAGEMANAGER->addImage("title22", "resource/title_Resource/title (22).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[22] = IMAGEMANAGER->addImage("title23", "resource/title_Resource/title (23).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[23] = IMAGEMANAGER->addImage("title24", "resource/title_Resource/title (24).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[24] = IMAGEMANAGER->addImage("title25", "resource/title_Resource/title (25).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[25] = IMAGEMANAGER->addImage("title26", "resource/title_Resource/title (26).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[26] = IMAGEMANAGER->addImage("title27", "resource/title_Resource/title (27).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[27] = IMAGEMANAGER->addImage("title28", "resource/title_Resource/title (28).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[28] = IMAGEMANAGER->addImage("title29", "resource/title_Resource/title (29).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[29] = IMAGEMANAGER->addImage("title30", "resource/title_Resource/title (30).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[30] = IMAGEMANAGER->addImage("title31", "resource/title_Resource/title (31).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[31] = IMAGEMANAGER->addImage("title32", "resource/title_Resource/title (32).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[32] = IMAGEMANAGER->addImage("title33", "resource/title_Resource/title (33).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[33] = IMAGEMANAGER->addImage("title34", "resource/title_Resource/title (34).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[34] = IMAGEMANAGER->addImage("title35", "resource/title_Resource/title (35).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[35] = IMAGEMANAGER->addImage("title36", "resource/title_Resource/title (36).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[36] = IMAGEMANAGER->addImage("title37", "resource/title_Resource/title (37).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[37] = IMAGEMANAGER->addImage("title38", "resource/title_Resource/title (38).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[38] = IMAGEMANAGER->addImage("title39", "resource/title_Resource/title (39).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[39] = IMAGEMANAGER->addImage("title40", "resource/title_Resource/title (40).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[40] = IMAGEMANAGER->addImage("title41", "resource/title_Resource/title (41).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[41] = IMAGEMANAGER->addImage("title42", "resource/title_Resource/title (42).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[42] = IMAGEMANAGER->addImage("title43", "resource/title_Resource/title (43).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[43] = IMAGEMANAGER->addImage("title44", "resource/title_Resource/title (44).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[44] = IMAGEMANAGER->addImage("title45", "resource/title_Resource/title (45).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[45] = IMAGEMANAGER->addImage("title46", "resource/title_Resource/title (46).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[46] = IMAGEMANAGER->addImage("title47", "resource/title_Resource/title (47).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[47] = IMAGEMANAGER->addImage("title48", "resource/title_Resource/title (48).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[48] = IMAGEMANAGER->addImage("title49", "resource/title_Resource/title (49).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[49] = IMAGEMANAGER->addImage("title50", "resource/title_Resource/title (50).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[50] = IMAGEMANAGER->addImage("title51", "resource/title_Resource/title (51).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[51] = IMAGEMANAGER->addImage("title52", "resource/title_Resource/title (52).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[52] = IMAGEMANAGER->addImage("title53", "resource/title_Resource/title (53).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[53] = IMAGEMANAGER->addImage("title54", "resource/title_Resource/title (54).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[54] = IMAGEMANAGER->addImage("title55", "resource/title_Resource/title (55).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[55] = IMAGEMANAGER->addImage("title56", "resource/title_Resource/title (56).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[56] = IMAGEMANAGER->addImage("title57", "resource/title_Resource/title (57).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[57] = IMAGEMANAGER->addImage("title58", "resource/title_Resource/title (58).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[58] = IMAGEMANAGER->addImage("title59", "resource/title_Resource/title (59).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[59] = IMAGEMANAGER->addImage("title60", "resource/title_Resource/title (60).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[60] = IMAGEMANAGER->addImage("title61", "resource/title_Resource/title (61).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[61] = IMAGEMANAGER->addImage("title62", "resource/title_Resource/title (62).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[62] = IMAGEMANAGER->addImage("title63", "resource/title_Resource/title (63).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[63] = IMAGEMANAGER->addImage("title64", "resource/title_Resource/title (64).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[64] = IMAGEMANAGER->addImage("title65", "resource/title_Resource/title (65).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[65] = IMAGEMANAGER->addImage("title66", "resource/title_Resource/title (66).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[66] = IMAGEMANAGER->addImage("title67", "resource/title_Resource/title (67).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[67] = IMAGEMANAGER->addImage("title68", "resource/title_Resource/title (68).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[68] = IMAGEMANAGER->addImage("title69", "resource/title_Resource/title (69).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[69] = IMAGEMANAGER->addImage("title70", "resource/title_Resource/title (70).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[70] = IMAGEMANAGER->addImage("title71", "resource/title_Resource/title (71).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[71] = IMAGEMANAGER->addImage("title72", "resource/title_Resource/title (72).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[72] = IMAGEMANAGER->addImage("title73", "resource/title_Resource/title (73).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[73] = IMAGEMANAGER->addImage("title74", "resource/title_Resource/title (74).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[74] = IMAGEMANAGER->addImage("title75", "resource/title_Resource/title (75).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[75] = IMAGEMANAGER->addImage("title76", "resource/title_Resource/title (76).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[76] = IMAGEMANAGER->addImage("title77", "resource/title_Resource/title (77).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[77] = IMAGEMANAGER->addImage("title78", "resource/title_Resource/title (78).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[78] = IMAGEMANAGER->addImage("title79", "resource/title_Resource/title (79).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[79] = IMAGEMANAGER->addImage("title80", "resource/title_Resource/title (80).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[80] = IMAGEMANAGER->addImage("title81", "resource/title_Resource/title (81).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[81] = IMAGEMANAGER->addImage("title82", "resource/title_Resource/title (82).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[82] = IMAGEMANAGER->addImage("title83", "resource/title_Resource/title (83).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[83] = IMAGEMANAGER->addImage("title84", "resource/title_Resource/title (84).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[84] = IMAGEMANAGER->addImage("title85", "resource/title_Resource/title (85).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[85] = IMAGEMANAGER->addImage("title86", "resource/title_Resource/title (86).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[86] = IMAGEMANAGER->addImage("title87", "resource/title_Resource/title (87).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[87] = IMAGEMANAGER->addImage("title88", "resource/title_Resource/title (88).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[88] = IMAGEMANAGER->addImage("title89", "resource/title_Resource/title (89).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[89] = IMAGEMANAGER->addImage("title90", "resource/title_Resource/title (90).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[90] = IMAGEMANAGER->addImage("title91", "resource/title_Resource/title (91).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[91] = IMAGEMANAGER->addImage("title92", "resource/title_Resource/title (92).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[92] = IMAGEMANAGER->addImage("title93", "resource/title_Resource/title (93).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[93] = IMAGEMANAGER->addImage("title94", "resource/title_Resource/title (94).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[94] = IMAGEMANAGER->addImage("title95", "resource/title_Resource/title (95).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[95] = IMAGEMANAGER->addImage("title96", "resource/title_Resource/title (96).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[96] = IMAGEMANAGER->addImage("title97", "resource/title_Resource/title (97).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[97] = IMAGEMANAGER->addImage("title98", "resource/title_Resource/title (98).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[98] = IMAGEMANAGER->addImage("title99", "resource/title_Resource/title (99).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[99] = IMAGEMANAGER->addImage("title100", "resource/title_Resource/title (100).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[100] = IMAGEMANAGER->addImage("title101", "resource/title_Resource/title (101).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[101] = IMAGEMANAGER->addImage("title102", "resource/title_Resource/title (102).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[102] = IMAGEMANAGER->addImage("title103", "resource/title_Resource/title (103).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[103] = IMAGEMANAGER->addImage("title104", "resource/title_Resource/title (104).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[104] = IMAGEMANAGER->addImage("title105", "resource/title_Resource/title (105).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[105] = IMAGEMANAGER->addImage("title106", "resource/title_Resource/title (106).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[106] = IMAGEMANAGER->addImage("title107", "resource/title_Resource/title (107).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[107] = IMAGEMANAGER->addImage("title108", "resource/title_Resource/title (108).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[108] = IMAGEMANAGER->addImage("title109", "resource/title_Resource/title (109).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[109] = IMAGEMANAGER->addImage("title110", "resource/title_Resource/title (110).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[110] = IMAGEMANAGER->addImage("title111", "resource/title_Resource/title (111).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[111] = IMAGEMANAGER->addImage("title112", "resource/title_Resource/title (112).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[112] = IMAGEMANAGER->addImage("title113", "resource/title_Resource/title (113).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[113] = IMAGEMANAGER->addImage("title114", "resource/title_Resource/title (114).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[114] = IMAGEMANAGER->addImage("title115", "resource/title_Resource/title (115).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[115] = IMAGEMANAGER->addImage("title116", "resource/title_Resource/title (116).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[116] = IMAGEMANAGER->addImage("title117", "resource/title_Resource/title (117).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[117] = IMAGEMANAGER->addImage("title118", "resource/title_Resource/title (118).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[118] = IMAGEMANAGER->addImage("title119", "resource/title_Resource/title (119).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[119] = IMAGEMANAGER->addImage("title120", "resource/title_Resource/title (120).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[120] = IMAGEMANAGER->addImage("title121", "resource/title_Resource/title (121).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[121] = IMAGEMANAGER->addImage("title122", "resource/title_Resource/title (122).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[122] = IMAGEMANAGER->addImage("title123", "resource/title_Resource/title (123).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[123] = IMAGEMANAGER->addImage("title124", "resource/title_Resource/title (124).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[124] = IMAGEMANAGER->addImage("title125", "resource/title_Resource/title (125).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[125] = IMAGEMANAGER->addImage("title126", "resource/title_Resource/title (126).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[126] = IMAGEMANAGER->addImage("title127", "resource/title_Resource/title (127).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[127] = IMAGEMANAGER->addImage("title128", "resource/title_Resource/title (128).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[128] = IMAGEMANAGER->addImage("title129", "resource/title_Resource/title (129).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[129] = IMAGEMANAGER->addImage("title130", "resource/title_Resource/title (130).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[130] = IMAGEMANAGER->addImage("title131", "resource/title_Resource/title (131).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[131] = IMAGEMANAGER->addImage("title132", "resource/title_Resource/title (132).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[132] = IMAGEMANAGER->addImage("title133", "resource/title_Resource/title (133).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[133] = IMAGEMANAGER->addImage("title134", "resource/title_Resource/title (134).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[134] = IMAGEMANAGER->addImage("title135", "resource/title_Resource/title (135).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[135] = IMAGEMANAGER->addImage("title136", "resource/title_Resource/title (136).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[136] = IMAGEMANAGER->addImage("title137", "resource/title_Resource/title (137).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[137] = IMAGEMANAGER->addImage("title138", "resource/title_Resource/title (138).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[138] = IMAGEMANAGER->addImage("title139", "resource/title_Resource/title (139).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[139] = IMAGEMANAGER->addImage("title140", "resource/title_Resource/title (140).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[140] = IMAGEMANAGER->addImage("title141", "resource/title_Resource/title (141).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[141] = IMAGEMANAGER->addImage("title142", "resource/title_Resource/title (142).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[142] = IMAGEMANAGER->addImage("title143", "resource/title_Resource/title (143).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[143] = IMAGEMANAGER->addImage("title144", "resource/title_Resource/title (144).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[144] = IMAGEMANAGER->addImage("title145", "resource/title_Resource/title (145).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[145] = IMAGEMANAGER->addImage("title146", "resource/title_Resource/title (146).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[146] = IMAGEMANAGER->addImage("title147", "resource/title_Resource/title (147).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[147] = IMAGEMANAGER->addImage("title148", "resource/title_Resource/title (148).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[148] = IMAGEMANAGER->addImage("title149", "resource/title_Resource/title (149).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[149] = IMAGEMANAGER->addImage("title150", "resource/title_Resource/title (150).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[150] = IMAGEMANAGER->addImage("title151", "resource/title_Resource/title (151).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[151] = IMAGEMANAGER->addImage("title152", "resource/title_Resource/title (152).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[152] = IMAGEMANAGER->addImage("title153", "resource/title_Resource/title (153).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[153] = IMAGEMANAGER->addImage("title154", "resource/title_Resource/title (154).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[154] = IMAGEMANAGER->addImage("title155", "resource/title_Resource/title (155).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[155] = IMAGEMANAGER->addImage("title156", "resource/title_Resource/title (156).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[156] = IMAGEMANAGER->addImage("title157", "resource/title_Resource/title (157).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[157] = IMAGEMANAGER->addImage("title158", "resource/title_Resource/title (158).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[158] = IMAGEMANAGER->addImage("title159", "resource/title_Resource/title (159).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[159] = IMAGEMANAGER->addImage("title160", "resource/title_Resource/title (160).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[160] = IMAGEMANAGER->addImage("title161", "resource/title_Resource/title (161).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[161] = IMAGEMANAGER->addImage("title162", "resource/title_Resource/title (162).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[162] = IMAGEMANAGER->addImage("title163", "resource/title_Resource/title (163).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[163] = IMAGEMANAGER->addImage("title164", "resource/title_Resource/title (164).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[164] = IMAGEMANAGER->addImage("title165", "resource/title_Resource/title (165).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[165] = IMAGEMANAGER->addImage("title166", "resource/title_Resource/title (166).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[166] = IMAGEMANAGER->addImage("title167", "resource/title_Resource/title (167).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[167] = IMAGEMANAGER->addImage("title168", "resource/title_Resource/title (168).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[168] = IMAGEMANAGER->addImage("title169", "resource/title_Resource/title (169).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[169] = IMAGEMANAGER->addImage("title170", "resource/title_Resource/title (170).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[170] = IMAGEMANAGER->addImage("title171", "resource/title_Resource/title (171).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[171] = IMAGEMANAGER->addImage("title172", "resource/title_Resource/title (172).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[172] = IMAGEMANAGER->addImage("title173", "resource/title_Resource/title (173).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[173] = IMAGEMANAGER->addImage("title174", "resource/title_Resource/title (174).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[174] = IMAGEMANAGER->addImage("title175", "resource/title_Resource/title (175).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[175] = IMAGEMANAGER->addImage("title176", "resource/title_Resource/title (176).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[176] = IMAGEMANAGER->addImage("title177", "resource/title_Resource/title (177).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[177] = IMAGEMANAGER->addImage("title178", "resource/title_Resource/title (178).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[178] = IMAGEMANAGER->addImage("title179", "resource/title_Resource/title (179).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[179] = IMAGEMANAGER->addImage("title180", "resource/title_Resource/title (180).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[180] = IMAGEMANAGER->addImage("title181", "resource/title_Resource/title (181).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[181] = IMAGEMANAGER->addImage("title182", "resource/title_Resource/title (182).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[182] = IMAGEMANAGER->addImage("title183", "resource/title_Resource/title (183).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[183] = IMAGEMANAGER->addImage("title184", "resource/title_Resource/title (184).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[184] = IMAGEMANAGER->addImage("title185", "resource/title_Resource/title (185).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[185] = IMAGEMANAGER->addImage("title186", "resource/title_Resource/title (186).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[186] = IMAGEMANAGER->addImage("title187", "resource/title_Resource/title (187).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[187] = IMAGEMANAGER->addImage("title188", "resource/title_Resource/title (188).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[188] = IMAGEMANAGER->addImage("title189", "resource/title_Resource/title (189).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[189] = IMAGEMANAGER->addImage("title190", "resource/title_Resource/title (190).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[190] = IMAGEMANAGER->addImage("title191", "resource/title_Resource/title (191).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[191] = IMAGEMANAGER->addImage("title192", "resource/title_Resource/title (192).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[192] = IMAGEMANAGER->addImage("title193", "resource/title_Resource/title (193).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[193] = IMAGEMANAGER->addImage("title194", "resource/title_Resource/title (194).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[194] = IMAGEMANAGER->addImage("title195", "resource/title_Resource/title (195).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[195] = IMAGEMANAGER->addImage("title196", "resource/title_Resource/title (196).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[196] = IMAGEMANAGER->addImage("title197", "resource/title_Resource/title (197).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[197] = IMAGEMANAGER->addImage("title198", "resource/title_Resource/title (198).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[198] = IMAGEMANAGER->addImage("title199", "resource/title_Resource/title (199).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[199] = IMAGEMANAGER->addImage("title200", "resource/title_Resource/title (200).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		_title[200] = IMAGEMANAGER->addImage("title201", "resource/title_Resource/title (201).bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}
	*/

	_cover = IMAGEMANAGER->addImage("커버", "resource/title_Resource/cover.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_currentGauge = 0;
	_count = 0;

	return S_OK;
}

void loadingFrame::release(void)
{

}

void loadingFrame::update(void)
{
	_count += 0.10f;

	if (_count >= 201.f)
	{
		_count = 1.f;
	}

}

void loadingFrame::render(void)
{
	//_title[(int)_count]->render(getMemDC());
	//_loadingFrameScene->render(getMemDC());
	_cover->render(getMemDC());
}

void loadingFrame::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loadingFrame::loadImage(string keyName, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loadingFrame::loadImage(string keyName, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loadingFrame::loadFrameImage(string keyName, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loadingFrame::loadFrameImage(string keyName, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loadingFrame::loadSound(string keyName, const char * fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);
	_vLoadItem.push_back(item);
}

BOOL loadingFrame::loadingDone()
{
	//로딩이 완료됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;
	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	}
	break;
	case LOAD_KIND_IMAGE_2:
	{	tagImageResource img = item->getImageResource();
	IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
	}
	break;
	case LOAD_KIND_FRAMEIMAGE_0:
	{	tagImageResource img = item->getImageResource();
	IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;
	case LOAD_KIND_FRAMEIMAGE_1:
	{	tagImageResource img = item->getImageResource();
	IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;
	//곧 사운드 배우고 난후 알아서...
	case LOAD_KIND_SOUND:
	{
		tagSoundResource soundResource = item->getSoundResource();
		SOUNDMANAGER->addSound(soundResource.keyName, soundResource.fileName, soundResource.bgm, soundResource.loop);
	}
	break;
	}

	//현재게이지 증가
	_currentGauge++;

	//로딩바 이미지 변경
	//_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	return 0;
}
