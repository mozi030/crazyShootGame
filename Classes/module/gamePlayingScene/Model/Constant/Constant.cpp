#include"Constant.h"

Constant* Constant::constant = NULL;

//文件位置
string Constant::archerPath = "image/texture/archer.png";
string Constant::enemyPath = "image/texture/enemy.png";
string Constant::arrowPath = "image/arrow.png";
string Constant::backgroundPath = "image/background.png";
string Constant::processBar1Path = "image/processBar.png";
string Constant::processBar2Path = "image/processBar2.png";
string Constant::futuraPath = "fonts/futura-48.fnt";
string Constant::enemyGoblinPath = "image/enemy/Goblin/Goblin.plist";
string Constant::enemySoldierPath = "image/enemy/Soldier/Soldier.plist";
string Constant::enemyArrowEnemyPath = "image/enemy/ArrowEnemy/ArrowEnemy.plist";



//在cache中的名字(不能重复)
string Constant::archerFrameName = "archerFrameName";
string Constant::enemyFrameName = "enemyFrameName";
string Constant::enemyAnimationName = "enemyAnimationName";

//tag不能重复
int Constant::archerTag = 1;
int Constant::groundTag = 2;
int Constant::arrowTag = 3;
int Constant::enemyTag = 4;
int Constant::enemyTag1 = 5;
int Constant::enemyTag2= 6;
int Constant::enemyTag3 = 7;


float Constant::timeLimit = 10.0;

string Constant::getArcherPath() {
	return archerPath;
}

string Constant::getEnemyGoblinPath(){
	return enemyGoblinPath;
}

string Constant::getEnemySoldierPath(){
	return enemySoldierPath;
}

string Constant::getEnemyArrowEnemyPath(){
	return enemyArrowEnemyPath;
}

string Constant::getArcherFrameName() {
	return archerFrameName;
}

string Constant::getEnemyPath() {
	return enemyPath;
}

string Constant::getArrowPath() {
	return arrowPath;
}

string Constant::getEnemyFrameName() {
	return enemyFrameName;
}

string Constant::getEnemyAnimationName() {
	return enemyAnimationName;
}

int Constant::getArcherTag() {
	return archerTag;
}



int Constant::getGroundTag() {
	return groundTag;
}

int Constant::getArrowTag() {
	return arrowTag;
}

int Constant::getEnemyTag() {
	return enemyTag;
}

int Constant::getEnemyTag1() {
	return enemyTag1;
}

int Constant::getEnemyTag2() {
	return enemyTag2;
}

int Constant::getEnemyTag3() {
	return enemyTag3;
}

string Constant::getBackgroundPath() {
	return backgroundPath;
}

string Constant::getProcessBar1Path() {
	return processBar1Path;
}

string Constant::getProcessBar2Path() {
	return processBar2Path;
}

string Constant::getFuturaPath() {
	return futuraPath;
}

float Constant::getTimeLimit() {
	return timeLimit;
}