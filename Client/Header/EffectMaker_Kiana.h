#pragma once
#include "EffectMaker.h"

class CKiana;
class CEffectMaker_Kiana : public CEffectMaker
{
public:
	CEffectMaker_Kiana(CKiana* pKiana);
	~CEffectMaker_Kiana();

	void CreateEffect_Attack1();
	void CreateEffect_Attack2();
	void CreateEffect_Attack3();
	void CreateEffect_Attack4();
	void CreateEffect_Attack5();

	void CreateEffect_Attack3_Branch();
	void CreateEffect_Attack4_Branch();

	void CreateEffect_Ultra();

	void CreateEffect_Claw2();
	void CreateEffect_Claw3();
	void CreateEffect_Claw4();
	void CreateEffect_Claw4_1();
	void CreateEffect_Claw4_2();
	void CreateEffect_Claw4_3();
	void CreateEffect_Claw5();

	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack1, nullptr, Effect_Attack1)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack2, nullptr, Effect_Attack2)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack3, nullptr, Effect_Attack3)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack4, nullptr, Effect_Attack4)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack5, nullptr, Effect_Attack5)


	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack3_Branch, nullptr, Effect_Attack3_Branch)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Attack4_Branch, nullptr, Effect_Attack4_Branch)
	GETTOR_SETTOR(SP(Engine::CObject), m_spEffect_Ultra, nullptr, Effect_Ultra)


private:
	CKiana* m_pKiana;
};

