#include "cocos2d.h"
USING_NS_CC;

/*
class archerController : public cocos2d::Sprite{
public:
static archerController* getInstance();
void initial();
void rotateArrow(Point touchPoint);

private:
archerController();
~archerController();
static archerController* archer;
};
*/

class archer : public cocos2d::Layer{
public:

	bool onTouchBegan(Touch *touch, Event *unused_event);
	Sprite *head, *hand, *body;
	static archer* getInstance();
	virtual bool init();
	CREATE_FUNC(archer);

private:
	archer();
	~archer();
	static archer* archer_;
	Vec2 archerCenter;
	Size playerSize;
	Sprite *hpBgSprite;
	ProgressTimer *hpBar;
	Sprite *hpBar_back;
	Sprite *hpBar_fore;
	int hpValue;
};