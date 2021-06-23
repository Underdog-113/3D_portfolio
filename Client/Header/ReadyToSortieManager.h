#pragma once
class CReadyToSortieManager
{
public:
	DECLARE_SINGLETON(CReadyToSortieManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);
private:
};

