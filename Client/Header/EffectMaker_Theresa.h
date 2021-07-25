#pragma once
#include "EffectMaker.h"


#define AttackTrail_ObjectKey	L"Theresa_Trail"
#define AttackTrail_Tex1Name	L"Tornado_3"
#define AttackTrail_Tex2Name	L"Tornado_3"
#define AttackTrail_Tex3Name	L"yun01"

#define Ultra_Charge_ObjectKey	L"Theresa_Ult_Charge"
#define Ultra_Charge_Tex1Name	L"Charge"
#define Ultra_Charge_Tex2Name	L"Charge"

#define Ultra_Trail_ObjectKey	L"Theresa_Ult_Trail"
#define Ultra_Trail_Tex1Name	L"ground_seele_urtral2"
#define Ultra_Trail_Tex2Name	L"yun01"
#define Ultra_Trail_Tex3Name	L"ground_seele_urtral2"

#define Ultra_Smoke_ObjectKey	L"Theresa_Ult_Smoke"
#define Ultra_Smoke_Tex1Name	L"Grenade_Explosion"
#define Ultra_Smoke_Tex2Name	L"Grenade_Explosion"

#define Ultra_ChargeSmoke_ObjectKey	L"Theresa_Ult_ChargeSmoke"
#define Ultra_ChargeSmoke_Tex1Name	L"fx_snowfield_fog03"
#define Ultra_ChargeSmoke_Tex2Name	L"fx_snowfield_fog03"

#define Ultra_Explosion_ObjectKey	L"Theresa_Ult_Explosion"
#define Ultra_Explosion_Tex1Name	L"Wave01"
#define Ultra_Explosion_Tex2Name	L"Wave01"
#define Ultra_Explosion_Tex3Name	L"CH11-wind01"

class CTheresa;
class CEffectMaker_Theresa :public CEffectMaker
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

	void CreateEffect_Charge0();
	void CreateEffect_Charge1();
	void CreateEffect_Charge2();

	void CreateEffect_Ultra_Charge();
	void CreateEffect_Ultra_Trail();
	void CreateEffect_Ultra_Smoke();
	void CreateEffect_Ultra_ChargeSmoke();
	void CreateEffect_Ultra_Bomb();

private:
	CTheresa* m_pTheresa;

	_float3 m_posOffset = _float3(0.f, 0.1f, 0.1f);
};
