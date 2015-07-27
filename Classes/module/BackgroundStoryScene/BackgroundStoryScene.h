#include "cocos2d.h"
USING_NS_CC;

class BackgroundStoryScene :public cocos2d::Scene{
public:
	static BackgroundStoryScene* createScene();
	CREATE_FUNC(BackgroundStoryScene);
	virtual bool init();

	void SkipMenuItemCallback(Ref* sender);
};