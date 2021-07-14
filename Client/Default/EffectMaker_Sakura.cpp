#include "stdafx.h"
#include "EffectMaker_Sakura.h"
#include "Sakura.h"

#define AttackTrail_ObjectKey	L"Sakura_Trail"
#define AttackTrail_Tex1Name	L"Yuan046"
#define AttackTrail_Tex2Name	L"Mei_Dodge_Line"
#define AttackTrail_Tex3Name	L"Austerity"

#define Flash_ObjKey			L""

CEffectMaker_Sakura::CEffectMaker_Sakura(CSakura * pSakura)
{
	m_pSakura = pSakura;
}

CEffectMaker_Sakura::~CEffectMaker_Sakura()
{
}

void CEffectMaker_Sakura::CreateEffect_Attack1()
{
	_float size = 1.f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_0", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
}

void CEffectMaker_Sakura::CreateEffect_Attack2()
{
	_float size = 1.f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_0", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
}

void CEffectMaker_Sakura::CreateEffect_Attack3()
{
	_float size = 1.f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_0", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
}

void CEffectMaker_Sakura::CreateEffect_Attack4()
{
	_float size = 1.f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_0", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
}

void CEffectMaker_Sakura::CreateEffect_Beam()
{
}
