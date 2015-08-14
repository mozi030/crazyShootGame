#ifndef __ENEMY1_H__
#define __ENEMY1_H__

#include"Enemy.h"

class Enemy1 : public Enemy{
public :
	virtual bool init();
	CREATE_FUNC(Enemy1);

	virtual void setLoc(float dt);
	virtual Sprite* createDispearSprite(Vec2);
	virtual int attack();
	virtual void attackCancel();
	void AttackArcher(float dt);

private:

};

#endif