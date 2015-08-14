#include"itemCarrier.h"

Sprite* itemCarrier::itermBall(int PositionY){
	Sprite* itermBall = Sprite::create(Constant::getItermBallPath());

	itermBall->setPosition(Vec2(1024, PositionY));

	itermBall->runAction(MoveBy::create(10, Vec2(-1024, 0)));

	auto aBody = PhysicsBody::createCircle(itermBall->getContentSize().width / 2);
	aBody->setRotationEnable(false);
	itermBall->setPhysicsBody(aBody);

	//并没有设置好，你来设置掩码之类
	aBody->setCategoryBitmask(0x000000FF); //种类
	aBody->setContactTestBitmask(0x000000FF);
	aBody->setCollisionBitmask(0x00000000);
	aBody->setGroup(0);

	aBody->getFirstShape()->setTag(Constant::getItermBallTag());

	aBody->setGravityEnable(false);

	ItermBall = itermBall;
	return ItermBall;
}

Sprite* itemCarrier::getItermBall(){
	return  ItermBall;
}

void itemCarrier::drop(){

}