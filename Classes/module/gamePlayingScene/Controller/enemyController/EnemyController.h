#include "cocos2d.h"

class EnemyController :public cocos2d::Layer {
public:
	static EnemyController*getInstance();
	virtual bool init();
	CREATE_FUNC(EnemyController);

	void EnemyAttacked(cocos2d::Node*, cocos2d::Vec2);
private:
	EnemyController();
	~EnemyController();
	static EnemyController*enemyController;
};