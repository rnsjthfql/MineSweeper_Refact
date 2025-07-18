#pragma once
#include "Singleton.h"

class CGameManager : public SSingleton<CGameManager>
{
	friend SSingleton<CGameManager>;

protected:
	CGameManager();
	~CGameManager();

private:
	CGameManager(CGameManager&) = delete;
	CGameManager& operator=(const CGameManager&) = delete;

public:
	int mineCount;
	void Run();
	void ShowMenu();
	void ShowWin();
	void ShowLose();
};

