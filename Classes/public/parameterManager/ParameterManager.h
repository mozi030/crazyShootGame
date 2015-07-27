#include"cocos2d.h"
USING_NS_CC;

struct ArcherParameter{
	cocos2d::Vec2 initialPosition;
	ArcherParameter();
	ArcherParameter(cocos2d::Vec2 _initialPosition);
	/*ArcherParameter operator = (ArcherParameter _archerParameter){
	this->initialPosition = _archerParameter.initialPosition;
	return *this;
	}*/
};

struct EnemyParameter {
	cocos2d::Vec2 initialPosition;
	int mode;
	int blood;
	EnemyParameter();
	EnemyParameter(cocos2d::Vec2 _initialPosition, int _blood, int _mode);
	/*EnemyParameter operator = (EnemyParameter _enemyParameter) {
	this->initialPosition = _enemyParameter.initialPosition;
	this->blood = _enemyParameter.blood;
	this->mode = _enemyParameter.mode;
	return *this;
	}*/
};

struct GameParameterForLevels{
	int levelNum;
	ArcherParameter* archerParameter;
	std::vector<EnemyParameter*> enemyParameter;
	GameParameterForLevels(int _levelNum, ArcherParameter* _archerParameter, std::vector<EnemyParameter*> _enemyParameter);
};

class ParameterManager {
public:

	//获取弓箭最大初速度
	static float getArrow1MaxVelocity();

	//获取敌人移动的最长时间
	//static float getEnemyMovingTime();

	//获取物理世界的重力
	static Vec2 getGravity();

	//获取屏幕大小
	static Size getVisibleSize();

	//获取每一关配置
	static GameParameterForLevels* getLevelInstance(int levelNum);

	static void deleteAll();

	static int getCurrentLevel();
	static void setCurrentLevel(int);
	static int getUnlockedLevel();
	static void setUnlockedLevel(int);
private:
	//全局参数
	static Vec2 gravity;//重力
	static Size visibleSize;//可视范围的尺寸
	static int unlockedLevel;//已经解锁到第几关
	static int currentLevel;//现在在玩第几关

	//弓箭
	static float arrow1MaxVelocity;//第一种弓箭的最大速度

	//敌人
	//static float enemyMovingTime;

	static GameParameterForLevels* level1GameParameter;


};