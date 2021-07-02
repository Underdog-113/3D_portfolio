#include "stdafx.h"
#include "..\Header\EffectMaker_Kiana.h"
#include "Kiana.h"

#define AttackTrail_ObjectKey	L"Kiana_Trail"
#define AttackTrail_Tex1Name	L"K_Trail"
#define AttackTrail_Tex2Name	L"explosionpoint1"
#define AttackTrail_Tex3Name	L"Ability_aura"

#define UltraTrail_ObjectKey	L"Kiana_Ult_Trail"
#define UltraTrail_Tex1Name		L"Kiana_CatPaw_Trail"
#define UltraTrail_Tex2Name		L"explosionpoint1"
#define UltraTrail_Tex3Name		L"Ability_aura"

CEffectMaker_Kiana::CEffectMaker_Kiana(CKiana * pKiana)
{
	m_pKiana = pKiana;
	m_pOwner = pKiana;
}


CEffectMaker_Kiana::~CEffectMaker_Kiana()
{
}

void CEffectMaker_Kiana::CreateEffect_Attack1()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_0", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pKiana->GetTransform());
	effect->GetTransform()->AddPositionZ(m_forwardOffset);
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));

}

void CEffectMaker_Kiana::CreateEffect_Attack2()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_1", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pKiana->GetTransform());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));


	if (m_pKiana->GetUltraMode())
	{
		CreateEffect_Claw2();
	}
}

void CEffectMaker_Kiana::CreateEffect_Attack3()
{
	_float size = 0.5f;

	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_2", AttackTrail_Tex1Name, AttackTrail_Tex2Name , AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pKiana->GetTransform());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));

	if (m_pKiana->GetUltraMode())
	{
		CreateEffect_Claw3();
	}
}

void CEffectMaker_Kiana::CreateEffect_Attack4()
{
	_float size = 0.5f;
	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_3", AttackTrail_Tex1Name, AttackTrail_Tex2Name, AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pKiana->GetTransform());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
}

void CEffectMaker_Kiana::CreateEffect_Attack5()
{
	_float size = 0.5f;
	auto effect = CreateEffect_Trail(AttackTrail_ObjectKey, L"K_Trail_4", AttackTrail_Tex1Name, AttackTrail_Tex2Name , AttackTrail_Tex3Name);
	effect->GetTransform()->SetParent(m_pKiana->GetTransform());
	effect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset() * 0.5f);
	effect->GetTransform()->SetSize(_float3(size, size, size));

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));

	if (m_pKiana->GetUltraMode())
	{
		CreateEffect_Claw5();
	}
}

void CEffectMaker_Kiana::CreateEffect_Attack3_Branch()
{
}

void CEffectMaker_Kiana::CreateEffect_Attack4_Branch()
{
}

void CEffectMaker_Kiana::CreateEffect_Ultra()
{
	_float size = 5.f;
	auto effect = CreateEffect_AlphaMask(L"Kiana_Ult_Eff", L"Ring_Ground", L"ring_ground", L"ring_ground");
	effect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	//effect->GetTransform()->AddPositionY(-m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	effect->GetTransform()->SetSize(_float3(size, size, size));

	effect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	effect->GetTransform()->AddRotationY(m_pKiana->GetTransform()->GetRotation().y);

}

void CEffectMaker_Kiana::CreateEffect_Claw2()
{
	_float size = 0.5f;
	auto clawEffect = CreateEffect_Dissolve(UltraTrail_ObjectKey, L"CatPaw_Att_1", UltraTrail_Tex1Name, UltraTrail_Tex2Name, UltraTrail_Tex3Name);
	clawEffect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	clawEffect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	clawEffect->GetTransform()->SetSize(_float3(size, size, size));

	clawEffect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	clawEffect->GetTransform()->AddRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CEffectMaker_Kiana::CreateEffect_Claw3()
{
	_float size = 0.5f;
	auto clawEffect = CreateEffect_Dissolve(UltraTrail_ObjectKey, L"CatPaw_Att_2", UltraTrail_Tex1Name, UltraTrail_Tex2Name, UltraTrail_Tex3Name);
	clawEffect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	clawEffect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	clawEffect->GetTransform()->SetSize(_float3(size, size, size));

	clawEffect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	clawEffect->GetTransform()->AddRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CEffectMaker_Kiana::CreateEffect_Claw4()
{
	CreateEffect_Claw4_1();
	CreateEffect_Claw4_2();
	CreateEffect_Claw4_3();
}


void CEffectMaker_Kiana::CreateEffect_Claw4_1()
{
	_float size = 0.5f;
	auto clawEffect = CreateEffect_Dissolve(UltraTrail_ObjectKey, L"CatPaw_Att_3_1", UltraTrail_Tex1Name, UltraTrail_Tex2Name, UltraTrail_Tex3Name);
	clawEffect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	clawEffect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	clawEffect->GetTransform()->SetSize(_float3(size, size, size));

	clawEffect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	clawEffect->GetTransform()->AddRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CEffectMaker_Kiana::CreateEffect_Claw4_2()
{
	_float size = 0.5f;
	auto clawEffect = CreateEffect_Dissolve(UltraTrail_ObjectKey, L"CatPaw_Att_3_2", UltraTrail_Tex1Name, UltraTrail_Tex2Name, UltraTrail_Tex3Name);
	clawEffect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	clawEffect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	clawEffect->GetTransform()->SetSize(_float3(size, size, size));

	clawEffect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	clawEffect->GetTransform()->AddRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CEffectMaker_Kiana::CreateEffect_Claw4_3()
{
	_float size = 0.5f;
	auto clawEffect = CreateEffect_Dissolve(UltraTrail_ObjectKey, L"CatPaw_Att_3_3", UltraTrail_Tex1Name, UltraTrail_Tex2Name, UltraTrail_Tex3Name);
	clawEffect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	clawEffect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	clawEffect->GetTransform()->SetSize(_float3(size, size, size));

	clawEffect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	clawEffect->GetTransform()->AddRotationY(m_pKiana->GetTransform()->GetRotation().y);
}

void CEffectMaker_Kiana::CreateEffect_Claw5()
{
	_float size = 0.5f;
	auto clawEffect = CreateEffect_Dissolve(UltraTrail_ObjectKey, L"CatPaw_Att_4", UltraTrail_Tex1Name, UltraTrail_Tex2Name, UltraTrail_Tex3Name);
	clawEffect->GetTransform()->SetPosition(m_pKiana->GetTransform()->GetPosition());
	clawEffect->GetTransform()->AddPositionY(m_pKiana->GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	clawEffect->GetTransform()->SetSize(_float3(size, size, size));

	clawEffect->GetTransform()->SetRotationY(D3DXToRadian(180.f));
	clawEffect->GetTransform()->AddRotationY(m_pKiana->GetTransform()->GetRotation().y);
}
