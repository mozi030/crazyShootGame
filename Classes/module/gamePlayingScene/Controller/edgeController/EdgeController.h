#ifndef __EDGE_CONTROLLER_H__
#define __EDGE_CONTROLLER_H__

#include"cocos2d.h"
USING_NS_CC;
#include"../../../../public/parameterManager/ParameterManager.h"
#include"../../../../public/Constant/Constant.h"
#include"../../Model/edge/edge.h"

class EdgeController :public cocos2d::Node{
public:
	static EdgeController* getInstance();
	CREATE_FUNC(EdgeController);
	virtual bool init();

private:
	EdgeController();
	~EdgeController();
	static EdgeController* edgeController;
};

#endif