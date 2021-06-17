#ifndef WOOSCENE_H
#define WOOSCENE_H

#include "ClientScene.h"

class CStageController;
class CFSM_AxeC;
class CFSM_SpiderC;
class CFSM_SickleC;

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
	void SicklePattern0();

	/* Axe */
	void AxePattern0();
	void AxePattern1();
	void AxePattern2();

	void PlayOnceAni(std::wstring playAni, std::wstring nextAni);
	void PlayAni(std::wstring ani);
	void EndPattern();

private:
					void				InitPrototypes		(void) override;

					Engine::CObject* m_pivot;
					SP(Engine::CObject) m_spSpider;
					SP(Engine::CObject) m_spAxe;
					SP(Engine::CObject) m_spSickle;
					SP(Engine::CObject) m_spKiana;

					_bool m_pattern1 = false;
					_bool m_pattern2 = false;

					_bool m_nextAni = false;

					_uint m_curPatternIdx = 0;
					
					SP(CFSM_SickleC) m_fsm;
					_float m_accTime = 0.f;

					CStageController* m_pController = nullptr;
};

#endif