#include"cocos2d.h"

class ArrowController :public cocos2d::Sprite {
public:
	static ArrowController* createAnArrow(float, float, float, float);
	void updateTimeToChangeArrowAngle(float dt, void* data,std::string );
private:
	ArrowController();
};