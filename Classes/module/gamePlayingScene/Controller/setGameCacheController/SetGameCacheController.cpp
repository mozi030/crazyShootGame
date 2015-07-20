#include"SetGameCacheController.h"
#include"../../Model/Constant/Constant.h"
#include"cocos2d.h"
USING_NS_CC;

SetGameCacheController* SetGameCacheController::gameCacheController = NULL;

SetGameCacheController::SetGameCacheController(){}

SetGameCacheController* SetGameCacheController::getInstance() {
	if (gameCacheController == NULL) {
		gameCacheController = new SetGameCacheController();
	}
	return gameCacheController;
}

void SetGameCacheController::setGameCache(){
	auto texture = Director::getInstance()->getTextureCache()->addImage(Constant::getArcherPath());
	float width = texture->getPixelsWide();
	float height = texture->getPixelsHigh();
	SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::createWithTexture(texture, Rect(0, 0, width / 4, height)), Constant::getArcherFrameName());

	Animation* enemyAnimation = Animation::create();
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage(Constant::getEnemyPath());
	Size tempSize = texture2->getContentSize();
	for (int i = 0; i < 4; i++) {
		enemyAnimation->addSpriteFrame(SpriteFrame::createWithTexture(texture2, Rect(i * tempSize.width / 4, 0, tempSize.width / 4, tempSize.height)));
	}
	enemyAnimation->setDelayPerUnit(0.2);
	AnimationCache::getInstance()->addAnimation(enemyAnimation, Constant::getEnemyAnimationName());
	SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::createWithTexture(texture2, Rect(0, 0, tempSize.width / 4, tempSize.height)), Constant::getEnemyFrameName());
}

void SetGameCacheController::deleteInstance() {
	if (gameCacheController != NULL) {
		delete gameCacheController;
		gameCacheController = NULL;
	}
}