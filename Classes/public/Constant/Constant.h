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

	//arrow
	static string getArrowPath();
	static int getArrowTag();
	static int getEnemyArrowTag();

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

private:

	static float timeLimit;

	//levelChosenScene
	static string levelChosenSceneBackgroundPath;
	static string levelChosenButton1Path;

	//gamePlayingScene
	static string level1MapCsdPath;
	static string gameEndedPath;

	//arrow
	static string arrowPath;
	static int arrowTag;
	static int enemyArrowTag;

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
};
