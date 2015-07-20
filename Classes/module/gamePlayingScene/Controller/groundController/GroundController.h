#include"cocos2d.h"

class GroundController :public cocos2d::Node{
public:
	static GroundController* getInstance();
	void initial();

private:
	GroundController();
	~GroundController();
	static GroundController* groundController;
};