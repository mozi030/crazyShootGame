#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	void ClickStart(Ref* sender);
	void ClickDescription(Ref* sender);
	void ClickLoadGame(Ref* sender);
	void ClickTopRank(Ref* sender);
	void ClickControl(Ref* sender);
};

#endif // __HELLOWORLD_SCENE_H__
