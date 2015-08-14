#ifndef __ENEMY4_H__
#define __ENEMY4_H__

#include"Enemy.h"

class Enemy4 : public Enemy{
public:
	virtual bool init();
	CREATE_FUNC(Enemy4);

	virtual void setLoc(float dt);
	virtual Sprite* createDispearSprite(Vec2);
	virtual int attack();
	virtual void attackCancel();
	void AttackEnemy(float dt);
private:

};

#endif