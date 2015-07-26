using namespace std;
#include<string>

class Constant{
public:
	static string getArcherPath();
	static string getEnemyPath();
	static string getArrowPath();
	static string getBackgroundPath();
	static string getProcessBar1Path();
	static string getProcessBar2Path();
	static string getFuturaPath();
	static string getEnemySoldierPath();
	static string getEnemyGoblinPath();
	static string getEnemyArrowEnemyPath();

	static string getArcherbodyPath();
	static string getArcherhandPath();
	static string getArcherheadPath();
	static string getplayerarrowFrameName();
	static string getplayerarrowPath();

	static string getArcherFrameName();
	static string getEnemyFrameName();
	static string getEnemyAnimationName();

	static int getArcherTag();
	static int getGroundTag();
	static int getArrowTag();
	static int getEnemyTag();
	static int getEnemyTag1();
	static int getEnemyTag2();
	static int getEnemyTag3();

	static float getTimeLimit();


	static int getArcherheadTag();

	static int getArcherhandTag();

private:
	static Constant* constant;

	static string archerPath;
	static string enemyPath;
	static string arrowPath;
	static string backgroundPath;
	static string processBar1Path;
	static string processBar2Path;
	static string futuraPath;
	static string enemyGoblinPath;
	static string enemySoldierPath;
	static string enemyArrowEnemyPath;

	static string archerFrameName;
	static string enemyFrameName;
	static string enemyAnimationName;

	static int archerTag;
	static int groundTag;
	static int arrowTag;
	static int enemyTag;
	static int enemyTag1;
	static int enemyTag2;
	static int enemyTag3;

	static float timeLimit;


	static string archerheadPath;
	static string archerhandPath;
	static string archerbodyPath;
	static string playerarrowPath;
	static string playerarrowFrameName;
	static int archerhandTag;
	static int archerheadTag;
};
