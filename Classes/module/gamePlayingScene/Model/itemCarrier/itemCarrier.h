#ifndef __ITEM_CARRIER_H__
#define __ITEM_CARRIER_H__

#include"cocos2d.h"
#include"../../../../public/parameterManager/parameterManager.h"
#include"../../../../public/Constant/Constant.h"
USING_NS_CC;

class itemCarrier{
public:
	Sprite* itermBall(int);
	Sprite* getItermBall();
	void drop();
private:
	Sprite* ItermBall;
};
#endif