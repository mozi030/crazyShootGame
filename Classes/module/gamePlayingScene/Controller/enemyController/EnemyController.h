#include "cocos2d.h"

class EnemyController :public cocos2d::Layer {
public:
	static EnemyController*getInstance();
	virtual bool init();
	CREATE_FUNC(EnemyController);

	void EnemyAttacked(cocos2d::Node*);
	void Attack(cocos2d::Node* enemyNode, cocos2d::Node*);
	void AttackCancel(cocos2d::Node* enemyNode, cocos2d::Node*);
	void Turn(cocos2d::Node*);
	void UpdateControl(float dt, cocos2d::Node*, cocos2d::Node*);
private:
	EnemyController();
	~EnemyController();
	static EnemyController*enemyController;
};