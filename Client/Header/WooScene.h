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

	/* Sickle */
	void SicklePattern0(); // base
	void SicklePattern1(); // attack_1
	void SicklePattern2(); // walk_back
	void SicklePattern3(); // attack_2

	/* Ganesha */
	void GaneshaPattern0(); // base
	void GaneshaPattern1();
	void GaneshaPattern2();

	void CoolTime(_float& curTime, _float maxTime, _bool& readyType); // 현재 쿨타임, 맥스 쿨타임, 쿨타임 타입

private:
	void InitPrototypes(void) override;

	Engine::CObject* m_pivot;
	SP(Engine::CObject) m_spSpider;
	SP(Engine::CObject) m_spSickle;
	SP(Engine::CObject) m_spGanesha;
	SP(Engine::CObject) m_spKiana;

	_uint m_curPatternIdx = 0;

	SP(CFSM_SickleC) m_fsm;
	
	/* for. sickle */
	_float m_sickleAtkTime = 0.f; // 공격 쿨타임
	_float m_sickleWalkTime = 0.f; // 이동 쿨타임
	_bool m_sickleAtkReady = true; // true : 공격 가능, false : 공격 불가
	_bool m_sickleWalkReady = true; // ture : 이동 가능, false : 이동 불가
	_bool m_sicklePattern0 = true;
	_bool m_sicklePattern1 = false;
	_bool m_sicklePattern2 = false;
	_bool m_sicklePattern3 = false;
	_float m_sickleAtkDis = 3.f/*3.f*/; // 낫 공격 거리
	_float m_sickleAtkCool = 2.f; // 공격 쿨타임
	_float m_sickleWalkCool = 0.3f; // 공격 끝나고 이동 시간

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