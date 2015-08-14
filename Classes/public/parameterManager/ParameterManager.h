#ifndef __PARAMETER_MANAGER_H__
#define __PARAMETER_MANAGER_H__


#include"cocos2d.h"
USING_NS_CC;

struct ArcherParameter{
	cocos2d::Vec2 initialPosition;
	ArcherParameter();
	ArcherParameter(cocos2d::Vec2 _initialPosition);
};

struct EnemyParameter {
	cocos2d::Vec2 initialPosition;
	int mode;
	int blood;
	EnemyParameter();
	EnemyParameter(cocos2d::Vec2 _initialPosition, int _blood, int _mode);
};

struct EdgeParameter {
	cocos2d::Vec2 firstPoint;
	cocos2d::Vec2 secondPoint;
	int type;
	EdgeParameter();
	EdgeParameter(cocos2d::Vec2 _firstPoint, cocos2d::Vec2 _secondPoint, int _type);
};

struct GameParameterForLevels{
	int levelNum;
	Size mapSize;
	ArcherParameter* archerParameter;
	std::vector<EnemyParameter*> enemyParameter;
	std::vector<EdgeParameter*> edgeParameter;
	GameParameterForLevels(int _levelNum, Size _mapSize, ArcherParameter* _archerParameter, std::vector<EnemyParameter*> _enemyParameter, std::vector<EdgeParameter*> _edgeParameter);
};

struct LevelParameter  {
	int levelNum;
	int blood;
	int blue;
	int power;
	int levelUpExp;
};

class ParameterManager {
public:
	//全局参数
	//获取物理世界的重力
	static Vec2 getGravity();
	//获取屏幕大小
	static Size getVisibleSize();
	//获取每一关配置
	static GameParameterForLevels* getGameParameterInstance(int levelNum);
	//每一个等级的参数
	static LevelParameter* getLevelParameterInstance(int levelNum);
	//delete指针
	static void deleteAll();

	static int getCurrentGameLevel();
	static void setCurrentGameLevel(int);
	//static int getUnlockedLevel();
	//static void setUnlockedLevel(int);
	static int getArcherLevel();
	static void setArcherLevel(int);

	//地板
	static float getBottomGroundHeight();
	//弓箭
	//获取弓箭最大初速度
	static float getArrow1MaxVelocity();

	//敌人
	//获取敌人移动的最长时间
	//static float getEnemyMovingTime();

private:
	//全局参数
	static Vec2 gravity;//重力
	static Size visibleSize;//可视范围的尺寸
	static int currentGameLevel;//现在在玩第几关

	static GameParameterForLevels* level1GameParameter;
	static GameParameterForLevels* level2GameParameter;
	static GameParameterForLevels* level3GameParameter;
	static GameParameterForLevels* level4GameParameter;
	static GameParameterForLevels* level5GameParameter;

	static LevelParameter* level1Parameter;
	static LevelParameter* level2Parameter;
	static LevelParameter* level3Parameter;
	static LevelParameter* level4Parameter;
	static LevelParameter* level5Parameter;
	static LevelParameter* levelDefaultParameter;

	//地板
	static float bottomGroundHeight;
	//弓箭
	static float arrow1MaxVelocity;//第一种弓箭的最大速度

	//敌人
	//static float enemyMovingTime;

};

#endif