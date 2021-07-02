#ifndef ONESTAGESCENE_H
#define ONESTAGESCENE_H

#include "ClientScene.h"
class CLoading;
class CStageControlTower;
class CBattleUiManager;
class CPortal;
class COneStageScene final :public CClientScene
{
private:
	explicit							COneStageScene(void);
	~COneStageScene(void);

public:
	static			CClientScene*		Create(void);
	void				Free(void) override;

	void				Awake(_int numOfLayers) override;
	void				Start(void) override;

	void				FixedUpdate(void) override;
	void				Update(void) override;
	void				LateUpdate(void) override;

	void				OnDestroy(void) override;

	void				OnEnable(void) override;
	void				OnDisable(void) override;

private:
	void				SetupFromLoader(void);
	
	void				SetupMembers(void);
	void				Create_ActorValkyrie(void);
	void				Create_SceneCamera(void);
	
	void				Create_Dummy(_float3 pos);
	void				Create_Sickle(_float3 pos);
	void				Create_Spider(_float3 pos);


	void				InitPrototypes(void) override;

	void				ForUITest();




private:
	CStageControlTower* m_pControlTower = nullptr;
	CBattleUiManager* m_pBattleUIManager = nullptr;

	SP(Engine::CObject) m_spValkyrie;

	std::vector<SP(Engine::CObject)> m_vSickle;
	std::vector<SP(Engine::CObject)> m_vSpider;
	
	SP(Engine::CObject) m_spGanesha;

	//_bool m_bossSpawn = false; // 보스 소환 스위치
	//_bool m_onBoss = false; // true : 보스 소환함 false : 보스 소환 안함

	std::vector<SP(Engine::CObject)> m_vDummy;
};

#endif