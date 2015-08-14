#ifndef __CAMERA_CONTROLLER__
#define __CAMERA_CONTROLLER__

#include"cocos2d.h"
#include"../../../../public/parameterManager/parameterManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"../ArcherController/ArcherController.h"
#include"../GameoverController/GameoverController.h"
USING_NS_CC;

class CameraController : public cocos2d::Layer {
public:
	static CameraController* getInstance();
	CREATE_FUNC(CameraController);
	virtual bool init();
	void updateCamera(bool);
	Camera* getCamera();
	void lookAtInitial();
private:
	static CameraController*cameraController;
	CameraController();
	~CameraController();
	Camera*camera;
};

#endif