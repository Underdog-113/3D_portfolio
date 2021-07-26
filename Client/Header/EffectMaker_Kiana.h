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
	void CreateEffect_Attack4(_float yPos);
	void CreateEffect_Attack5();

	void CreateEffect_BranchSign();

	void CreateEffect_Attack3_Branch();
	void CreateEffect_Attack4_Branch();

	void CreateEffect_Attack_QTE();

	void CreateEffect_Ultra();

	void CreateEffect_Claw2();
	void CreateEffect_Claw3();
	void CreateEffect_Claw4();
	void CreateEffect_Claw4_1();
	void CreateEffect_Claw4_2();
	void CreateEffect_Claw4_3();
	void CreateEffect_Claw5();

private:
	CKiana* m_pKiana;
	float m_forwardOffset = 1.f;
};


