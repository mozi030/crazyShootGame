#include"SetGameCacheController.h"
#include"../../../../public/Constant/Constant.h"
#include"cocos2d.h"
USING_NS_CC;

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

}

