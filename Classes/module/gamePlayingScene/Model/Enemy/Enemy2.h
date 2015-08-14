#ifndef __ENEMY2_H__
#define __ENEMY2_H__

#include"Enemy.h"

class Enemy2 : public Enemy{
public:
	virtual bool init();
	CREATE_FUNC(Enemy2);

	void UpdateTimeToAttack(float);
	void Boob();
	virtual void setLoc(float dt);
	virtual Sprite* createDispearSprite(Vec2);
	virtual int attack();
	virtual void attackCancel();

private:
};

#endif