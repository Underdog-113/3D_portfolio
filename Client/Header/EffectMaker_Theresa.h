#pragma once
#include "EffectMaker.h"


#define AttackTrail_ObjectKey	L"Theresa_Trail"
#define AttackTrail_Tex1Name	L"H_Trail"
#define AttackTrail_Tex2Name	L"ground_seele_urtral"
#define AttackTrail_Tex3Name	L"ground_seele_urtral"

#define Ultra_Charge_ObjectKey	L"Theresa_Ult_Charge"
#define Ultra_Charge_Tex1Name	L"Charge"
#define Ultra_Charge_Tex2Name	L"Charge"

#define Ultra_Trail_ObjectKey	L"Theresa_Ult_Trail"
#define Ultra_Trail_Tex1Name	L"Tornado_3"
#define Ultra_Trail_Tex2Name	L"ATK_Distortion_3"

#define Ultra_Smoke_ObjectKey	L"Theresa_Ult_Smoke"
#define Ultra_Smoke_Tex1Name	L"fx_snowfield_fog03"
#define Ultra_Smoke_Tex2Name	L"fx_snowfield_fog03"
#
#define Ultra_Boom_ObjectKey	L"Theresa_Ult_Boom"
#define Ultra_Boom_Tex1Name		L"Ult_Boom"
#define Ultra_Boom_Tex2Name		L"Ult_Boom"

class CTheresa;
class CEffectMaker_Theresa :
	public CEffectMaker
{
public:
	CEffectMaker_Theresa(CTheresa* pTheresa);
	~CEffectMaker_Theresa();

	void CreateEffect_Attack1_1();
	void CreateEffect_Attack1_2();
	void CreateEffect_Attack2_1();
	void CreateEffect_Attack2_2();
	void CreateEffect_Attack3_1();
	void CreateEffect_Attack3_2();
	void CreateEffect_Attack4_1();
	void CreateEffect_Attack4_2();

	void CreateEffect_Ultra_Charge();
	void CreateEffect_Ultra_Trail();
	void CreateEffect_Ultra_Smoke();
	void CreateEffect_Ultra_Bomb();

private:
	CTheresa* m_pTheresa;
};

