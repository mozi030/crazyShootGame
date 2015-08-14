#ifndef __ARCHER_CONTROLLER_H__
#define __ARCHER_CONTROLLER_H__

#include "cocos2d.h"
USING_NS_CC;
#include"../../Model/archer/archer.h"
#include"../../../../public/Constant/Constant.h"
#include"../../../../public/ParameterManager/ParameterManager.h"
#include"../../Model/archer/arrow.h"
#include"../../Model/archer/progressTime.h"
#include"../cameraController/CameraController.h"
#include"../../Model/Enemy/Enemy.h"

class ArcherController : public cocos2d::Layer{
public:
	static ArcherController* getInstance();
	virtual bool init();
	CREATE_FUNC(ArcherController);

	archer* getArcher();
	progressTime* getProgressTime();

	static void touchBegan(Vec2);
	static void touchEnded(Vec2);
	void updateTimeForProgressBar(float dt);
	void updateTimeForAddExp(float dt);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*event);

	void landGround();
	void leaveGround();
	void attacked(Node* aNode, int);
	void setWeapon(int);
	void gameEndedAndRemove();

	void touchRope();
	void leaveRope();

	void createArrowRainTouch(Node* arrowRainNode);
private:
	ArcherController();
	~ArcherController();
	static ArcherController* archerController;

	static archer* archer_;
	static progressTime* progressTime_;

	static float totalTimeForProgressBar;

	static bool moveLeftAngRightLock;
	static bool moveUpAndDownLock;
	static bool onAir;
	static bool climbing;
};

#endif