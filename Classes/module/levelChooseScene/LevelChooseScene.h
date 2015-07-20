#include "cocos2d.h"
USING_NS_CC;

class LevelChooseScene :public cocos2d::Scene{
public:
	CREATE_FUNC(LevelChooseScene);

	virtual bool init();

	void LevelChosenMenuItemCallback(Ref* sender);
};