#ifndef __LEVEL_CHOOSE_SCENE_H__
#define __LEVEL_CHOOSE_SCENE_H__

#include "cocos2d.h"
#include"../gamePlayingScene/GamePlayingScene.h"
#include"../../public/Constant/Constant.h"
#include "../../public/Item/itemInformation.h"
USING_NS_CC;

class LevelChooseScene :public cocos2d::Scene{
public:
	CREATE_FUNC(LevelChooseScene);

	virtual bool init();

	void OpenShop(Ref* sender);

	void ExitShop(Ref* sender);

	void buySomething(Ref* sender);

	void Level1ChosenMenuItemCallback(Ref* sender);
	void Level2ChosenMenuItemCallback(Ref* sender);
	void Level3ChosenMenuItemCallback(Ref* sender);
	void Level4ChosenMenuItemCallback(Ref* sender);
	void Level5ChosenMenuItemCallback(Ref* sender);

	void ShopCallback(Ref* sender);

	void update(float delta);

	void buyHp(Ref* sender);

	void buyBp(Ref* sender);

	void buyarrow(Ref* sender);

	void saleHp(Ref* sender);

	void saleBp(Ref* sender);

	void saleArrow(Ref* sender);

private:
	Node * shop;
	ui::Text* hpNumText;
	ui::Text* bpNumText;
	ui::Text* arrowNumText;
	ui::Text* moneyText;
	MenuItemImage* level1;
	MenuItemImage* level2;
	MenuItemImage* level3;
	MenuItemImage* level4;
	MenuItemImage* level5;
};

#endif
