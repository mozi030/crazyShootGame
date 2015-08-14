#include"Constant.h"

float Constant::timeLimit = 10.0;
float Constant::getTimeLimit() {
	return timeLimit;
}

//levelChosenScene
string Constant::levelChosenSceneBackgroundPath = "LevelChosenScene/bg2.png";
string Constant::getLevelChosenSceneBackgroundPath() { return levelChosenSceneBackgroundPath; }

string Constant::levelChosenButton1Path = "LevelChosenScene/choose_btn_1.png";
string Constant::getLevelChosenButton1Path() { return levelChosenButton1Path; }

string Constant::levelChosenButton2Path = "LevelChosenScene/choose_btn_2.png";
string Constant::getLevelChosenButton2Path() { return levelChosenButton2Path; }

string Constant::levelChosenButton3Path = "LevelChosenScene/choose_btn_3.png";
string Constant::getLevelChosenButton3Path() { return levelChosenButton3Path; }

string Constant::levelChosenButton4Path = "LevelChosenScene/choose_btn_4.png";
string Constant::getLevelChosenButton4Path() { return levelChosenButton4Path; }

string Constant::levelChosenButton5Path = "LevelChosenScene/choose_btn_boss.png";
string Constant::getLevelChosenButton5Path() { return levelChosenButton5Path; }

string Constant::levelChosenButtonshopPath = "LevelChosenScene/choose_btn_shop.png";
string Constant::getLevelChosenButtonshopPath() { return levelChosenButtonshopPath; }

//gamePlayingScene
string Constant::level1MapCsdPath = "MapScene/Layer.csb";
string Constant::getLevel1MapCsdPath() { return level1MapCsdPath; }

string Constant::gameEndedPath = "GamePlayingScene/menuGameEnded.png";
string Constant::getGameEndedPath() { return gameEndedPath; }

string Constant::gameOverCsdPath = "GamePlayingScene/GameOverCsd/GameOver1.csb";
string Constant::getGameOverCsdPath() { return gameOverCsdPath; }

//arrow
string Constant::arrow1Path = "GamePlayingScene/arrow/arrow.png";
string Constant::getArrow1Path() { return arrow1Path; }

string Constant::arrow2Path = "GamePlayingScene/arrow/arrow2.png";
string Constant::getArrow2Path() { return arrow2Path; }

string Constant::arrow3Path = "GamePlayingScene/arrow/arrow3.png";
string Constant::getArrow3Path() { return arrow3Path; }

int Constant::arrowTag = 3;//tag选择范围0-9
int Constant::getArrowTag() { return arrowTag; }

int Constant::arrow4Tag = 4;//tag选择范围0-9
int Constant::getArrow4Tag() { return arrow4Tag; }

bitmask Constant::arrowBitmask;
bitmask Constant::getArrowBitmask() {
	arrowBitmask.categoryBitmask = 0x0000000F;
	arrowBitmask.collisionBitmask = 0x0000000F;
	arrowBitmask.contactTestBitmask = 0x000000FF;
	arrowBitmask.group = -2;
	return arrowBitmask;
}

//processBar
string Constant::processBar1Path = "GamePlayingScene/processBar/processBar.png";
string Constant::getProcessBar1Path() { return processBar1Path; }

string Constant::processBar2Path = "GamePlayingScene/processBar/processBar2.png";
string Constant::getProcessBar2Path() { return processBar2Path; }

string Constant::futuraPath = "fonts/futura-48.fnt";
string Constant::getFuturaPath() { return futuraPath; }

//enemy
string Constant::enemyGoblinPath = "GamePlayingScene/enemy/Goblin/Goblin.plist";
string Constant::enemySoldierPath = "GamePlayingScene/enemy/Soldier/Soldier.plist";
string Constant::enemySheepPath = "GamePlayingScene/enemy/Sheep/Sheep.plist";
string Constant::enemyBossPath = "GamePlayingScene/enemy/Boss/Boos/Boss.plist";
string Constant::enemyBossAttackPath = "GamePlayingScene/enemy/Boss/Ability/BossAttack.plist";
string Constant::enemyArrowPath = "GamePlayingScene/enemy/EnemyArrow.png";
string Constant::enemyBoobPath = "GamePlayingScene/enemy/Boob.png";
string Constant::enemyArrowEnemyPath = "GamePlayingScene/enemy/ArrowEnemy/ArrowEnemy.plist";
string Constant::enemyFrameName = "enemyFrameName";
string Constant::enemyAnimationName = "enemyAnimationName";
int Constant::enemyTag = 10;//tag选择范围10-19
int Constant::enemyArrowTag = 13;
string Constant::enemyBloodBackPath = "GamePlayingScene/enemy/blood_back.png";
string Constant::enemyBloodForePath = "GamePlayingScene/enemy/blood_fore.png";

