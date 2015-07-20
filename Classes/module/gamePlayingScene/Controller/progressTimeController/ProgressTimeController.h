#include"cocos2d.h"
USING_NS_CC;

class ProgressTimeController : public cocos2d::Layer{
public:
	static ProgressTimeController* getInstance();
	void initial();

	ProgressTimer* getProgressTimer();
	Label* getProgressTimerLabel();

private:
	ProgressTimeController();
	~ProgressTimeController();
	static ProgressTimeController* progressTimeController;

	Sprite* progressSprite1;
	Sprite* progressSprite2;
	ProgressTimer* progressTimer;
	Label* progressTimerLabel;
};