#ifndef __ITEM_CONTROLLER_H__
#define __ITEM_CONTROLLER_H__

#include"cocos2d.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"
#include "../../../../public/Item/itemInformation.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../../Model/itemCarrier/itemCarrier.h"
#include "../../Model/archer/archer.h"

class ItemController :public cocos2d::Layer{
public:
	static ItemController* getInstance();
	CREATE_FUNC(ItemController);
	virtual bool init();

	void update(float delta);

	Sprite* AddBall();
	Sprite* Drop(Sprite*);

	void useHP(Ref* sender);
	void useMp(Ref* sender);
	void useArrow(Ref* sender);
private:
	ItemController();
	~ItemController();
	static ItemController* itemController;

	ui::Button* HP_button;
	ui::Button* MP_button;
	ui::Button* ARROW_button;

	ui::LoadingBar* HP_percent;
	ui::LoadingBar* MP_percent;
	ui::LoadingBar* EXP_percent;

	ui::Text* level_text;

	Label* arrowLabel;
};

#endif