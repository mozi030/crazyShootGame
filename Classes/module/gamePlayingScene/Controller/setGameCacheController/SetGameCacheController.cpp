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

}

