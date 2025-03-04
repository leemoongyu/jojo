#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다
	
	//앞으로 메인게임 클래스 안에서는 씬들만 관리한다
	//그리고 각각의 씬들이 메인게임 역할을 하면 된다

	/*씬추가*/
	//SCENEMANAGER->addScene("픽셀충돌", new pixelCollision);
	//SCENEMANAGER->addScene("테스트씬", new sceneTest);
	//SCENEMANAGER->addScene("ini", new iniTestScene);
	SCENEMANAGER->addScene("로딩화면", new loadingScene);
	//SCENEMANAGER->addScene("사운드", new soundTestScene);
	//SCENEMANAGER->addScene("애니메이션", new aniTestScene);
	//SCENEMANAGER->addScene("이펙트", new effectTestScene);
	//SCENEMANAGER->addScene("로테이트", new rotateTestScene);
	SCENEMANAGER->addScene("조조전맵툴", new tankGameScene);
	SCENEMANAGER->addScene("조조전로딩", new loadingScene);
	SCENEMANAGER->addScene("조조전전장", new jojoGameScene);

	/*현재씬 설정*/
	SCENEMANAGER->loadScene("조조전로딩");
	_img = IMAGEMANAGER->addImage("jojo_hand", "resource/jojo/jojo_hand.bmp", 50, 50, true, RGB(255, 0, 255));

	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	ShowCursor(false);
	//씬매니져 업데이트
	SCENEMANAGER->update();

	//사운드매니져 업데이트
	SOUNDMANAGER->update();

	//이펙트매니져 업데이트
	EFFECTMANAGER->update();
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	//씬매니져 렌더
	SCENEMANAGER->render();

	//이펙트매니져 렌더
	EFFECTMANAGER->render();

	//타임매니져 렌더
	TIMEMANAGER->render(getMemDC());

	IMAGEMANAGER->render("jojo_hand", getMemDC(), _ptMouse.x, _ptMouse.y);

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}
