class SetGameCacheController{
public:
	static SetGameCacheController* getInstance();
	void setGameCache();

	static void deleteInstance();

private:
	SetGameCacheController();
	~SetGameCacheController();
	static SetGameCacheController* gameCacheController;
};