#ifndef __GAME_PLAYING_SCENE_H__
#define __GAME_PLAYING_SCENE_H__

#include "cocos2d.h"
#include"Controller/archerController/archerController.h"
#include"Controller\edgeController\EdgeController.h"
#include"Controller\enemyController\EnemyController.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"../../public/parameterManager/ParameterManager.h"
#include"../../public/Constant/Constant.h"
#include"Controller/setGameCacheController/SetGameCacheController.h"
#include"Controller\GameoverController\GameoverController.h"
#include"Controller\cameraController\CameraController.h"
#include "Controller\ItemController\ItemController.h"
#include"Controller\weatherController\weatherController.h"
USING_NS_CC;

class GamePlayingScene :public cocos2d::Scene{
public:
	//CREATE_WITH_PHYSICS_FUNC(GamePlayingScene);
	void initial();
	static GamePlayingScene* createScene();

	//void initial();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	bool onContactBegan(PhysicsContact& contact);
	void onContactSeperate(PhysicsContact& contact);

	void update(float dt);
private:
	Sprite* backgroundSprite;

	bool isGameEnded;

	Node *map;
};

#endif