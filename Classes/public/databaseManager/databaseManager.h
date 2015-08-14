#ifndef __DATABASE_MANAGER_H__
#define __DATABASE_MANAGER_H__

using namespace std;
#include"string"
#include"cocos2d.h"
USING_NS_CC;

#define database UserDefault::getInstance()
#define storeIntToXML UserDefault::getInstance()->setIntegerForKey
#define getIntFromXML UserDefault::getInstance()->getIntegerForKey

struct dataTemplete {
	int recordNum;//第几个记录
	int highestGameLevel;//最高到第几关
	int totalScore;//总得分

	//items:
	int bloodBottleNum;//血瓶数
	int blueBottleNum;//蓝瓶数
	int weapon1Num;//武器1的数量
	int weapon2Num;//武器2的数量
	int coinNum;//金币数

	int currentArcherLevel;//射手的等级
	int exp;

	string date;
};

class databaseManager {
public:
	static dataTemplete databaseSelete(int recordNum);
	static void databaseSave(dataTemplete);
	
};

#endif