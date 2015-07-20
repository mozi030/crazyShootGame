#include "cocos2d.h"
USING_NS_CC;

class StartScene :public cocos2d::Scene{
public:
	static StartScene* createScene();
	CREATE_FUNC(StartScene);
	~StartScene();
	virtual bool init();

	void SkipMenuItemCallback(Ref* sender);
};