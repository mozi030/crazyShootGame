#include "cocos2d.h"
USING_NS_CC;

class archerController : public cocos2d::Layer{
public:

	bool onTouchBegan(Touch *touch, Event *unused_event);

	static archerController* getInstance();
	virtual bool init();
	CREATE_FUNC(archerController);

private:
	archerController();
	~archerController();
	static archerController* archer;
	Vec2 archerCenter;
	Sprite *head, *hand, *body;
};