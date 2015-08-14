#ifndef __WEATHER_CONTROLLER_H__
#define __WEATHER_CONTROLLER_H__

#include "cocos2d.h"
USING_NS_CC;

#include"../../../../public/Constant/Constant.h"
#include"../../../../public/ParameterManager/ParameterManager.h"
#include"../../Model/archer/arrow.h"
#include"../../Model/archer/progressTime.h"
#include"../cameraController/CameraController.h"


class weatherController : public cocos2d::Layer{
public:
	static weatherController* getInstance();
	virtual bool init();
	CREATE_FUNC(weatherController);
	void flashAction(float dt);
	Sprite *cloud;
	Sprite *flash;
	
private:
	weatherController();
	~weatherController();
	static weatherController* weather;
};

#endif