
#ifndef __ITEM_H__
#define __ITEM_H__ 
#include <string>
#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class item{ 
public:
	static void buyHp();
	static void buyBp();
	static void buyArrow();
	static void saleHp();
	static void saleBp();
	static void saleArrow();

	static string getHpNum();
	static string getBpNum();
	static string getArrowNum();
	static string getMoneyNum();

	static void useHp();
	static void useMp();
	static void useArrow();

	static int getHp();
	static void setHpNum(int);
	static int getBp();
	static void setBpNum(int);
	static int getArrow();
	static void setArrowNum(int);
	static void setMoney(int);
	static void addMoney(int);
	static int getMoney();

	static void setTotalScore(int);
	static void addTotalScore(int);
	static int getTotalScore();

	static void setHighestGameLevel(int);
	static int getHighestGameLevel();
	static void setCurrentArcherLevel(int);
	static int getCurrentArcherLevel();
	static void addCurrentArcherLevel();

	static int getExp();
	static void setExp(int);
private:
	static int hpNum;
	static int bpNum;
	static int arrowNum;
	static int money;

	static int totalScore;//
	static int highestGameLevel;//
	static int currentArcherLevel;//

	static int exp;
};
#endif