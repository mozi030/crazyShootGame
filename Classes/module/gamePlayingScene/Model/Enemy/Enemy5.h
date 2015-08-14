#ifndef __ENEMY5_H__
#define __ENEMY5_H__

#include"Enemy.h"

class Enemy5 : public Enemy{
public:
	virtual bool init();
	CREATE_FUNC(Enemy5);

	virtual void setLoc(float dt);
	virtual Sprite* createDispearSprite(Vec2);
	//virtual int attack();
	//virtual void attackCancel();

	bool getUseOfAddBlood();
	bool getUseOfCall();
	bool getUseOfAttack();
	void setgetUseOfAddBlood(bool _set);
	void setUseOfCall(bool _set);
	void setUseOfAttack(bool _set);
	void useAbility(float dt, Action*, ActionInterval*);
	void attackNormal();
	void attackCall();
	void attackAddBlood();
	void addEnemy();
	void DelayAttack(float dt, Vec2 _enemyLoc1, Sprite* Attack);

	virtual int attack();
	virtual void attackCancel();
	void AttackEnemy(float dt);

private:
	bool UseOfAddBlood;
	bool UseOfCall;
	Vec2 enemyLoc1;
	Vec2 enemyLoc2;
	bool UseOfAttack;
	Vector <Enemy*> smallEnemy;
	/*
	0 - ²»¹¥»÷
	5 - ÆÕÍ¨¹¥»÷
	7- ÆÕÍ¨¹¥»÷£¬ ÕÙ»½Ð¡¹Ö
	10 - ÆÕÍ¨¹¥»÷£¬ ÕÙ»½Ð¡¹Ö£¬ Ð¡¹Ö¼ÓÑª
	*/
	float AttackMode;
};

#endif