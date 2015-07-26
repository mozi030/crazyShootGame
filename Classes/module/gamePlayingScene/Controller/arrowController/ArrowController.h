#include"cocos2d.h"

class ArrowController :public cocos2d::Sprite {
public:
	static ArrowController* createAnArrow(float, float, float, float);
private:
	ArrowController();
};