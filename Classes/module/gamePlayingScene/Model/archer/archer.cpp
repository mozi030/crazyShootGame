#include"archer.h"

archer* archer::archer_ = NULL;

archer::archer() {}

archer::~archer() {
	if (archer_ != NULL) {
		archer_->removeFromParentAndCleanup(true);
		archer_ = NULL;
	}
}

archer* archer::getInstance() {
	if (archer_ == NULL) {
		archer_ = archer::create();
	}
	return archer_;
}

bool archer::init(){
	if (!Sprite::init()) { return false; }

	setParameter();

	//建立弓箭手模型
	createModel();

	//创建血条
	createBloodBar();

	//整体
	auto aBody = PhysicsBody::createBox(Size(body->getContentSize().width * 0.8, body->getContentSize().height * 1.4));
	aBody->getFirstShape()->setTag(Constant::getArcherTag());
	this->setPhysicsBody(aBody);
	aBody->setRotationEnable(false);

	bitmask aBitmask = Constant::getArcherBitmask();
	auto physicsBody = this->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask);
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);

	return true;
}

void archer::setParameter() {
	
}

void archer::createModel(){
	Size visibleSize = ParameterManager::getVisibleSize();
	float times = 1.5;//图形放大倍数

	body = Sprite::create(Constant::getArcherbodyPath());
	body->setPosition(0, 0);
	body->setScale(times);
	this->addChild(body, 1);

	//绘制武器种类	
	hand = Sprite::create(Constant::getArcherhandPath());
	hand->setPosition(body->getPositionX() - (4 * times), body->getPositionY() - (3 * times));
	hand->setScale(times);
	this->addChild(hand, 3);

	head = Sprite::create(Constant::getArcherheadPath());
	head->setPosition(body->getPositionX() - (1 * times), body->getPositionY() + (2 * times));
	head->setScale(times);
	this->addChild(head, 2);

	//run动画
	CCAnimation *running = CCAnimation::create();
	for (int i = 0; i < 3; i++){
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/archer/running_%d.png", i); 
		running->addSpriteFrameWithFileName(FileName);
	}
	running->setDelayPerUnit(0.8f / 3.0f);
	CCAnimate *runningAction = CCAnimate::create(running);

	runner = Sprite::create("GamePlayingScene/archer/running_0.png");
	runner->setScale(times);
	runner->runAction(RepeatForever::create(runningAction));
	runner->setPosition(0, 10 * times);
	this->addChild(runner, 1);
	this->runner->setVisible(false);

	//死亡状态
	deathSprite = Sprite::create("GamePlayingScene/archer/death/death_0.png");
	this->addChild(deathSprite, 1);
	deathSprite->setScale(times);
	deathSprite->setPosition(0, 10 * times);
	this->deathSprite->setVisible(false);

	//climb动画
	climbSprite = Sprite::create("GamePlayingScene/archer/climb/climb_0.png");
	//climbSprite->setScale(times);
	climbSprite->setPosition(0, 10 * times);
	this->addChild(climbSprite, 1);
	this->climbSprite->setVisible(false);

	direction = true;
}

void archer::createBloodBar() {
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
}

void archer::aimAt(Vec2 touchPoint) {
	auto archerCenter = this->getPosition();
	if (touchPoint.x >= archerCenter.x) {
		direction = true;
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
		direction = false;
		double angle = -atan((touchPoint.y - archerCenter.y) / (touchPoint.x - archerCenter.x)) / 3.141592654 * 180;
		body->setFlippedX(true);
		head->setFlippedX(true);
		hand->setFlippedX(true);
		if (angle > 45) angle = 45;
		else if (angle < -45) angle = -45;
		head->setRotation(angle);
		hand->setRotation(angle + 90);
	}
}

//属性参数
void archer::setBlood(int value){ 
	hpValue = value; 
	if (hpValue > initialHpValue) {
		hpValue = initialHpValue;
	}
	hpBar->setPercentage(100.0 * hpValue / initialHpValue);
}
int archer::getBlood(){ return hpValue; }
void archer::setInitialBlood(int num) { initialHpValue = num; }
int archer::getInitialBlood() { return initialHpValue; }

