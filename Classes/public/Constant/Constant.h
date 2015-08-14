#ifndef __CONSTANT_H__
#define __CONSTANT_H__

using namespace std;
#include<string>

struct bitmask{
	int categoryBitmask; //种类
	int contactTestBitmask; //接触掩码
	int collisionBitmask; //碰撞掩码
	int group; //分组
};

class Constant{
public:

	static float getTimeLimit();

	//levelChosenScene
	static string getLevelChosenSceneBackgroundPath();
	static string getLevelChosenButton1Path();
	static string getLevelChosenButton2Path();
	static string getLevelChosenButton3Path();
	static string getLevelChosenButton4Path();
	static string getLevelChosenButton5Path();
	static string getLevelChosenButtonshopPath();

	//gamePlayingScene
	static string getLevel1MapCsdPath();
	static string getGameEndedPath();
	static string getGameOverCsdPath();

	//arrow
	static string getArrow1Path();
	static string getArrow2Path();
	static string getArrow3Path();
	static int getArrowTag();
	static int getArrow4Tag();
	static bitmask getArrowBitmask();

	//processBar
	static string getProcessBar1Path();
	static string getProcessBar2Path();
	static string getFuturaPath();

	//enemy
	static string getEnemySoldierPath();
	static string getEnemySheepPath();
	static string getEnemyGoblinPath();
	static string getEnemyArrowPath();
	static string getEnemyBoobPath();
	static string getEnemyBossPath();
	static string getEnemyBossAttackPath();
	static string getEnemyArrowEnemyPath();
	static string getEnemyFrameName();
	static string getEnemyAnimationName();
	static int getEnemyTag();
	static int getEnemyArrowTag();
	static string getEnemyBloodBackPath();
	static string getEnemyBloodForePath();
	static string getEnemySoldierMove();
	static string getEnemySoldierDeath();
	static string getEnemySoldierAttack();
	static string getEnemyGoblinMove();
	static string getEnemyGoblinDeath();
	static string getEnemyGoblinAttack();
	static string getEnemySheepMove();
	static string getEnemySheepDeath();
	static string getEnemySheepAttack();
	static string getEnemyArrowEnemyMove();
	static string getEnemyArrowEnemyDeath();
	static string getEnemyArrowEnemyAttack();
	static string getEnemyBossNormal();
	static string getEnemyBossAttack();
	static string getEnemyBossCall();
	static string getEnemyBossAddBlood();
	static string getEnemyBossAttackReal();
	static string getEnemyBossAttackCall();
	static string getEnemyBossAttackAddBlood();
	static bitmask getEnemyBitmask();
	static bitmask getEnemyArrowBitmask();

	//archer
	static string getArcherbodyPath();
	static string getArcherhandPath();
	static string getArcherheadPath();
	static string getArcherFrameName();
	static int getArcherTag();
	static int getArcherheadTag();
	static int getArcherhandTag();
	static string getBloodBackPath();
	static string getBloodForePath();
	static bitmask getArcherBitmask();
	static bitmask getArcherClimbingBitmask();
	static int getArcherMoveLeftActionTag();
	static int getArcherMoveRightActionTag();
	static int getArcherClimbUpActionTag();
	static int getArcherClimbDownActionTag();

	//ground
	static int getEdge1Tag();
	static int getEdge2Tag();
	static int getRopeTag();
	static bitmask getEdge1Bitmask();
	static bitmask getEdge2Bitmask();
	static bitmask getRopeBitmask();

	//iterm
	static string getItermBallPath();
	static int getItermBallTag();
	static int getItermTag();

private:

	static float timeLimit;

	//levelChosenScene
	static string levelChosenSceneBackgroundPath;
	static string levelChosenButton1Path;
	static string levelChosenButton2Path;
	static string levelChosenButton3Path;
	static string levelChosenButton4Path;
	static string levelChosenButton5Path;
	static string levelChosenButtonshopPath;

	//gamePlayingScene
	static string level1MapCsdPath;
	static string gameEndedPath;
	static string gameOverCsdPath;

	//arrow
	static string arrow1Path;
	static string arrow2Path;
	static string arrow3Path;
	static int arrowTag;
	static int arrow4Tag;
	static bitmask arrowBitmask;

	//processBar
	static string processBar1Path;
	static string processBar2Path;
	static string futuraPath;

	//enemy
	static string enemyGoblinPath;
	static string enemySoldierPath;
	static string enemySheepPath;
	static string enemyArrowPath;
	static string enemyBoobPath;
	static string enemyBossPath;
	static string enemyBossAttackPath;
	static string enemyArrowEnemyPath;
	static string enemyFrameName;
	static string enemyAnimationName;
	static int enemyTag;
	static int enemyArrowTag;
	static string enemyBloodBackPath;
	static string enemyBloodForePath;
	static string enemyArrowEnemyMove;
	static string enemyArrowEnemyAttack;
	static string enemyArrowEnemyDeath;
	static string enemySoldierMove;
	static string enemySoldierAttack;
	static string enemySoldierDeath;
	static string enemyGoblinMove;
	static string enemyGoblinAttack;
	static string enemyGoblinDeath;
	static string enemySheepMove;
	static string enemySheepAttack;
	static string enemySheepDeath;
	static string enemyBossNormal;
	static string enemyBossAttack;
	static string enemyBossAddBlood;
	static string enemyBossCall;
	static string enemyBossAttackCall;
	static string enemyBossAttackReal;
	static string enemyBossAttackAddBlood;
	static bitmask enemyBitmask;
	static bitmask enemyArrowBitmask;

	//archer
	static string archerFrameName;
	static int archerTag;
	static string archerheadPath;
	static string archerhandPath;
	static string archerbodyPath;
	static int archerhandTag;
	static int archerheadTag;
	static string bloodBackPath;
	static string bloodForePath;
	static bitmask archerBitmask;
	static bitmask archerClimbingBitmask;
	static int archerMoveLeftActionTag;
	static int archerMoveRightActionTag;
	static int archerClimbUpActionTag;
	static int archerClimbDownActionTag;

	//edge
	static int edge1Tag;
	static int edge2Tag;
	static int ropeTag;
	static bitmask edge1Bitmask;
	static bitmask edge2Bitmask;
	static bitmask ropeBitmask;

	//iterm
	static int itermBallTag;
	static int itermTag;
	static string itermBallPath;
};

#endif