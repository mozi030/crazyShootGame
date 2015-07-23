#include "cocos2d.h"

class EnemyController :public cocos2d::Sprite {
public:
	EnemyController();
	static EnemyController* createAnEnemy();
private:
	EnemyController* enemy;
	//Point block;	
};