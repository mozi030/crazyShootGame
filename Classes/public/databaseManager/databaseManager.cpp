#include"databaseManager.h"

dataTemplete databaseManager::databaseSelete(int recordNum) {
	dataTemplete aDataTemplete;
	char nameOfTemp[30];

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_exist", recordNum);
	if (database->getBoolForKey(nameOfTemp) == false) {
		aDataTemplete.recordNum = 0;
		return aDataTemplete;
	}

	aDataTemplete.recordNum = recordNum;

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_highestGameLevel", recordNum);
	aDataTemplete.highestGameLevel = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_totalScore", recordNum);
	aDataTemplete.totalScore = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_bloodBottleNum", recordNum);
	aDataTemplete.bloodBottleNum = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_blueBottleNum", recordNum);
	aDataTemplete.blueBottleNum = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_weapon1Num", recordNum);
	aDataTemplete.weapon1Num = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_weapon2Num", recordNum);
	aDataTemplete.weapon2Num = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_currentArcherLevel", recordNum);
	aDataTemplete.currentArcherLevel = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_coinNum", recordNum);
	aDataTemplete.coinNum = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_exp", recordNum);
	aDataTemplete.exp = getIntFromXML(nameOfTemp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_date", recordNum);
	aDataTemplete.date = database->getStringForKey(nameOfTemp);

	return aDataTemplete;
}

void databaseManager::databaseSave(dataTemplete _aDataTemplete) {
	char nameOfTemp[30];

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_exist", _aDataTemplete.recordNum);
	database->setBoolForKey(nameOfTemp, true);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_highestGameLevel", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.highestGameLevel);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_totalScore", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.totalScore);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_highestGameLevel", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.highestGameLevel);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_bloodBottleNum", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.bloodBottleNum);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_blueBottleNum", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.blueBottleNum);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_weapon1Num", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.weapon1Num);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_weapon2Num", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.weapon2Num);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_coinNum", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.coinNum);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_currentArcherLevel", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.currentArcherLevel);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_exp", _aDataTemplete.recordNum);
	storeIntToXML(nameOfTemp, _aDataTemplete.exp);

	memset(nameOfTemp, 0, 30);
	sprintf(nameOfTemp, "Record%d_date", _aDataTemplete.recordNum);
	database->setStringForKey(nameOfTemp, _aDataTemplete.date);
}