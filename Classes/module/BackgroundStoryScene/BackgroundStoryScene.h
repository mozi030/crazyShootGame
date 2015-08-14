#ifndef __BACKGROUND_STORY_SCENE_H__
#define __BACKGROUND_STORY_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
#include"../levelChooseScene/LevelChooseScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "../../public/Constant/Constant.h"

class BackgroundStoryScene :public cocos2d::Scene{
public:
	static BackgroundStoryScene* createScene();
	CREATE_FUNC(BackgroundStoryScene);
	virtual bool init();

	void SkipMenuItemCallback(Ref* sender);
};

#endif