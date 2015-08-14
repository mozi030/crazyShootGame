#ifndef __EDGE_H__
#define __EDGE_H__

#include"cocos2d.h"
#include"../../../../public/parameterManager/parameterManager.h"
#include"../../../../public/Constant/Constant.h"
USING_NS_CC;

class edge :public Node{
public:
	static Node* createEdge1(Vec2, Vec2);
	static Node* createEdge2(Vec2, Vec2);
	static Node* createRope(Vec2, Vec2);

	CREATE_FUNC(edge);
	virtual bool init();
private:
	edge();
	static Vec2 edgeFirstPoint;
	static Vec2 edgeLastPoint;
};
#endif