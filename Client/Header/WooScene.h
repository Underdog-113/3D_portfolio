#ifndef WOOSCENE_H
#define WOOSCENE_H

#include "ClientScene.h"

class CStageControlTower;
class CFSM_AxeC;
class CFSM_SpiderC;
class CFSM_SickleC;
class CFSM_GaneshaC;

class CWooScene final :public CClientScene
{
private:
	explicit CWooScene(void);
	~CWooScene(void);

public:
	static CClientScene* Create(void);
	void Free(void) override;

	void Awake(_int numOfLayers) override;
	void Start(void) override;

	void FixedUpdate(void) override;
	void Update(void) override;
	void LateUpdate(void) override;

	void OnDestroy(void) override;

	void OnEnable(void) override;
	void OnDisable(void) override;

private:
	void InitPrototypes(void) override;
	void PlayerSetting(void);
	void TerrainSetting(void);
	void SickleSetting(void);
	void GaneshaSetting(void);
	void SpiderSetting(void);

private:
	SP(Engine::CObject) m_pivot;
	SP(Engine::CObject) m_spSpider;
	SP(Engine::CObject) m_spSickle;
	SP(Engine::CObject) m_spGanesha;
	SP(Engine::CObject) m_spKiana;

	SP(Engine::CObject) m_pivot_kiana;

	_uint m_curPatternIdx = 0;

	CStageControlTower* m_pController = nullptr;
};

#endif