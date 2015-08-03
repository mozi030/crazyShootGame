#include "cocos2d.h"
#include"Controller/archerController/archerController.h"
#include"Controller/progressTimeController/ProgressTimeController.h"
#include"Controller\groundController\GroundController.h"
#include"Controller\enemyController\EnemyController.h"
#include"Controller\arrowController\ArrowController.h"
USING_NS_CC;

class GamePlayingScene :public cocos2d::Scene{
public:
	//CREATE_WITH_PHYSICS_FUNC(GamePlayingScene);
	void initial();
	static GamePlayingScene* createScene();

	//void initial();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void updateTimeForProgressBar(float dt);
	bool onContactBegan(PhysicsContact& contact);

	void ClickGameEnded(Ref* sender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*event);

	/*void updateTimeToMoveLeft(float dt);
	void updateTimeToMoveRight(float dt);*/

	void GamePlayingScene::guanka(Ref* sender);
	void GamePlayingScene::again(Ref* sender);
	void GamePlayingScene::next(Ref* sender);

	void update(float dt);
private:
	static Camera* camera;

	Sprite* backgroundSprite;
	float totalTime;

	Node *map;
	ArcherController* player;

	MenuItemImage*gameEndedItem;
};