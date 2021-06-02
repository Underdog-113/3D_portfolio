#ifndef UIMANAGER_H
#define UIMANAGER_H

class CUiManager
{
	DECLARE_SINGLETON(CUiManager)
private:

public:
	CUiManager();
	~CUiManager();

	void OnDestroy();
};

#endif // !UIMANAGER_H