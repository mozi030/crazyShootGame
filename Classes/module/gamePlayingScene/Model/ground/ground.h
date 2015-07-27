#include"cocos2d.h"
USING_NS_CC;

class ground :public Node{
public:
	static Node* createBottomGround();
	CREATE_FUNC(ground);
	virtual bool init();
private:
	ground();
	static Vec2 groundFirstPoint;
	static Vec2 groundLastPoint;
};