#include "cocos2d.h"
USING_NS_CC;

class GamePlayingScene :public cocos2d::Scene{
public:
	//CREATE_WITH_PHYSICS_FUNC(GamePlayingScene);
	void initial();
	static GamePlayingScene* createScene();

	void setGameParameter();
	//void initial();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void updateTimeForProgressBar(float dt);
	void updateTimeToCreateEnemy(float dt);
	bool onContactBegan(PhysicsContact& contact);

	void ClickGameEnded(Ref* sender);

private:
	int i = 0;
	Sprite* backgroundSprite;
	float totalTime;
};