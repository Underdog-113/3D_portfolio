#include "stdafx.h"
#include "Kiana.h"

#include "FSM_KianaC.h"
#include "ObjectFactory.h"
#include "DynamicMeshData.h"

#include "StageControlTower.h"
#include "UILinker.h"

#include "Kiana_CatPaw_Atk01.h"
#include "Kiana_CatPaw_Atk02.h"
#include "Kiana_CatPaw_Atk03.h"
#include "Kiana_CatPaw_Atk04.h"
#include "Kiana_CatPaw_Atk05.h"

#include "AttackBall.h"

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


	spClone->m_spRigidBody	= spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug		= spClone->GetComponent<Engine::CDebugC>();


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
	//CreateCatPaw();

	// status
	V_WarshipStat stat;

	m_pStat = new V_Kiana_Stat;
	m_pStat->SetupStatus(&stat);
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
		UseUltraCost();

}

void CKiana::LateUpdate(void)
{
	__super::LateUpdate();
}

void CKiana::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CKiana::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CKiana::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CKiana::OnDestroy(void)
{
	delete m_pStat;

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
	//m_spWeapon_Left = GetScene()->ADD_CLONE(L"Kiana_Pistol_USP45", false, (_uint)ELayerID::Player, L"Weapon_Left");
	//m_spWeapon_Left->GetTransform()->SetParent(m_spTransform);

	//Engine::CDynamicMeshData* pDM = m_spMesh->GetFirstMeshData_Dynamic();
	//
	//m_pLeftHand_Frame = pDM->GetFrameByName("Bip001_Prop2");
	//m_pLeftHand_BoneOffset = pDM->GetFrameOffsetMatrix("Bip001_Prop2");
	//m_pLeftHand_World = new _mat;
	//*m_pLeftHand_World = *m_pLeftHand_BoneOffset * m_pLeftHand_Frame->CombinedTransformMatrix;

	//m_spWeapon_Left->GetTransform()->SetOffsetMatrix(m_pLeftHand_World);

	//m_spWeapon_Right = GetScene()->ADD_CLONE(L"Kiana_Pistol_USP45", false, (_uint)ELayerID::Player, L"Weapon_Right");
	//m_spWeapon_Right->GetTransform()->SetParent(m_spTransform);

	//m_pRightHand_Frame = pDM->GetFrameByName("Bip001_Prop1");
	//m_pRightHand_BoneOffset = pDM->GetFrameOffsetMatrix("Bip001_Prop1");
	//m_pRightHand_World = new _mat;
	//*m_pRightHand_World = *m_pRightHand_BoneOffset * m_pRightHand_Frame->CombinedTransformMatrix;

	//m_spWeapon_Right->GetTransform()->SetOffsetMatrix(m_pRightHand_World);
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

	m_spCatPaw_Ring_Atk01 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Ring_Atk01", false, (_uint)ELayerID::Player, L"CatPaw_Ring_Atk01");
	m_spCatPaw_Ring_Atk01->SetIsEnabled(false);
	//m_spCatPaw_Ring_Atk02 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Ring_Atk02", false, (_uint)ELayerID::Player, L"CatPaw_Ring_Atk02");
	//m_spCatPaw_Ring_Atk02->SetIsEnabled(false);
	//m_spCatPaw_Ring_Atk03 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Ring_Atk03", false, (_uint)ELayerID::Player, L"CatPaw_Ring_Atk03");
	//m_spCatPaw_Ring_Atk03->SetIsEnabled(false);
	//m_spCatPaw_Ring_Atk04 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Ring_Atk04", false, (_uint)ELayerID::Player, L"CatPaw_Ring_Atk04");
	//m_spCatPaw_Ring_Atk04->SetIsEnabled(false);
	//m_spCatPaw_Ring_Atk05 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Ring_Atk05", false, (_uint)ELayerID::Player, L"CatPaw_Ring_Atk05");
	//m_spCatPaw_Ring_Atk05->SetIsEnabled(false);
}

void CKiana::UseUltraCost(void)
{
	_float curSp = m_pStat->GetCurSp();
	curSp -= 10.f * GET_DT;

	if (curSp < 0.f)
	{
		m_ultraMode = false;
		curSp = 0.f;
	}

	m_pStat->SetCurSp(curSp);
}


