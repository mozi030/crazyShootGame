#ifndef __ARCHER_H__
#define __ARCHER_H__

#include "cocos2d.h"
#include"../../../../public/Constant/Constant.h"
#include"../../../../public/ParameterManager/ParameterManager.h"
#include"../../../../public/Item/itemInformation.h"
USING_NS_CC;

class archer : public cocos2d::Sprite{
public:
	static archer* getInstance();
	CREATE_FUNC(archer);
	virtual bool init();
	void setParameter();

	void createModel();
	void createBloodBar();

	void aimAt(Vec2);

	//属性参数
	void setBlood(int value);
	void setInitialBlood(int value);
	int getBlood();
	int getInitialBlood();

	void setBlue(int value);
	void setInitialBlue(int value);
	int getBlue();
	int getInitialBLue();

	void setExp(int value);
	void setTotalExp(int value);
	int getExp();
	int getTotalExp();
	void addExp(int); 

	void setWeapon(int m);
	int getWeapon();

	void setScore(int);
	int getScore();
	void addScore(int);

	bool getDirection();

	void killEnemy(int mode);

	void jump();
	void running(bool direction,bool isClimbing);
	void stopping();
	void attacked(int);
	void death();
	void climb();
	void notClimb(bool isRunning);
	void climbUp();
	void climbDown();
	void stoppingClimbing();

private:
	archer();
	~archer();
	static archer* archer_;

	Sprite *head, *hand, *body;
	//跑步动画
	Sprite *runner;
	//死亡动画
	Sprite *deathSprite;
	//Sprite *hand1, *hand2, *hand3;
	//climb动画
	Sprite *climbSprite;
	Sprite *hpBgSprite;
	ProgressTimer *hpBar;
	Sprite *hpBar_back;
	Sprite *hpBar_fore;

	//血量
	int hpValue;
	int initialHpValue;
	//蓝量
	int blueValue;
	int initialBlueValue;
	//经验值
	int expValue;
	int totalExpValue;
	//弓箭种类1,2,3
	int weapon;
	//本关得分
	int score;

	//方向，面向左为false，右为true
	bool direction;
};

#endif