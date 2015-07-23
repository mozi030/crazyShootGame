#include"TopRankScene.h"



Scene* TopRankScene::createScene()
{
	auto aScene = Scene::create();
	auto layer = TopRankScene::create();
	aScene->addChild(layer);
	return aScene;
}


bool TopRankScene::init() {

	auto backgroundSprite = Sprite::create("image/background.png");
	backgroundSprite->setPosition(0, 0);
	backgroundSprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(backgroundSprite, 0);

	//可视范围大小
	Size visibleSize = backgroundSprite->getContentSize();

	//创建menu,实现return个按钮
	auto _return = Menu::create();
	_return->setPosition(Vec2::ZERO);
	_return->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(_return);

	auto returnIterm = MenuItemImage::create(
																		"Return.gif", 
																		"Return.gif",
																		CC_CALLBACK_1(TopRankScene::Return, this));
	returnIterm->setPosition(visibleSize.width , 0);
	returnIterm->setAnchorPoint(ccp(1,0));
	_return->addChild(returnIterm);
	//test
	Node *temp = TopRankScene::createFirstRow();
	this->addChild(temp);
	int i = 1;
	while (i < 6){
		Node * temp = TopRankScene::createDefaultRow(i);
		this->addChild(temp);
		i++;

	}
	return true;
}

void TopRankScene::Return(Ref* sender){
	Director::sharedDirector()->popScene();
}



rankStore TopRankScene::getStore(int n){//获得排行n的信息
	rankStore t;
	return t;
}

Node* TopRankScene::createFirstRow(){
	Node* row = Node::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	
	LabelTTF* labelRank = LabelTTF::create("排名", "AppleGothic", 20);
	LabelTTF* labelScore = LabelTTF::create("分数", "AppleGothic", 20);
	LabelTTF* labelName = LabelTTF::create("姓名", "AppleGothic", 20);


	labelRank->setAnchorPoint(Point(0, 0));
	labelRank->setPosition(visibleSize.width / 4, visibleSize.height / 20 * 5 + 10);
	labelScore->setAnchorPoint(Point(0, 0));
	labelScore->setPosition(visibleSize.width / 4 * 3 + 10, visibleSize.height / 20 * 5  + 10);
	labelName->setAnchorPoint(Point(0, 0));
	labelName->setPosition(visibleSize.width / 4 * 2 + 10, visibleSize.height / 20 * 5 + 10);

	row->addChild(labelName);
	row->addChild(labelRank);
	row->addChild(labelScore);

	row->setAnchorPoint(Point(0, 0));
	row->setPosition(0, visibleSize.height / 20 * 5+ 10);
	return row;
}

Node* TopRankScene::createRow(int rank, int score, std::string name){

	Node* row = Node::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	char _rank[2];
	itoa(rank, _rank, 10);
	LabelTTF* labelRank = LabelTTF::create(_rank, "AppleGothic", 20);
	char _score[10];
	itoa(score, _score, 10);
	LabelTTF* labelScore = LabelTTF::create(_score, "AppleGothic", 20); 
	LabelTTF* labelName = LabelTTF::create(name, "AppleGothic", 20);


	labelRank->setAnchorPoint(Point(0, 0));
	labelRank->setPosition(visibleSize.width / 4 + 10, visibleSize.height / 20 * (5 - rank) + 10);
	labelScore->setAnchorPoint(Point(0, 0));
	labelScore->setPosition(visibleSize.width / 4 * 3 + 10, visibleSize.height / 20 * (5 - rank) + 10);
	labelName->setAnchorPoint(Point(0, 0));
	labelName->setPosition(visibleSize.width / 4 * 2 + 10, visibleSize.height / 20 * (5 - rank) + 10);

	row->addChild(labelName);
	row->addChild(labelRank);
	row->addChild(labelScore);

	row->setAnchorPoint(Point(0, 0));
	row->setPosition(0, visibleSize.height / 20 * (5 - rank));
	return row;
}

Node* TopRankScene::createDefaultRow(int rank){

	Node* row = Node::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	char _rank[2];
	itoa(rank, _rank, 10);
	LabelTTF* labelRank = LabelTTF::create(_rank, "AppleGothic", 20);
	LabelTTF* labelScore = LabelTTF::create("0", "AppleGothic", 20);
	LabelTTF* labelName = LabelTTF::create("Default", "AppleGothic", 20);


	labelRank->setAnchorPoint(Point(0, 0));
	labelRank->setPosition(visibleSize.width / 4  + 10, visibleSize.height / 20 * (5 - rank) + 10);
	labelScore->setAnchorPoint(Point(0, 0));
	labelScore->setPosition(visibleSize.width / 4 * 3 + 10, visibleSize.height / 20 * (5 - rank)+10);
	labelName->setAnchorPoint(Point(0, 0));
	labelName->setPosition(visibleSize.width / 4 * 2 + 10, visibleSize.height / 20 * (5 - rank)+10);

	row->addChild(labelName);
	row->addChild(labelRank);
	row->addChild(labelScore);

	row->setAnchorPoint(Point(0, 0));
	row->setPosition(0, visibleSize.height / 20 * (5 - rank)+10);
	return row;
}