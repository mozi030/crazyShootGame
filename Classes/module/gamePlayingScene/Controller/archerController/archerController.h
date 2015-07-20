#include "cocos2d.h"
USING_NS_CC;

class archerController : public cocos2d::Sprite{
public:
	static archerController* getInstance();
	void initial();

private:
	archerController();
	~archerController();
	static archerController* archer;
};