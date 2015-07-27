#include"cocos2d.h"

class GroundController :public cocos2d::Node{
public:
	static GroundController* getInstance();
	CREATE_FUNC(GroundController);
	virtual bool init();

private:
	GroundController();
	~GroundController();
	static GroundController* groundController;
};