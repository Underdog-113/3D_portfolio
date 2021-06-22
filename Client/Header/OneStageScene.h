#ifndef ONESTAGESCENE_H
#define ONESTAGESCENE_H

#include "ClientScene.h"
class CLoading;
class CStageControlTower;
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
	void				Start_SetupUI(void);
	
	void				Start_SetupMembers(void);
	void				Create_ActorValkyrie(void);
	void				Create_SceneCamera(void);

	void				InitPrototypes(void) override;

	void				ForUITest();




private:
	CStageControlTower* m_pControlTower = nullptr;

	SP(Engine::CObject) m_spValkyrie;
	SP(Engine::CObject) m_spSpider;
};

#endif