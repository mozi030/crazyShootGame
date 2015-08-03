#include "cocos2d.h"
USING_NS_CC;

class archer : public cocos2d::Sprite{
public:

	bool onTouchBegan(Touch *touch, Event *unused_event);
	Sprite *head, *hand, *body;
	//Vector <SpriteFrame*> runningArcher;
	Sprite *runner;
	Sprite *hand1, *hand2, *hand3;

	static archer* getInstance();
	CREATE_FUNC(archer);
	virtual bool init();
	void createModel();

	//弓箭手属性
	//blood
	Sprite *hpBgSprite;
	ProgressTimer *hpBar;
	Sprite *hpBar_back;
	Sprite *hpBar_fore;

	int hpValue;
	int initialHpValue;

	//武器种类1,2,3
	int weapon;
	//状态参数(1 stop,2 running,3 jump)
	int state;
	//运动方向
	bool ArcherDirection;

	void setBlood(int value);
	int getBlood();

	void setWeapon(int m);
	int getWeapon();

	void jump();
	void running();
	void stopping();
	void attacked(int);

private:
	archer();
	~archer();
	static archer* archer_;
};