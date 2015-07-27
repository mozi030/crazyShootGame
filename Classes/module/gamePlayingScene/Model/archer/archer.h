#include "cocos2d.h"
USING_NS_CC;

class archer : public cocos2d::Sprite{
public:

	bool onTouchBegan(Touch *touch, Event *unused_event);
	Sprite *head, *hand, *body;

	static archer* getInstance();
	CREATE_FUNC(archer);
	virtual bool init();

private:
	archer();
	~archer();
	static archer* archer_;

	Sprite *hpBgSprite;
	ProgressTimer *hpBar;
	Sprite *hpBar_back;
	Sprite *hpBar_fore;
	int hpValue;
};