#include"cocos2d.h"
USING_NS_CC;

class ground :public Node{
public:
	static Node* createBottomGround();
	static Node* createBottomGround1();
	static Node* createBottomGround2();
	static Node* createBottomGround3();
	static Node* createLeftGround();
	static Node* createRightGround();
	CREATE_FUNC(ground);
	virtual bool init();
private:
	ground();
	static Vec2 groundFirstPoint;
	static Vec2 groundLastPoint;
	static Vec2 groundFirstPoint1;
	static Vec2 groundLastPoint1;
	static Vec2 groundFirstPoint2;
	static Vec2 groundLastPoint2;
	static Vec2 groundFirstPoint3;
	static Vec2 groundLastPoint3;
};