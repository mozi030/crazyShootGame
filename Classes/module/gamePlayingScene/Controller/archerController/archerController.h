#include "cocos2d.h"
USING_NS_CC;
#include"../../Model/archer/archer.h"

class ArcherController : public cocos2d::Layer{
public:
	static ArcherController* getInstance();
	virtual bool init();
	CREATE_FUNC(ArcherController);

	archer* getArcher();

private:
	ArcherController();
	~ArcherController();
	static ArcherController* archerController;
	archer* archer_;
};