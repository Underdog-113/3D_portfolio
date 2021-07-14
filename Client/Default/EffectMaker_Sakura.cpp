#include "stdafx.h"
#include "EffectMaker_Sakura.h"
#include "Sakura.h"

#define AttackTrail_ObjectKey	L"Sakura_Trail"
#define AttackTrail_Tex1Name	L"Yuan046"
#define AttackTrail_Tex2Name	L"Mei_Dodge_Line"
#define AttackTrail_Tex3Name	L"Austerity"

#define Beam_ObjectKey			L"Sakura_Charge_Att"
#define Beam_Tex1Name			L"Sakura_Dodge_Line"
#define Beam_Tex2Name			L"Sakura_Dodge_Line"
#define Beam_Tex3Name			L"Sakura_Dodge_Line"

CEffectMaker_Sakura::CEffectMaker_Sakura(CSakura * pSakura)
{
	m_pSakura = pSakura;
}

CEffectMaker_Sakura::~CEffectMaker_Sakura()
{
}

void CEffectMaker_Sakura::CreateEffect_Attack1()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"SakuraAtt_1", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	//effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Sakura::CreateEffect_Attack2()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"SakuraAtt_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	//effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Sakura::CreateEffect_Attack2_2()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"SakuraAtt_2_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	//effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Sakura::CreateEffect_Attack3()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"SakuraAtt_3", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	//effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Sakura::CreateEffect_Attack4()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"SakuraAtt_4", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	//effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
}

void CEffectMaker_Sakura::CreateEffect_Attack4_2()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"SakuraAtt_4_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	//effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Sakura::CreateEffect_Attack4_3()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"SakuraAtt_4_3", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	//effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));
	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Sakura::CreateEffect_Beam()
{
	_float size = 1.f;

	auto effect = CreateEffect_Laser(Beam_ObjectKey, L"Sakura_Beam", Beam_Tex1Name, Beam_Tex2Name, Beam_Tex3Name);
	//effect->GetTransform()->SetParent(m_pSakura->GetTransform());
	effect->GetTransform()->SetPosition(m_pSakura->GetTransform()->GetPosition());
	effect->GetTransform()->AddPositionY(m_pSakura->GetComponent<Engine::CMeshC>()->GetHalfYOffset() * 1.5f);
	effect->GetTransform()->SetSize(_float3(size, size, size));

	effect->GetTransform()->SetRotationY(m_pSakura->GetTransform()->GetRotation().y);
	effect->GetTransform()->AddRotationY(D3DXToRadian(180.f));
}
