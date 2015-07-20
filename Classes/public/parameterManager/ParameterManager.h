#include"cocos2d.h"
USING_NS_CC;

class ParameterManager {
public:
	/*
	获取弓箭最大初速度
	*/
	static float getArrowMaxVelocity();

	/*
	获取敌人移动的最长时间
	*/
	static float getEnemyMovingTime();

	/*
	获取物理世界的重力
	*/
	static Vec2 getGravity();

	/*
	获取屏幕大小
	*/
	static Size getVisibleSize();
private:
	static ParameterManager* parameterManager;

	static float arrowMaxVelocity;
	static float enemyMovingTime;
	static Vec2 gravity;

	static Size visibleSize;
};