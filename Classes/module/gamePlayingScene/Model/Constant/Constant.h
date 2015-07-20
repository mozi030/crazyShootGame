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

	static string getArcherFrameName();
	static string getEnemyFrameName();
	static string getEnemyAnimationName();

	static int getArcherTag();
	static int getGroundTag();
	static int getArrowTag();
	static int getEnemyTag();

	static float getTimeLimit();

private:
	static Constant* constant;

	static string archerPath;
	static string enemyPath;
	static string arrowPath;
	static string backgroundPath;
	static string processBar1Path;
	static string processBar2Path;
	static string futuraPath;

	static string archerFrameName;
	static string enemyFrameName;
	static string enemyAnimationName;

	static int archerTag;
	static int groundTag;
	static int arrowTag;
	static int enemyTag;

	static float timeLimit;
};