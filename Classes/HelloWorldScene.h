#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "module\BackgroundStoryScene\BackgroundStoryScene.h"
#include "public/parameterManager/ParameterManager.h"
#include "public\databaseManager\databaseManager.h"
#include "public\Item\itemInformation.h"

USING_NS_CC;
using namespace std;
#include"string"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	void ClickStart(Ref* sender);
	void ClickDescription(Ref* sender);
	void ClickLoadGame(Ref* sender);
	void ClickTeam(Ref* sender);
	void ClickClose(Ref* sender);
	void menuCloseCallback(Ref* sender);

	void LoadCallback1(Ref* sender);
	void LoadCallback2(Ref* sender);
	void LoadCallback3(Ref* sender);
	void LoadCallback4(Ref* sender);
	void LoadCallback5(Ref* sender);
	void LoadCallback6(Ref* sender);

private:
	MenuItemImage* startItem;
	MenuItemImage* descriptionItem;
	MenuItemImage* loadGameItem;
	MenuItemImage* teamItem;
	MenuItemImage* closeItem;

	Menu* recordMenu;

	dataTemplete dataTemplete1;
	dataTemplete dataTemplete2;
	dataTemplete dataTemplete3;
	dataTemplete dataTemplete4;
	dataTemplete dataTemplete5;
	dataTemplete dataTemplete6;

};

#endif // __HELLOWORLD_SCENE_H__
