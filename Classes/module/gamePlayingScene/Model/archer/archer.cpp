#include"archer.h"
#include"../../../../public/Constant/Constant.h"
#include"../../../../public/ParameterManager/ParameterManager.h"

archer* archer::archer_ = NULL;

archer::archer() {}

archer::~archer() {
	if (archer_ != NULL) {
		archer_ = NULL;
	}
}

archer* archer::getInstance() {
	if (archer_ == NULL) {
		archer_ = archer::create();
	}
	return archer_;
}

void archer::createModel(){
	Size visibleSize = ParameterManager::getVisibleSize();
	float times = 1.5;//图形放大倍数

	body = Sprite::create(Constant::getArcherbodyPath());
	body->setPosition(0, 0);
	body->setScale(times);
	this->addChild(body, 1);

	//auto bodyBody = PhysicsBody::createBox(body->getContentSize());
	//bodyBody->getFirstShape()->setTag(Constant::getArcherTag());
	//body->setPhysicsBody(bodyBody);
	//body->getPhysicsBody()->setContactTestBitmask(0x0000000F);
	//body->getPhysicsBody()->setCollisionBitmask(0x0000000F);

	//绘制武器种类	
	hand = Sprite::create(Constant::getArcherhandPath());
	hand->setPosition(body->getPositionX() - (4 * times), body->getPositionY() - (3 * times));
	hand->setScale(times);
	this->addChild(hand, 3);

	//hand1 = Sprite::create("");
	//hand1->setVisible(false);

	//hand2 = Sprite::create("");
	//hand2->setVisible(false);

	//auto handBody = PhysicsBody::createBox(hand->getContentSize());
	//handBody->getFirstShape()->setTag(Constant::getArcherhandTag());
	//hand->setPhysicsBody(handBody);
	//hand->getPhysicsBody()->setContactTestBitmask(0x0000000F);
	//hand->getPhysicsBody()->setCollisionBitmask(0x0000000F);

	head = Sprite::create(Constant::getArcherheadPath());
	head->setPosition(body->getPositionX() - (1 * times), body->getPositionY() + (2 * times));
	head->setScale(times);
	this->addChild(head, 2);

	//running状态
	CCAnimation *running = CCAnimation::create();
	for (int i = 0; i < 3; i++){
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/archer/running_%d.png", i); 
		running->addSpriteFrameWithFileName(FileName);
	}

	running->setDelayPerUnit(0.8f / 3.0f);
	//running->setRestoreOriginalFrame(true);
	//running->setLoops(-1);
	CCAnimate *action = CCAnimate::create(running);
	runner = Sprite::create("GamePlayingScene/archer/running_0.png");
	runner->setScale(times);
	runner->runAction(RepeatForever::create(action));
	runner->setPosition(0, 10 * times);
	this->addChild(runner, 1);
	this->runner->setVisible(false);
}