string Constant::enemyArrowEnemyMove = "enemyArrowEnemyMove";
string Constant::enemyArrowEnemyAttack = "enemyArrowEnemyAttack";
string Constant::enemyArrowEnemyDeath = "enemyArrowEnemyDeath";
string Constant::enemySoldierAttack = "enemySoldierAttack";
string Constant::enemySoldierDeath = "enemySoldierDeath";
string Constant::enemySoldierMove = "enemySoldierMove";

string Constant::enemySheepMove = "enemyGoblinMove";
string Constant::enemySheepAttack = "enemyGoblinAttack";
string Constant::enemySheepDeath = "enemyGoblinDeath";

string Constant::enemyGoblinMove = "enemySheepMove";
string Constant::enemyGoblinAttack = "enemySheepAttack";
string Constant::enemyGoblinDeath = "enemySheepDeath";

string Constant::enemyBossNormal = "enemyBossNormal";
string Constant::enemyBossAttack = "enemyBossAttack";
string Constant::enemyBossAddBlood = "enemyBossAddBlood";
string Constant::enemyBossCall = "enemyBossCall";
string Constant::enemyBossAttackCall = "enemyBossAttackCall";
string Constant::enemyBossAttackReal = "enemyBossAttackReal";
string Constant::enemyBossAttackAddBlood = "enemyBossAttackAddBlood";

string Constant::getEnemyBossNormal(){ return enemyBossNormal; };
string Constant::getEnemyBossAttack(){ return enemyBossAttack; };
string Constant::getEnemyBossCall(){ return enemyBossCall; };
string Constant::getEnemyBossAddBlood(){ return enemyBossAddBlood; };
string Constant::getEnemyBossAttackReal(){ return enemyBossAttackReal; };
string Constant::getEnemyBossAttackCall(){ return enemyBossAttackCall; };
string Constant::getEnemyBossAttackAddBlood(){ return enemyBossAttackAddBlood; };

string Constant::getEnemyArrowEnemyMove() { return enemyArrowEnemyMove; }
string Constant::getEnemyArrowEnemyDeath() { return enemyArrowEnemyDeath; }
string Constant::getEnemyArrowEnemyAttack() { return enemyArrowEnemyAttack; }

string Constant::getEnemySheepMove() { return enemySheepMove; }
string Constant::getEnemySheepDeath() { return enemySheepDeath; }
string Constant::getEnemySheepAttack() { return enemySheepAttack; }

string Constant::getEnemyGoblinMove() { return enemyGoblinMove; }
string Constant::getEnemyGoblinDeath() { return enemyGoblinDeath; }
string Constant::getEnemyGoblinAttack() { return enemyGoblinAttack; }

string Constant::getEnemySoldierMove() { return enemySoldierMove; }
string Constant::getEnemySoldierDeath() { return enemySoldierDeath; }
string Constant::getEnemySoldierAttack() { return enemySoldierAttack; }

string Constant::getEnemyGoblinPath() { return enemyGoblinPath; }
string Constant::getEnemySheepPath() { return enemySheepPath; }
string Constant::getEnemySoldierPath() { return enemySoldierPath; }
string Constant::getEnemyArrowPath() { return enemyArrowPath; }
string Constant::getEnemyBoobPath() { return enemyBoobPath; }
string Constant::getEnemyBossPath() { return enemyBossPath; }
string Constant::getEnemyBossAttackPath() { return enemyBossAttackPath; }
string Constant::getEnemyArrowEnemyPath(){ return enemyArrowEnemyPath; }
string Constant::getEnemyFrameName() { return enemyFrameName; }
string Constant::getEnemyAnimationName() { return enemyAnimationName; }
int Constant::getEnemyTag() { return enemyTag; }
int Constant::getEnemyArrowTag() { return enemyArrowTag; }
string Constant::getEnemyBloodBackPath() { return enemyBloodBackPath; }
string Constant::getEnemyBloodForePath() { return enemyBloodForePath; }


bitmask Constant::enemyBitmask;
bitmask Constant::getEnemyBitmask() {
	enemyBitmask.categoryBitmask = 0x000000FF;
	enemyBitmask.collisionBitmask = 0x000000FF;
	enemyBitmask.contactTestBitmask = 0x000000FF;
	enemyBitmask.group = -3;
	return enemyBitmask;
}
bitmask Constant::enemyArrowBitmask;
bitmask Constant::getEnemyArrowBitmask() {
	enemyArrowBitmask.categoryBitmask = 0x0000000F;
	enemyArrowBitmask.collisionBitmask = 0x0000000F;
	enemyArrowBitmask.contactTestBitmask = 0x000000FF;
	enemyArrowBitmask.group = -3;
	return enemyArrowBitmask;
}

