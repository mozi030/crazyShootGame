#ifndef __ARROW_H__
#define __ARROW_H__

#include"cocos2d.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"
#include "../../../../public/Item/itemInformation.h"

class arrow :public cocos2d::Sprite {
public:
	static arrow* createAnArrow(Vec2 beginPoint, Vec2 endedPoint, float percent, int arrowType);
	//arrow rain
	static arrow* createArrowRain(Vec2 beginPoint, Vec2 endedPoint, float percent);
	static arrow* createArrowRainTouch(float, Vec2);

	void updateTimeToChangeArrowAngle(float dt, void* data,std::string );
	int getPower();
private:
	arrow();
	int power;
};

#endif