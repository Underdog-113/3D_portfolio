#ifndef JONGSCENE_H
#define JONGSCENE_H

#include "ClientScene.h"
class Engine::CObject;
class CStageControlTower;
class CJongScene final :public CClientScene
{
private:
	explicit							CJongScene			(void);
									   ~CJongScene			(void);

public:
	static			CClientScene*		Create				(void);
					void				Free				(void) override;

					void				Awake				(_int numOfLayers) override;
					void				Start				(void) override;
															   
					void				FixedUpdate			(void) override;
					void				Update				(void) override;
					void				LateUpdate			(void) override;	
					
					void				OnDestroy			(void) override;

					void				OnEnable			(void) override;	 
					void				OnDisable			(void) override;

private:
					void				InitPrototypes		(void) override;

					void KianaTest();
					void TheresaTest();
					void SakuraTest();

					void SetSceneCamera(SP(Engine::CObject) pTarget);

					void CollisionDummy();
					void SpiderTest();
					void SickleTest();
					void GaneshaTest();
					void RobotTest();

					void FloorTest();

					void SetupStageUI();
private:
	SP(Engine::CObject) m_spKiana;
	SP(Engine::CObject) m_spTheresa;
	SP(Engine::CObject) m_spSakura;
	Engine::CObject* m_pivot;

	SP(Engine::CObject) m_spDummy;
	SP(Engine::CObject) m_spDummy2;
	SP(Engine::CObject) m_spSickle;

	Engine::CObject* m_obj;
	Engine::CObject* m_obj1;
	Engine::CObject* m_obj2;
	Engine::CObject* m_obj3;
	Engine::CObject* m_obj4;
	int num = 0;
	int idx = 0;
private:
	CStageControlTower* m_pControlTower = nullptr;
};

#endif