//archer
string Constant::archerbodyPath = "GamePlayingScene/archer/body.png";
string Constant::archerheadPath = "GamePlayingScene/archer/head.png";
string Constant::archerhandPath = "GamePlayingScene/archer/hand.png";
string Constant::archerFrameName = "archerFrameName";
int Constant::archerTag = 20;//tag选择范围20-29
int Constant::archerhandTag = 21;
int Constant::archerheadTag = 22;
string Constant::bloodBackPath = "GamePlayingScene/archer/blood_back.png";
string Constant::bloodForePath = "GamePlayingScene/archer/blood_fore.png";

string Constant::getArcherbodyPath() { return archerbodyPath; }
string Constant::getArcherheadPath() { return archerheadPath; }
string Constant::getArcherhandPath() { return archerhandPath; }
string Constant::getArcherFrameName() { return archerFrameName; }
int Constant::getArcherTag() { return archerTag; }
int Constant::getArcherheadTag() { return archerheadTag; }
int Constant::getArcherhandTag() { return archerhandTag; }
string Constant::getBloodBackPath() { return bloodBackPath; }
string Constant::getBloodForePath() { return bloodForePath; }

bitmask Constant::archerBitmask;
bitmask Constant::getArcherBitmask() {
	archerBitmask.categoryBitmask = 0x000000FF;
	archerBitmask.collisionBitmask = 0x000000FF;
	archerBitmask.contactTestBitmask = 0x000000FF;
	archerBitmask.group = -2;
	return archerBitmask;
}

bitmask Constant::archerClimbingBitmask;
bitmask Constant::getArcherClimbingBitmask() {
	archerBitmask.categoryBitmask = 0x0000000F;
	archerBitmask.collisionBitmask = 0x0000000F;
	archerBitmask.contactTestBitmask = 0x000000FF;
	archerBitmask.group = -2;
	return archerBitmask;
}

int Constant::archerMoveLeftActionTag = 23;
int Constant::getArcherMoveLeftActionTag() { return archerMoveLeftActionTag; }
int Constant::archerMoveRightActionTag = 24;
int Constant::getArcherMoveRightActionTag() { return archerMoveRightActionTag; }
int Constant::archerClimbUpActionTag = 25;
int Constant::getArcherClimbUpActionTag() { return archerClimbUpActionTag; }
int Constant::archerClimbDownActionTag = 26;
int Constant::getArcherClimbDownActionTag() { return archerClimbDownActionTag; }


//edge
int Constant::edge1Tag = 30;//tag选择范围30-39
int Constant::getEdge1Tag() { return edge1Tag; }

int Constant::edge2Tag = 31;
int Constant::getEdge2Tag() { return edge2Tag; }

int Constant::ropeTag = 32;
int Constant::getRopeTag() { return ropeTag; }

bitmask Constant::edge1Bitmask;
bitmask Constant::getEdge1Bitmask(){
	edge1Bitmask.categoryBitmask = 0x000000F0;
	edge1Bitmask.collisionBitmask = 0x000000F0;
	edge1Bitmask.contactTestBitmask = 0x000000FF;
	edge1Bitmask.group = -1;
	return edge1Bitmask;
}

bitmask Constant::edge2Bitmask;
bitmask Constant::getEdge2Bitmask() {
	edge2Bitmask.categoryBitmask = 0x0000000F;
	edge2Bitmask.collisionBitmask = 0x0000000F;
	edge2Bitmask.contactTestBitmask = 0x000000FF;
	edge2Bitmask.group = -1;
	return edge2Bitmask;
}

bitmask Constant::ropeBitmask;
bitmask Constant::getRopeBitmask() {
	ropeBitmask.categoryBitmask = 0x000000FF;
	ropeBitmask.collisionBitmask = 0x00000000;
	ropeBitmask.contactTestBitmask = 0x000000FF;
	ropeBitmask.group = 0;
	return ropeBitmask;
}


//iterm
string Constant::itermBallPath = "GamePlayingScene/itermBall.png";
int Constant::itermBallTag = 50;
int Constant::itermTag = 51;
string Constant::getItermBallPath(){ return itermBallPath; };
int Constant::getItermBallTag(){ return itermBallTag; }
int Constant::getItermTag(){ return itermTag; }