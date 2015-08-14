#include "itemInformation.h"

int item::bpNum;
int item::hpNum;
int item::arrowNum;
int item::money;
void item::setHpNum(int num) { hpNum = num; }
int item::getHp() { return hpNum; }
void item::setBpNum(int num) { bpNum = num; }
int item::getBp() { return bpNum; }
void item::setArrowNum(int num) { arrowNum = num; }
int item::getArrow() { return arrowNum; }

void item::setMoney(int num) { money = num; }
void item::addMoney(int num) { money += num; }
int item::getMoney() { return money; }

int item::totalScore;
void item::setTotalScore(int num) { totalScore = num; }
void item::addTotalScore(int num) { totalScore += num; }
int item::getTotalScore() { return totalScore; }

int item::highestGameLevel;
int item::currentArcherLevel;
void item::setHighestGameLevel(int num) { highestGameLevel = num; }
int item::getHighestGameLevel() { return highestGameLevel; }
void item::setCurrentArcherLevel(int num) { currentArcherLevel = num; }
int item::getCurrentArcherLevel(){ return currentArcherLevel; }
void item::addCurrentArcherLevel() { currentArcherLevel++; }

int item::exp;
void item::setExp(int num) { exp = num; }
int item::getExp() { return exp; }

void item::buyArrow(){
	if (money >= 100) {
		arrowNum++;
		money -= 100;
	}
}

void item::saleArrow(){
	if (arrowNum > 0) {
		arrowNum--;
		money += 50;
	}
}

void item::buyBp(){
	if (money >= 10) {
		bpNum++;
		money -= 10;
	}
}

void item::saleBp(){
	if (bpNum > 0) {
		bpNum--;
		money += 5;
	}
}

void item::buyHp(){
	if (money >= 10) {
		hpNum++;
		money -= 10;
	}
}

void item::saleHp(){
	if (hpNum > 0) {
		hpNum--;
		money += 5;
	}
}

string item::getHpNum(){
	return to_string(hpNum);
}

string item::getBpNum(){
	return to_string(bpNum);
}

string item::getArrowNum(){
	return to_string(arrowNum);
}

string item::getMoneyNum(){
	return to_string(money);
}

void item::useArrow(){
	arrowNum--;
}

void item::useHp(){
	hpNum--;
}

void item::useMp(){
	bpNum--;
}