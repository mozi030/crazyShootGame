#include"SetGameCacheController.h"

SetGameCacheController* SetGameCacheController::gameCacheController = NULL;

SetGameCacheController::SetGameCacheController(){}

SetGameCacheController::~SetGameCacheController() {
	if (gameCacheController != NULL) {
		delete gameCacheController;
		gameCacheController = NULL;
	}
}

SetGameCacheController* SetGameCacheController::getInstance() {
	if (gameCacheController == NULL) {
		gameCacheController = new SetGameCacheController();
	}
	return gameCacheController;
}

void SetGameCacheController::setGameCache(){
	AnimationCache* animationCache = AnimationCache::getInstance();
	SpriteFrameCache * cache = SpriteFrameCache::getInstance();

	cache->addSpriteFramesWithFile(Constant::getEnemyGoblinPath());
	cache->addSpriteFramesWithFile(Constant::getEnemySoldierPath());
	cache->addSpriteFramesWithFile(Constant::getEnemyArrowEnemyPath());
	cache->addSpriteFramesWithFile(Constant::getEnemySheepPath());
	cache->addSpriteFramesWithFile(Constant::getEnemyBossAttackPath());
	cache->addSpriteFramesWithFile(Constant::getEnemyBossPath());
	//Goblin Move
	Vector <SpriteFrame*> temp;
	char name[20];
	memset(name, 0, sizeof(name));
	for (int i = 0; i < 5; i++){
		sprintf(name, "Goblin_%d.png", i + 1);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}

	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.1f), Constant::getEnemyGoblinMove());

	//Sheep Move
	temp.clear();
	memset(name, 0, sizeof(name));
	for (int i = 4; i < 8; i++){
		sprintf(name, "Sheep_%d.png", i);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}

	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.1f), Constant::getEnemySheepMove());

	//Soldier Move
	temp.clear();
	memset(name, 0, sizeof(name));
	for (int i = 0; i < 8; i++){
		sprintf(name, "Soldier_%d.png", i + 1);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.1f), Constant::getEnemySoldierMove());

	//ArrowEnemy Attack
	temp.clear();
	for (int i = 9; i < 16; i++){
		sprintf(name, "ArrowEnemy_%d.png", i + 1);
		SpriteFrame* sf = cache->spriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.2f), Constant::getEnemyArrowEnemyAttack());

	//Goblin Death
	temp.clear();
	for (int i = 10; i < 14; i++){
		sprintf(name, "Goblin_%d.png", i + 1);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.5f), Constant::getEnemyGoblinDeath());

	//Sheep Death
	temp.clear();
	for (int i = 13; i < 22; i++){
		sprintf(name, "Sheep_%d.png", i);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.5f), Constant::getEnemySheepDeath());


	//Soldier Death
	temp.clear();
	for (int i = 17; i < 23; i++){
		sprintf(name, "Soldier_%d.png", i + 1);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.5f), Constant::getEnemySoldierDeath());

	//ArrowEnemy Death
	temp.clear();
	for (int i = 17; i < 21; i++){
		sprintf(name, "ArrowEnemy_%d.png", i + 1);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.5f), Constant::getEnemyArrowEnemyDeath());

	//Boss Normal
	temp.clear();
	for (int i = 17; i < 23; i++){
		sprintf(name, "Boss_%d.png", i);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.2f), Constant::getEnemyBossNormal());


	//Boss Attack
	temp.clear();
	for (int i = 1; i < 17; i++){
		sprintf(name, "Boss_%d.png", i);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.1f), Constant::getEnemyBossAttack());

	//Boss Call

	temp.clear();
	for (int i = 23; i < 58; i++){
		sprintf(name, "Boss_%d.png", i);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.1f), Constant::getEnemyBossCall());

	//BossAttack Real
	temp.clear();
	for (int i = 1; i < 20; i++){
		sprintf(name, "BossAttack_%d.png", i);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.1f), Constant::getEnemyBossAttackReal());

	//BossAttack Call
	temp.clear();
	for (int i = 32; i < 37; i++){
		sprintf(name, "BossAttack_%d.png", i);
		SpriteFrame* sf = cache->getSpriteFrameByName(name);
		temp.pushBack(sf);
	}
	animationCache->addAnimation(Animation::createWithSpriteFrames(temp, 0.1f), Constant::getEnemyBossAttackCall());

	
}

