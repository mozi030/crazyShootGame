#ifndef __ENEMY_CONTROLLER_H__
#define __ENEMY_CONTROLLER_H__

#include "cocos2d.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../Model/archer/archer.h"
#include "../../Model/Enemy/Enemy.h"
#include "../../Model/Enemy/Enemy1.h"
#include "../../Model/Enemy/Enemy2.h"
#include "../../Model/Enemy/Enemy3.h"
#include "../../Model/Enemy/Enemy4.h"
#include "../../Model/Enemy/Enemy5.h"
#include "../../Model/archer/arrow.h"

class EnemyController :public cocos2d::Layer {
public:
	static EnemyController*getInstance();
	virtual bool init();
	CREATE_FUNC(EnemyController);

	void EnemyAttacked(cocos2d::Node*, cocos2d::Node*);
	void Attack(cocos2d::Node* enemyNode, cocos2d::Node*);
	void AttackCancel(cocos2d::Node* enemyNode, cocos2d::Node*);
	void Turn(cocos2d::Node*);
	void UpdateControl(float dt, cocos2d::Node*, cocos2d::Node*);
	void AddAenemy();

	int totalEnemyNum;

	void gameEndedAndRemove();
private:
	EnemyController();
	~EnemyController();
	static EnemyController*enemyController;

	Vector<Enemy*>allEnemy;
};
#endif