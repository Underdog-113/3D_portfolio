#include "stdafx.h"
#include "Kiana.h"

#include "FSM_KianaC.h"
#include "ObjectFactory.h"
#include "DynamicMeshData.h"

#include "Kiana_CatPaw_Atk01.h"
#include "Kiana_CatPaw_Atk02.h"
#include "Kiana_CatPaw_Atk03.h"
#include "Kiana_CatPaw_Atk04.h"
#include "Kiana_CatPaw_Atk05.h"


CKiana::CKiana()
{
}


CKiana::~CKiana()
{
	OnDestroy();
}

SP(CKiana) CKiana::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CKiana) spInstance(new CKiana, Engine::SmartDeleter<CKiana>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CKiana::MakeClone(void)
{
	SP(CKiana) spClone(new CKiana, Engine::SmartDeleter<CKiana>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh		= spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spStateMachine	= spClone->GetComponent<CFSM_KianaC>();
	return spClone;
}

void CKiana::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_KianaC>();
}

void CKiana::Start(void)
{
	__super::Start();

	m_spMesh->OnRootMotion();
	
	//weapon
	//CreatePistol();

	//catpaw
	CreateCatPaw();

}

void CKiana::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana::Update(void)
{
	Update_WeaponTransform();

	__super::Update();

	if (m_ultraMode)
	{
		m_ultraTimer += GET_DT;
		if (m_ultraTimer > m_ultraDuration)
		{
			m_ultraMode = false;
			m_ultraTimer = 0.f;
		}
	}
}

void CKiana::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana::PreRender(void)
{
	m_spMesh->PreRender(m_spGraphics);
}

void CKiana::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana::Render(void)
{
	m_spMesh->Render(m_spGraphics);
}

void CKiana::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana::PostRender(void)
{
	m_spMesh->PostRender(m_spGraphics);
}

void CKiana::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana::OnDestroy(void)
{
	delete m_pLeftHand_World;
	delete m_pRightHand_World;
	__super::OnDestroy();
}

void CKiana::OnEnable(void)
{
	__super::OnEnable();
}

void CKiana::OnDisable(void)
{
	__super::OnDisable();
}

void CKiana::Update_WeaponTransform(void)
{
	//*m_pLeftHand_World = *m_pLeftHand_BoneOffset * m_pLeftHand_Frame->CombinedTransformMatrix;
	//*m_pRightHand_World = *m_pRightHand_BoneOffset * m_pRightHand_Frame->CombinedTransformMatrix;
}

void CKiana::CreatePistol(void)
{
	m_spWeapon_Left = GetScene()->ADD_CLONE(L"Kiana_Pistol_USP45", false, (_uint)ELayerID::Player, L"Weapon_Left");
	m_spWeapon_Left->GetTransform()->SetParent(m_spTransform);

	Engine::CDynamicMeshData* pDM = m_spMesh->GetFirstMeshData_Dynamic();
	
	m_pLeftHand_Frame = pDM->GetFrameByName("Bip001_Prop2");
	m_pLeftHand_BoneOffset = pDM->GetFrameOffsetMatrix("Bip001_Prop2");
	m_pLeftHand_World = new _mat;
	*m_pLeftHand_World = *m_pLeftHand_BoneOffset * m_pLeftHand_Frame->CombinedTransformMatrix;

	m_spWeapon_Left->GetTransform()->SetOffsetMatrix(m_pLeftHand_World);

	m_spWeapon_Right = GetScene()->ADD_CLONE(L"Kiana_Pistol_USP45", false, (_uint)ELayerID::Player, L"Weapon_Right");
	m_spWeapon_Right->GetTransform()->SetParent(m_spTransform);

	m_pRightHand_Frame = pDM->GetFrameByName("Bip001_Prop1");
	m_pRightHand_BoneOffset = pDM->GetFrameOffsetMatrix("Bip001_Prop1");
	m_pRightHand_World = new _mat;
	*m_pRightHand_World = *m_pRightHand_BoneOffset * m_pRightHand_Frame->CombinedTransformMatrix;

	m_spWeapon_Right->GetTransform()->SetOffsetMatrix(m_pRightHand_World);
}

void CKiana::CreateCatPaw(void)
{
	m_spCatPaw_Atk01 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk01", false, (_uint)ELayerID::Player, L"CatPaw_Atk01");
	m_spCatPaw_Atk01->SetIsEnabled(false);
	m_spCatPaw_Atk02 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk02", false, (_uint)ELayerID::Player, L"CatPaw_Atk02");
	m_spCatPaw_Atk02->SetIsEnabled(false);
	m_spCatPaw_Atk03 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk03", false, (_uint)ELayerID::Player, L"CatPaw_Atk03");
	m_spCatPaw_Atk03->SetIsEnabled(false);
	m_spCatPaw_Atk04 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk04", false, (_uint)ELayerID::Player, L"CatPaw_Atk04");
	m_spCatPaw_Atk04->SetIsEnabled(false);
	m_spCatPaw_Atk05 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk05", false, (_uint)ELayerID::Player, L"CatPaw_Atk05");
	m_spCatPaw_Atk05->SetIsEnabled(false);
}

void CKiana::SetBasicName(void)
{
}

void CKiana::UltraAtk(UltraAttack index)
{
	if (!m_ultraMode)
		return;

	switch (index)
	{
	case CKiana::ATK01:
		m_spCatPaw_Atk01->SetIsEnabled(true);
		break;
	case CKiana::ATK02:
		m_spCatPaw_Atk02->SetIsEnabled(true);
		break;
	case CKiana::ATK03:
		m_spCatPaw_Atk03->SetIsEnabled(true);
		break;
	case CKiana::ATK04:
		m_spCatPaw_Atk04->SetIsEnabled(true);
		break;
	case CKiana::ATK05:
		m_spCatPaw_Atk05->SetIsEnabled(true);
		break;
	case CKiana::Branch_ATK01:
		break;
	case CKiana::Branch_ATK02:
		break;
	case CKiana::QTE_ATK:
		break;
	default:
		break;
	}
}