void archer::setBlue(int _value) { 
	blueValue = _value; 
	if (blueValue > initialBlueValue) {
		blueValue = initialBlueValue;
	}
}
int archer::getBlue() { return blueValue; }
int archer::getInitialBLue() { return initialBlueValue; }
void archer::setInitialBlue(int num) { initialBlueValue = num; }

void archer::setExp(int _value){ expValue = _value; }
int archer::getExp() { return expValue; }
void archer::addExp(int num) {
	expValue += num;
	if (expValue >= totalExpValue) {
		while (expValue >= totalExpValue) {
			//level up
			item::addCurrentArcherLevel();
			expValue -= totalExpValue;
			totalExpValue = ParameterManager::getLevelParameterInstance(item::getCurrentArcherLevel())->levelUpExp;

			auto levelUpLabel = LabelBMFont::create("levelUp", "fonts/futura-48.fnt");
			this->addChild(levelUpLabel, 3);
			levelUpLabel->setPosition(0,100);
			levelUpLabel->runAction(FadeOut::create(10));
		}
		auto aLevelParameter = ParameterManager::getLevelParameterInstance(item::getCurrentArcherLevel());
		setInitialBlood(aLevelParameter->blood);
		setInitialBlue(aLevelParameter->blue);
		hpBar->setPercentage(100.0 * hpValue / initialHpValue);
	}
}
void archer::setTotalExp(int num) { totalExpValue = num; }
int archer::getTotalExp() { return totalExpValue; }

void archer::setWeapon(int m){
	weapon = m;
}
int archer::getWeapon(){
	return weapon;
}

int archer::getScore() { return score; }
void archer::setScore(int num) { score = num; }
void archer::addScore(int num) { score += num; }

bool archer::getDirection() { return direction; }

void archer::killEnemy(int mode) {
	addExp(mode * 5 * ParameterManager::getCurrentGameLevel());
	addScore(mode * 5 * ParameterManager::getCurrentGameLevel());
	item::addMoney(mode * 5);
}

void archer::running(bool direction,bool isClimbing){
	this->direction = direction;
	hand->setVisible(false);
	body->setVisible(false);
	head->setVisible(false);
	//runner->setVisible(false);
	//climbSprite->setVisible(false);
	if (hpValue > 0) {
		if (isClimbing == false) {
			runner->setVisible(true);
		}
		else {
			climbSprite->setVisible(true);
		}
		if (direction == true){
			head->setFlippedX(false);
			body->setFlippedX(false);
			hand->setFlippedX(false);
			head->setRotation(0);
			body->setRotation(0);
			hand->setRotation(0);
			runner->setFlippedX(false);

			auto action = RepeatForever::create(MoveBy::create(1, Vec2(100, 0)));
			action->setTag(Constant::getArcherMoveRightActionTag());
			archer_->runAction(action);
		}
		else{
			head->setFlippedX(true);
			body->setFlippedX(true);
			hand->setFlippedX(true);
			head->setRotation(0);
			body->setRotation(0);
			hand->setRotation(0);
			runner->setFlippedX(true);

			auto action = RepeatForever::create(MoveBy::create(1, Vec2(-100, 0)));
			action->setTag(Constant::getArcherMoveLeftActionTag());
			archer_->runAction(action);
		}
	}
}

void archer::stopping(){
	if (hpValue > 0){
		hand->setVisible(true);
		body->setVisible(true);
		head->setVisible(true);
		runner->setVisible(false);
		climbSprite->setVisible(false);
	}
	else{
		hand->setVisible(false);
		body->setVisible(false);
		head->setVisible(false);
		runner->setVisible(false);
		climbSprite->setVisible(false);
	}
}

void archer::jump(){
	//auto jump = JumpBy::create(0.1, Vec2(0,50), 200.0, 1);
	//archer_->runAction(jump);
	auto velocity = this->getPhysicsBody()->getVelocity();
	this->getPhysicsBody()->setVelocity(Vec2(velocity.x, velocity.y + 300));
}