void CKiana::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CKiana::UltraAtk(AttackOption index)
{
	if (!m_ultraMode)
		return;

	_float3 pos;
	switch (index)
	{
	case CKiana::ATK01:

		m_spCatPaw_Atk01->SetIsEnabled(true);

		pos = m_spTransform->GetPosition() + m_spTransform->GetForward();
		m_spCatPaw_Atk01->GetTransform()->SetPosition(pos);
		m_spCatPaw_Atk01->GetTransform()->AddPositionY(-0.25f);
		m_spCatPaw_Atk01->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		m_spCatPaw_Atk01->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK02:
		m_spCatPaw_Atk02->SetIsEnabled(true);

		pos = m_spTransform->GetPosition();
		m_spCatPaw_Atk02->GetTransform()->SetPosition(pos);
		m_spCatPaw_Atk02->GetTransform()->AddPositionY(-0.25f);
		m_spCatPaw_Atk02->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		m_spCatPaw_Atk02->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK03:
		m_spCatPaw_Atk03->SetIsEnabled(true);

		pos = m_spTransform->GetPosition();
		m_spCatPaw_Atk03->GetTransform()->SetPosition(pos);
		m_spCatPaw_Atk03->GetTransform()->AddPositionY(-0.25f);
		m_spCatPaw_Atk03->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		m_spCatPaw_Atk03->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK04:
		m_spCatPaw_Atk04->SetIsEnabled(true);

		pos = m_spTransform->GetPosition();
		m_spCatPaw_Atk04->GetTransform()->SetPosition(pos);
		m_spCatPaw_Atk04->GetTransform()->AddPositionY(-0.25f);
		m_spCatPaw_Atk04->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		m_spCatPaw_Atk04->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK05:
		m_spCatPaw_Atk05->SetIsEnabled(true);

		pos = m_spTransform->GetPosition();
		m_spCatPaw_Atk05->GetTransform()->SetPosition(pos);
		m_spCatPaw_Atk05->GetTransform()->AddPositionY(-0.25f);
		m_spCatPaw_Atk05->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		m_spCatPaw_Atk05->GetTransform()->UpdateWorldMatrix();
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

void CKiana::UltraAtk_Ring(AttackOption index)
{
	if (!m_ultraMode)
		return;

	_float3 pos;
	switch (index)
	{
	case CKiana::ATK01:
		m_spCatPaw_Ring_Atk01->SetIsEnabled(true);

		pos = m_spTransform->GetPosition() + m_spTransform->GetForward() * 1.3f;
		m_spCatPaw_Ring_Atk01->GetTransform()->SetPosition(pos);
		m_spCatPaw_Ring_Atk01->GetTransform()->AddPositionY(-0.27f);
		m_spCatPaw_Ring_Atk01->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		m_spCatPaw_Ring_Atk01->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK02:
		//m_spCatPaw_Atk02->SetIsEnabled(true);

		//pos = m_spTransform->GetPosition();
		//m_spCatPaw_Atk02->GetTransform()->SetPosition(pos);
		//m_spCatPaw_Atk02->GetTransform()->AddPositionY(-0.25f);
		//m_spCatPaw_Atk02->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		//m_spCatPaw_Atk02->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK03:
		//m_spCatPaw_Atk03->SetIsEnabled(true);

		//pos = m_spTransform->GetPosition();
		//m_spCatPaw_Atk03->GetTransform()->SetPosition(pos);
		//m_spCatPaw_Atk03->GetTransform()->AddPositionY(-0.25f);
		//m_spCatPaw_Atk03->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		//m_spCatPaw_Atk03->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK04:
		//m_spCatPaw_Atk04->SetIsEnabled(true);

		//pos = m_spTransform->GetPosition();
		//m_spCatPaw_Atk04->GetTransform()->SetPosition(pos);
		//m_spCatPaw_Atk04->GetTransform()->AddPositionY(-0.25f);
		//m_spCatPaw_Atk04->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		//m_spCatPaw_Atk04->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK05:
		//m_spCatPaw_Atk05->SetIsEnabled(true);

		//pos = m_spTransform->GetPosition();
		//m_spCatPaw_Atk05->GetTransform()->SetPosition(pos);
		//m_spCatPaw_Atk05->GetTransform()->AddPositionY(-0.25f);
		//m_spCatPaw_Atk05->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		//m_spCatPaw_Atk05->GetTransform()->UpdateWorldMatrix();
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

void CKiana::SetUltraMode(bool value)
{
	m_ultraMode = value;

	if (m_ultraMode)
		m_pCT->GetUILinker()->Ultra();
}

SP(Engine::CObject) CKiana::CreateEffect(std::wstring name)
{
	SP(Engine::CObject) spMeshEffect = Engine::GET_CUR_SCENE->
		GetObjectFactory()->AddClone(L"AttackTrail_Client", true, (_int)ELayerID::Effect, L"Cube0");

	//spEmptyObject->GetComponent<Engine::CMeshC>()->SetInitTex(true);
	spMeshEffect->GetComponent<Engine::CMeshC>()->AddMeshData(name);
	spMeshEffect->GetComponent<Engine::CMeshC>()->SetisEffectMesh(true);
	spMeshEffect->GetComponent<Engine::CGraphicsC>()->SetRenderID((_int)Engine::ERenderID::AlphaBlend);
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackTrail_01");
	spMeshEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"AttackTrail_12");
	spMeshEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)Engine::EShaderID::MeshTrailShader); 

	spMeshEffect->GetTransform()->SetPosition(GetTransform()->GetPosition());
	spMeshEffect->GetTransform()->AddPositionY(GetComponent<Engine::CMeshC>()->GetHalfYOffset());
	//spMeshEffect->GetTransform()->AddRotationX(D3DXToRadian(90.f));

	return spMeshEffect;
}

void CKiana::SetEffect(SP(Engine::CObject) spEffect, AttackOption option)
{
	switch (option)
	{
	case CKiana::ATK01:
		m_spEffect_Attack1 = spEffect;
		break;
	case CKiana::ATK02:
		m_spEffect_Attack2 = spEffect;
		break;
	case CKiana::ATK03:
		m_spEffect_Attack3 = spEffect;
		break;
	case CKiana::ATK04:
		m_spEffect_Attack4 = spEffect;
		break;
	case CKiana::ATK05:
		m_spEffect_Attack5 = spEffect;
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
