#ifndef __SET_GAME_CACHE_CONTROLLER_H__
#define __SET_GAME_CACHE_CONTROLLER_H__

#include"../../../../public/Constant/Constant.h"
#include"cocos2d.h"
USING_NS_CC; 
class SetGameCacheController{
public:
	static SetGameCacheController* getInstance();
	void setGameCache();

	static void deleteInstance();

private:
	SetGameCacheController();
	~SetGameCacheController();
	static SetGameCacheController* gameCacheController;
};

#endif