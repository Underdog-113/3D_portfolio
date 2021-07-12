#include "stdafx.h"
#include "..\Header\EffectMaker_Theresa.h"
#include "Theresa.h"

CEffectMaker_Theresa::CEffectMaker_Theresa(CTheresa * pTheresa)
{
	m_pTheresa = pTheresa;
	m_pOwner = pTheresa;
}

CEffectMaker_Theresa::~CEffectMaker_Theresa()
{
}

void CEffectMaker_Theresa::CreateEffect_Attack1_1()
{
	_float3 size = _float3(0.3f, 0.2f, 0.3f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_1", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Attack1_2()
{
	_float3 size = _float3(0.3f, 0.2f, 0.3f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_1_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Attack2_1()
{
	_float3 size = _float3(0.3f, 0.2f, 0.3f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Attack2_2()
{
	_float3 size = _float3(0.3f, 0.2f, 0.3f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_2_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));

}

void CEffectMaker_Theresa::CreateEffect_Attack3_1()
{
	_float3 size = _float3(0.2f, 0.25f, 0.2f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_3", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	//effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionZ(0.1f);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Attack3_2()
{
	_float3 size = _float3(0.2f, 0.25f, 0.2f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_3_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	//effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionZ(0.1f);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Attack4_1()
{
	_float3 size = _float3(0.3f, 0.2f, 0.3f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_4", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Attack4_2()
{
	_float3 size = _float3(0.3f, 0.2f, 0.3f);

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"Theresa_Att_4_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->AddPosition(m_posOffset);
	effect->GetTransform()->AddPositionY(m_pTheresa->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Charge0()
{
}

void CEffectMaker_Theresa::CreateEffect_Charge1()
{
}

void CEffectMaker_Theresa::CreateEffect_Charge2()
{
}

void CEffectMaker_Theresa::CreateEffect_Ultra_Charge()
{
	_float3 size = _float3(0.05f, 0.05f, 0.05f);

	auto effect = CreateEffect_AlphaMask(Ultra_Charge_ObjectKey, L"Ult_Charge", Ultra_Charge_Tex1Name, Ultra_Charge_Tex2Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Ultra_Trail()
{
	_float3 size = _float3(0.3f, 0.2f, 0.3f);

	auto effect = CreateEffect_Dissolve(Ultra_Trail_ObjectKey, L"Ult_Trail", Ultra_Trail_Tex1Name, Ultra_Trail_Tex2Name, Ultra_Trail_Tex3Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Ultra_Smoke()
{
	// alphamask

	_float3 size = _float3(0.05f, 0.f, 0.05f);

	auto effect = CreateEffect_AlphaMask(Ultra_Smoke_ObjectKey, L"Ult_Smoke", Ultra_Smoke_Tex1Name, Ultra_Smoke_Tex2Name);
	effect->GetTransform()->SetParent(m_pTheresa->GetTransform());
	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Theresa::CreateEffect_Ultra_Bomb()
{
	_float3 size = _float3(0.1f, 0.1f, 0.1f);

	auto effect = CreateEffect_Fire(Ultra_Boom_ObjectKey, L"Ult_Boom", Ultra_Boom_Tex1Name, Ultra_Boom_Tex2Name);

	_mat* axeMat = m_pTheresa->GetAxePivotWorldMatrix();
	_float3 offset = _float3(2.f, 0.f, 0.f);
	_float3 offsetPos;
	D3DXVec3TransformCoord(&offsetPos, &offset, axeMat);
	effect->GetTransform()->SetPosition(offsetPos);

	effect->GetTransform()->SetSize(size);

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	effect->GetTransform()->AddRotationY(m_pTheresa->GetTransform()->GetRotation().y);
}