//弓箭手受到攻击
void archer::attacked(int _damage){
	int initialBlood = getBlood();
	int currentBlood = initialBlood - _damage;
	if (currentBlood <= 0) currentBlood = 0;
	setBlood(currentBlood);
	//受伤动画:跳数字
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

	if (hpValue <= 0) {
		//gameover
		death();
	}
}

//死亡动画
void archer::death(){
	hand->setVisible(false);
	body->setVisible(false);
	head->setVisible(false);
	runner->setVisible(false);
	climbSprite->setVisible(false);
	hpBar_back->setVisible(false);
	deathSprite->setVisible(true);

	CCAnimation *dead = CCAnimation::create();
	for (int i = 0; i < 9; i++){
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/archer/death/death_%d.png", i);
		dead->addSpriteFrameWithFileName(FileName);
	}

	dead->setDelayPerUnit(1.8f / 9.0f);
	CCAnimate *action = CCAnimate::create(dead);
	deathSprite->runAction(Repeat::create(action, 1));
}

void archer::climb() {
	hand->setVisible(false);
	body->setVisible(false);
	head->setVisible(false);
	runner->setVisible(false);
	climbSprite->setVisible(true);
	//deathSprite->setVisible(false);

	bitmask aBitmask = Constant::getArcherClimbingBitmask();
	auto physicsBody = archer_->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask);
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);

	physicsBody->setVelocity(Vec2::ZERO);
	physicsBody->setGravityEnable(false);
}

void archer::notClimb(bool isRunning) {
	if (isRunning == true) {
		hand->setVisible(false);
		body->setVisible(false);
		head->setVisible(false);
		runner->setVisible(true);
	}
	else{
		hand->setVisible(true);
		body->setVisible(true);
		head->setVisible(true);
		runner->setVisible(false);
	}
	climbSprite->setVisible(false);
	//deathSprite->setVisible(false);

	bitmask aBitmask = Constant::getArcherBitmask();
	auto physicsBody = archer_->getPhysicsBody();
	physicsBody->setCategoryBitmask(aBitmask.categoryBitmask);
	physicsBody->setCollisionBitmask(aBitmask.collisionBitmask);
	physicsBody->setContactTestBitmask(aBitmask.contactTestBitmask);
	physicsBody->setGroup(aBitmask.group);

	//physicsBody->setVelocity(Vec2::ZERO);
	physicsBody->setGravityEnable(true);
}

void archer::climbUp() {
	auto action = RepeatForever::create(MoveBy::create(1, Vec2(0, 100)));
	action->setTag(Constant::getArcherClimbUpActionTag());
	archer_->runAction(action);

	CCAnimation *climbing = CCAnimation::create();
	for (int i = 0; i <= 1; i++){
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/archer/climb/climb_%d.png", i);
		climbing->addSpriteFrameWithFileName(FileName);
	}
	climbing->setDelayPerUnit(0.5f);
	auto climbingAction = RepeatForever::create(CCAnimate::create(climbing));
	climbingAction->setTag(999);

	climbSprite->runAction(climbingAction);
}

void archer::climbDown() {
	auto action = RepeatForever::create(MoveBy::create(1, Vec2(0, -100)));
	action->setTag(Constant::getArcherClimbDownActionTag());
	archer_->runAction(action);

	CCAnimation *climbing = CCAnimation::create();
	for (int i = 0; i <= 1; i++){
		char FileName[128] = { 0 };
		sprintf(FileName, "GamePlayingScene/archer/climb/climb_%d.png", i);
		climbing->addSpriteFrameWithFileName(FileName);
	}
	climbing->setDelayPerUnit(0.5f);
	auto climbingAction = RepeatForever::create(CCAnimate::create(climbing));
	climbingAction->setTag(999);

	climbSprite->runAction(climbingAction);
}

void archer::stoppingClimbing() {
	climbSprite->stopActionByTag(999);
}