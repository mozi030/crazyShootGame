#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;


class LoadGameScene :public cocos2d::Scene, TableViewDataSource {
private:
	int numOfCells;
public:
	CREATE_FUNC(LoadGameScene);

	virtual bool init();

	int getNumOfRecord();
	void deleteIterm();

	/**
	* a cell instance at a given index
	*
	* @param idx index to search for a cell
	* @return cell found at idx
	*/
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) {
		TableViewCell* t;
		return t;
	}
	/**
	* Returns number of cells in a given table view.
	*
	* @return number of cells
	*/
	virtual ssize_t numberOfCellsInTableView(TableView *table);
};