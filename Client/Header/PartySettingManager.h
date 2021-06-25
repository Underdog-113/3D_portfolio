#pragma once
class CPartySettingManager
{
public:
	DECLARE_SINGLETON(CPartySettingManager)

public:
	void Start(Engine::CScene * pScene);
	void Update(void);
	void OnDestroy(void);
};