bool archer::init(){
	if (!Sprite::init()) { return false; }

	//设置属性
	weapon = 1;

	state = 1;

	initialHpValue = hpValue = 1000;

	//建立弓箭手模型
	createModel();

	//血条
	hpBar_back = Sprite::create(Constant::getBloodBackPath());
	hpBar_back->setPosition(Vec2(body->getContentSize().width / 2 - 35, body->getContentSize().height + 30));
	hpBar_back->setScale(1.4);
	this->addChild(hpBar_back);

	hpBar = ProgressTimer::create(Sprite::create(Constant::getBloodForePath()));
	hpBar->setType(ProgressTimer::Type::BAR); // 设置进度条样式（条形或环形）
	hpBar->setMidpoint(Vec2(0, 0.5f));        // 设置进度条的起始点，（0，y）表示最左边，（1，y）表示最右边，（x，1）表示最上面，（x，0）表示最下面。
	hpBar->setBarChangeRate(Vec2(1, 0));      // 设置进度条变化方向，（1,0）表示横方向，（0,1）表示纵方向。
	hpBar->setPercentage(100);                // 设置当前进度条的进度
	hpBar->setPosition(Vec2(hpBar_back->getContentSize().width / 2, hpBar_back->getContentSize().height / 2));
	hpBar_back->addChild(hpBar);
	hpBar_back->setVisible(true);   // 设置整个血条可见，我们将在Player 遭受攻击的时候再显示血条。


	//add touch listener
	EventListenerTouchOneByOne* screenListener = EventListenerTouchOneByOne::create();
	screenListener->setSwallowTouches(false);// true不向下触摸，简单点来说，比如有两个sprite ,A和 B，A在上B在下（位置重叠）
	screenListener->onTouchBegan = CC_CALLBACK_2(archer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(screenListener, this);
	//整体

	auto aBody = PhysicsBody::createBox(Size(body->getContentSize().width * 0.8, body->getContentSize().height * 1.4));
	aBody->getFirstShape()->setTag(Constant::getArcherTag());
	this->setPhysicsBody(aBody);
	aBody->setRotationEnable(false);

	this->getPhysicsBody()->setCategoryBitmask(0x000000FF); //种类
	this->getPhysicsBody()->setContactTestBitmask(0x000000FF);
	this->getPhysicsBody()->setCollisionBitmask(0x000000FF);
	this->getPhysicsBody()->setGroup(-2);

	return true;
}

bool archer::onTouchBegan(Touch *touch, Event *unused_event) {
	auto archerCenter = this->getPosition();
	auto touchPoint = touch->getLocation();
	if (touchPoint.x >= archerCenter.x) {
		body->setFlippedX(false);//不翻转
		head->setFlippedX(false);
		hand->setFlippedX(false);
		double angle;
		if (fabs(touchPoint.x - archerCenter.x) < 1e-6) {
			angle = 135;
		}
		else {
			//计算点击处与archer的连线与九点钟方向的顺时针夹角。
			angle = -atan((touchPoint.y - archerCenter.y) / (touchPoint.x - archerCenter.x)) / 3.141592654 * 180;
			angle += 180;
			if (angle < 135) angle = 135;//限制角的范围，不然如果要头往正上方看的话，图会很难看
			else if (angle > 225) angle = 225;
		}
		head->setRotation(angle - 180);
		hand->setRotation(angle + 90);
	}
	else {
		double angle = -atan((touchPoint.y - archerCenter.y) / (touchPoint.x - archerCenter.x)) / 3.141592654 * 180;
		body->setFlippedX(true);
		head->setFlippedX(true);
		hand->setFlippedX(true);
		if (angle > 45) angle = 45;
		else if (angle < -45) angle = -45;
		head->setRotation(angle);
		hand->setRotation(angle + 90);
	}
	return true;
}

void archer::setBlood(int value){
	hpValue = value;
}

int archer::getBlood(){
	return hpValue;
}

void archer::setWeapon(int m){
	weapon = m;
}

int archer::getWeapon(){
	return weapon;
}


void archer::running(){
	hand->setVisible(false);
	body->setVisible(false);
	head->setVisible(false);
	runner->setVisible(true);
	if (archer_->ArcherDirection == true){
		head->setFlippedX(false);
		body->setFlippedX(false);
		hand->setFlippedX(false);
		head->setRotation(0);
		body->setRotation(0);
		hand->setRotation(0);
		runner->setFlippedX(false);
	}
	else{
		head->setFlippedX(true);
		body->setFlippedX(true);
		hand->setFlippedX(true);
		head->setRotation(0);
		body->setRotation(0);
		hand->setRotation(0);
		runner->setFlippedX(true);
	}
}

void archer::stopping(){
	hand->setVisible(true);
	body->setVisible(true);
	head->setVisible(true);
	runner->setVisible(false);
}

void archer::jump(){
	//auto jump = JumpBy::create(0.1, Vec2(0,50), 200.0, 1);
	//archer_->runAction(jump);
	auto velocity = this->getPhysicsBody()->getVelocity();
	this->getPhysicsBody()->setVelocity(Vec2(velocity.x, velocity.y + 300));
}

//弓箭手受到攻击
void archer::attacked(int _damage){
	int currentHpValue = getBlood() - _damage;
	if (currentHpValue < 0) currentHpValue = 0;
	setBlood(currentHpValue);
	hpBar->setPercentage(100.0 * getBlood() / initialHpValue);
	//受伤动画
	string s = CCString::createWithFormat("%d", _damage)->_string;
	for (int i = 0; i < s.length(); i++) {
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/archer/number/num_%c.png", s[i]);
		auto number = Sprite::create(FileName);
		number->setPosition(Vec2(body->getContentSize().width / 2 - 40 + i * 30, body->getContentSize().height + 15));
		archer_->addChild(number, 1);
		auto move = JumpTo::create(0.8, Vec2(body->getContentSize().width / 2 - 40 + i * 30, body->getContentSize().height + 65), 50, 1);
		auto fadeout = FadeOut::create(1.0);
		auto action = Sequence::create(move, fadeout, NULL);
		number->runAction(action);
	}
}