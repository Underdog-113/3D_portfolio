#ifndef TRAPOBJECT_H
#define TRAPOBJECT_H

#include "Object.h"

class CTrapObject final : public Engine::CObject
{
	SMART_DELETER_REGISTER
private:
	explicit						CTrapObject			(void);
								   ~CTrapObject			(void);

public:
	static		SP(CTrapObject)		Create				(_bool isStatic, Engine::CScene* pScene);

				SP(Engine::CObject)	MakeClone			(void) override;
		
				void				Awake				(void) override;
				void				Start				(void) override;
		
				void				FixedUpdate			(void) override;
				void				Update				(void) override;
				void				LateUpdate			(void) override;
		
				void				PreRender			(LPD3DXEFFECT pEffect) override;
				void				Render				(LPD3DXEFFECT pEffect) override;
				void				PostRender			(LPD3DXEFFECT pEffect) override;

				void				OnDestroy			(void) override;
		
				void				OnEnable			(void) override;
				void				OnDisable			(void) override;
				void				SetBasicName		(void) override;

private:
				void				TrapAnimation		(void);
				void				ActiveAttackBall	(_float damageRate, HitInfo::Strength strength, HitInfo::CrowdControl cc, _mat* pBoneMat, _float radius);
				void				UnActiveAttackBall	(void);

private:
	static		_uint				m_s_uniqueID;

				_float3				m_initPos;
				_bool				m_onUp = true;
				_bool				m_onDown = false;
				_bool				m_onTop = true;
				_bool				m_onBottom = true;
				_float				m_accTime = 0.f;
				_float				m_maxTime = 3.f; // niddle 대기 시간
				_mat				m_atkMat;
				class CAttackBall*	m_pAttackBall = nullptr;

				GETTOR(M_Stat*,					m_pStat,		nullptr,	Stat)
				GETTOR(SP(Engine::CObject),		m_spPlate,		nullptr,	Plate)
				GETTOR(SP(Engine::CObject),		m_spNiddle,		nullptr,	Niddle)
				GETTOR(SP(Engine::CObject),		m_spTop,		nullptr,	Top)
				GETTOR(SP(Engine::CObject),		m_spBottom,		nullptr,	Bottom)
};
#endif