#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "../archer/archer.h"
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"

USING_NS_CC;

#define pi 3.141592654

class Enemy :public cocos2d::Node{
public:
	void onEnter();
	void onExit();
	/*
	默认在图的右上角生成有一个模式为2的敌人
	*/
	//CREATE_FUNC(Enemy);
	//virtual bool init();

	/*
	在（_locX, _locY）处，生成一个血量被_blood，模式为_mode的敌人
	*/
	void setParameter(Vec2 initialLocation, int _blood);

	void createProgressTimer();
	ProgressTimer* getProgressTimer();
	Sprite* getEnemySprite();
	/*
	创建一个哥布林：攻击力为5。（死亡条件：一支普通箭即可击杀）
	*/
	//void createEnemyOne();

	/*
	创建一个战士战士：近战攻击，攻击力为10。（死亡条件：两箭才能击杀）
	*/
	//void createEnemyTwo();

	/*
	弓箭手：不会移动，但会远程攻击，攻击力为10。（死亡条件：两箭才能击杀）
	*/
	//void createEnemyArrow();

	/*
	魔法师：远程攻击，每3秒瞬时移动一个其他位置，是最难击杀的一个，
	攻击力为15。（死亡条件：三箭才能击杀）
	*/
	//void createEnemyMagic(Enemy* _enemy);

	void setBlood(int _blood);

	int getPower();
	int getBlood();
	int getMode();
	int getShadowNumber();

	virtual void setLoc(float dt) = 0;
	virtual int attack() = 0;
	virtual void attackCancel() = 0;
	virtual Sprite* createDispearSprite(Vec2) = 0;

protected:
	//初始的X坐标
	//float locX;

	//初始的Y坐标
	//float locY;

	//	血量
	int blood;

	/*敌人模式
	mode 0   Undefined
	mode 1   Move enemy
	mode 2   Arrow enemy
	*/
	int mode;
	int power;

	//方向,false为左，true为右
	bool direction;

	bool attackShadowExist;
	char trueNumber[20];
	int shadowNumber;
	Sprite* enemySprite;
	Sprite* attackSprite;
	Action* currentAttackAction;

	ProgressTimer* progressTimer;
};

#endif