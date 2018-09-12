#pragma once
#include "singletonBase.h"
class cameraManager :public singletonBase<cameraManager>
{
	RECT _rcCamera;
	RECT _rcTemp;
public:

	RECT getCamera() { return _rcCamera; }
	void setCamera(RECT rc) { _rcCamera = rc; }

	RECT CameraPosSetting(RECT rc);
	bool CameraIn(RECT rc);

	HRESULT init();
	void update();
	//카메라매니져 해제
	void release();


	cameraManager() {}
	~cameraManager() {}
};

