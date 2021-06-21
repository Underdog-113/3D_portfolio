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
	explicit							CWooScene			(void);
									   ~CWooScene			(void);

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
	/* Spider */
	void SpiderPattern0();

	/* Ganesha */
	void GaneshaPattern0(); // base
	void GaneshaPattern1();
	void GaneshaPattern2();

private:
	void InitPrototypes(void) override;

	SP(Engine::CObject) m_pivot;
	SP(Engine::CObject) m_spSpider;
	SP(Engine::CObject) m_spSickle;
	SP(Engine::CObject) m_spGanesha;
	SP(Engine::CObject) m_spKiana;

	SP(Engine::CObject) m_pivot_kiana;

	_uint m_curPatternIdx = 0;

	SP(CFSM_SickleC) m_fsm;

	/* for. Ganesha */
	_float m_ganeshaAtkTime = 0.f; // 공격 쿨타임
	_float m_ganeshaWalkTime = 0.f; // 이동 쿨타임
	_bool m_ganeshaAtkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_ganeshaWalkReady = true; // ture : 이동 가능, false : 이동 불가
	_bool m_ganeshaPattern0 = true;
	_bool m_ganeshaPattern1 = false;
	_bool m_ganeshaPattern2 = false;
	_float m_ganeshaAtkDis = 1.7f/*3.f*/; // 낫 공격 거리
	_float m_ganeshaAtkCool = 2.f; // 공격 쿨타임
	_float m_ganeshaWalkCool = 0.3f; // 공격 끝나고 이동 시간

	CStageControlTower* m_pController = nullptr;
};

#endif