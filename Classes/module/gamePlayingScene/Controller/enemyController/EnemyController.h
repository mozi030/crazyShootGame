#include "cocos2d.h"

class EnemyController :public cocos2d::Sprite {
public:
	static EnemyController* createAnEnemy();
private:
	EnemyController();
};