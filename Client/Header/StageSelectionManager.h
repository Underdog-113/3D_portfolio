#pragma once
class CStageSelectionManager
{
public:
	DECLARE_SINGLETON(CStageSelectionManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);
private:

};

