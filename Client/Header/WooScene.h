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
	_float m_ganeshaAtkTime = 0.f; // ���� ��Ÿ��
	_float m_ganeshaWalkTime = 0.f; // �̵� ��Ÿ��
	_bool m_ganeshaAtkReady = true; // true : ���� ����, false : ���� �Ұ�
	_bool m_ganeshaWalkReady = true; // ture : �̵� ����, false : �̵� �Ұ�
	_bool m_ganeshaPattern0 = true;
	_bool m_ganeshaPattern1 = false;
	_bool m_ganeshaPattern2 = false;
	_float m_ganeshaAtkDis = 1.7f/*3.f*/; // �� ���� �Ÿ�
	_float m_ganeshaAtkCool = 2.f; // ���� ��Ÿ��
	_float m_ganeshaWalkCool = 0.3f; // ���� ������ �̵� �ð�

	CStageControlTower* m_pController = nullptr;
};

#endif