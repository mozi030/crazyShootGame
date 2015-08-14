#ifndef __GAMEOVER_CONTROLLER__
#define __GAMEOVER_CONTROLLER__

#include"cocos2d.h"
using namespace std;
#include"string"
#include"../../../../public/parameterManager/parameterManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"../../../levelChooseScene/LevelChooseScene.h"
#include"../cameraController/CameraController.h"
#include"../ArcherController/ArcherController.h"
#include"../enemyController/EnemyController.h"
#include"../../../../public/Item/itemInformation.h"
#include"../../../../public/databaseManager/databaseManager.h"
USING_NS_CC;
#include <time.h>

class GameoverController : public cocos2d::Layer {
public:
	static GameoverController* getInstance();
	CREATE_FUNC(GameoverController);
	virtual bool init();

	Menu* gameEndedMenu;
	Menu* gameoverMenu;

	void gameEnded(bool isWin);
private:
	static GameoverController*gameoverController;
	GameoverController();
	~GameoverController();

	void ClickGameEnded(Ref* sender);
	void guanka(Ref* sender);
	void again(Ref* sender);
	void next(Ref* sender);

	dataTemplete aDataTemplete;
};

#endif