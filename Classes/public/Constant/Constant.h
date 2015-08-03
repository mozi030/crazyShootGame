using namespace std;
#include<string>

class Constant{
public:

	static float getTimeLimit();

	//levelChosenScene
	static string getLevelChosenSceneBackgroundPath();
	static string getLevelChosenButton1Path();

	//gamePlayingScene
	static string getLevel1MapCsdPath();
	static string getGameEndedPath();
	static string getGameOverCsdPath();

	//arrow
	static string getArrowPath();
	static int getArrowTag();

	//processBar
	static string getProcessBar1Path();
	static string getProcessBar2Path();
	static string getFuturaPath();

	//enemy
	static string getEnemySoldierPath();
	static string getEnemyGoblinPath();
	static string getEnemyArrowPath();
	static string getEnemyArrowEnemyPath();
	static string getEnemyFrameName();
	static string getEnemyAnimationName();
	static int getEnemyTag1();
	static int getEnemyTag2();
	static int getEnemyTag3();
	static int getEnemyArrowTag();
	static string getEnemyBloodBackPath();
	static string getEnemyBloodForePath();
	static string getEnemySoldierMove();
	static string getEnemySoldierDeath();
	static string getEnemySoldierAttack();
	static string getEnemyGoblinMove();
	static string getEnemyGoblinDeath();
	static string getEnemyGoblinAttack();
	static string getEnemyArrowEnemyMove();
	static string getEnemyArrowEnemyDeath();
	static string getEnemyArrowEnemyAttack();

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

	//ground
	static int getBottomGroundTag();
	static int getLeftGroundTag();

private:

	static float timeLimit;

	//levelChosenScene
	static string levelChosenSceneBackgroundPath;
	static string levelChosenButton1Path;

	//gamePlayingScene
	static string level1MapCsdPath;
	static string gameEndedPath;
	static string gameOverCsdPath;

	//arrow
	static string arrowPath;
	static int arrowTag;

	//processBar
	static string processBar1Path;
	static string processBar2Path;
	static string futuraPath;

	//enemy
	static string enemyGoblinPath;
	static string enemySoldierPath;
	static string enemyArrowPath;
	static string enemyArrowEnemyPath;
	static string enemyFrameName;
	static string enemyAnimationName;
	static int enemyTag1;
	static int enemyTag2;
	static int enemyTag3;
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

	//ground
	static int bottomGroundTag;
	static int leftGroundTag;
};
