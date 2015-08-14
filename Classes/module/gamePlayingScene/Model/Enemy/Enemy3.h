#ifndef __ENEMY3_H__
#define __ENEMY3_H__

#include"Enemy.h"

class Enemy3 : public Enemy{
public:
	virtual bool init();
	CREATE_FUNC(Enemy3);

	virtual void setLoc(float dt);
	virtual Sprite* createDispearSprite(Vec2);
	virtual int attack();
	virtual void attackCancel();
	void AttackEnemy(float dt);

private:

	void updateTimeToArrowAttack(float dt);
	void updateTimeToChangeArrowAngle(float dt, void* data, std::string name);
};

#endif