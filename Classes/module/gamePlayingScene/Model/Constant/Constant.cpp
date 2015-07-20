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


//在cache中的名字(不能重复)
string Constant::archerFrameName = "archerFrameName";
string Constant::enemyFrameName = "enemyFrameName";
string Constant::enemyAnimationName = "enemyAnimationName";

//tag不能重复
int Constant::archerTag = 1;
int Constant::groundTag = 2;
int Constant::arrowTag = 3;
int Constant::enemyTag = 4;

float Constant::timeLimit = 10.0;

string Constant::getArcherPath() {
	return archerPath;
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