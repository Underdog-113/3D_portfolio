#include "stdafx.h"
#include "Kiana.h"

#include "FSM_KianaC.h"
#include "ObjectFactory.h"
#include "DynamicMeshData.h"
#include "StateMachineC.h"
#include "AniCtrl.h"

#include "StageControlTower.h"
#include "UILinker.h"

#include "Kiana_CatPaw_Atk01.h"
#include "Kiana_CatPaw_Atk02.h"
#include "Kiana_CatPaw_Atk03.h"
#include "Kiana_CatPaw_Atk04.h"
#include "Kiana_CatPaw_Atk05.h"

#include "Kiana_Pistol.h"

#include "AttackBall.h"
#include "FSMDefine_Kiana.h"

#include "BattleUiManager.h"
#include "DamageObjectPool.h"

_uint CKiana::m_s_uniqueID = 0;

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
	// status
	V_WarshipStat stat;

	m_pStat = new V_Kiana_Stat;
	m_pStat->SetUltraCost(75.f);
	m_pStat->SetupStatus(&stat);

	__super::Start();
	m_spDebug = AddComponent<Engine::CDebugC>();

	m_spTransform->SetSize(0.45f, 0.45f, 0.45f);

	m_spMesh->OnRootMotion();

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->GetTransform()->SetSize(3.f, 3.f, 3.f);
	m_pAttackBall->SetOwner(this);

	CreatePivotMatrix(&m_pLeftToe_World, &m_pLeftToe_Frame, "Bip001_L_Toe0");
	CreatePivotMatrix(&m_pRightToe_World, &m_pRightToe_Frame, "Bip001_R_Toe0");
	CreatePivotMatrix(&m_pRightHand_World, &m_pRightHand_Frame, "Bip001_R_Hand");
	CreatePivotMatrix(&m_pLeftHand_World, &m_pLeftHand_Frame, "Bip001_L_Hand");
	
	//weapon
	//CreatePistol();

	//catpaw
	CreateCatPaw();

	if (m_isWait)
	{
		__super::FixedUpdate();
		__super::Update();
		__super::LateUpdate();
		SetIsEnabled(false);
	}


	m_yDefaultOffset = 0.43f;	// 변경금지
}

void CKiana::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CKiana::Update(void)
{
	__super::Update();

	UpdatePivotMatrix(m_pLeftToe_World, m_pLeftToe_Frame);
	UpdatePivotMatrix(m_pRightToe_World, m_pRightToe_Frame);
	UpdatePivotMatrix(m_pRightHand_World, m_pRightHand_Frame);
	UpdatePivotMatrix(m_pLeftHand_World, m_pLeftHand_Frame);

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

void CKiana::RenderPerShader(void)
{
	m_spMesh->RenderPerShader(m_spGraphics);
}

void CKiana::OnDestroy(void)
{
	delete m_pStat;

	SAFE_DELETE(m_pLeftToe_World)
	SAFE_DELETE(m_pRightToe_World)
	SAFE_DELETE(m_pLeftHand_World)
	SAFE_DELETE(m_pRightHand_World)
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

void CKiana::CreatePistol(void)
{
	m_spWeapon_Left = GetScene()->ADD_CLONE(L"Kiana_Pistol", true, (_uint)ELayerID::Player, L"Weapon_Left");
	static_cast<CKiana_Pistol*>(m_spWeapon_Left.get())->SetParentMatrix(m_pLeftHand_World);

	m_spWeapon_Right = GetScene()->ADD_CLONE(L"Kiana_Pistol", true, (_uint)ELayerID::Player, L"Weapon_Right");
	static_cast<CKiana_Pistol*>(m_spWeapon_Right.get())->SetParentMatrix(m_pRightHand_World);
}

void CKiana::CreateCatPaw(void)
{
	_float size = 0.5f;

	m_spCatPaw_Atk01 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk01", true, (_uint)ELayerID::Player, L"CatPaw_Atk01");
	m_spCatPaw_Atk01->SetIsEnabled(false);
	m_spCatPaw_Atk01->GetTransform()->SetSize(size,size,size);
	((CKiana_CatPaw_Abs*)m_spCatPaw_Atk01.get())->SetPawOffset(_float3(0.f, 0.25f, 0.f));
	m_spCatPaw_Atk01->Start();

	m_spCatPaw_Atk02 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk02", true, (_uint)ELayerID::Player, L"CatPaw_Atk02");
	m_spCatPaw_Atk02->SetIsEnabled(false);
	m_spCatPaw_Atk02->GetTransform()->SetSize(size, size, size);
	((CKiana_CatPaw_Abs*)m_spCatPaw_Atk02.get())->SetPawOffset(_float3(0.f, 0.15f, 0.f));
	m_spCatPaw_Atk02->Start();
	m_spCatPaw_Atk02->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0.9f);

	m_spCatPaw_Atk03 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk03", true, (_uint)ELayerID::Player, L"CatPaw_Atk03");
	m_spCatPaw_Atk03->SetIsEnabled(false);
	m_spCatPaw_Atk03->GetTransform()->SetSize(size, size, size);
	((CKiana_CatPaw_Abs*)m_spCatPaw_Atk03.get())->SetPawOffset(_float3(0.f, 0.15f, 0.f));
	m_spCatPaw_Atk03->Start();
	m_spCatPaw_Atk03->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0.9f);

	m_spCatPaw_Atk04 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk04", true, (_uint)ELayerID::Player, L"CatPaw_Atk04");
	m_spCatPaw_Atk04->SetIsEnabled(false);
	m_spCatPaw_Atk04->GetTransform()->SetSize(size, size, size);
	((CKiana_CatPaw_Abs*)m_spCatPaw_Atk03.get())->SetPawOffset(_float3(0.f, 0.1f, 0.f));
	m_spCatPaw_Atk04->Start();
	m_spCatPaw_Atk04->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetSpeed(0.9f);

	m_spCatPaw_Atk05 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Atk05", true, (_uint)ELayerID::Player, L"CatPaw_Atk05");
	m_spCatPaw_Atk05->SetIsEnabled(false);
	m_spCatPaw_Atk05->GetTransform()->SetSize(size,size,size);
	((CKiana_CatPaw_Abs*)m_spCatPaw_Atk05.get())->SetPawOffset(_float3(0.f, 0.15f, 0.f));
	m_spCatPaw_Atk05->Start();

	m_spCatPaw_Ring_Atk01 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Ring_Atk01", true, (_uint)ELayerID::Player, L"CatPaw_Ring_Atk01");
	m_spCatPaw_Ring_Atk01->SetIsEnabled(false);
	m_spCatPaw_Ring_Atk02 = GetScene()->ADD_CLONE(L"Kiana_CatPaw_Ring_Atk02", true, (_uint)ELayerID::Player, L"CatPaw_Ring_Atk02");
	m_spCatPaw_Ring_Atk02->SetIsEnabled(false);
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
	curSp -= 10.f * GET_PLAYER_DT;

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

void CKiana::OnCollisionEnter(Engine::_CollisionInfo ci)
{
	__super::OnCollisionEnter(ci);

}

void CKiana::OnCollisionStay(Engine::_CollisionInfo ci)
{
	__super::OnCollisionStay(ci);
}

void CKiana::OnCollisionExit(Engine::_CollisionInfo ci)
{
	__super::OnCollisionExit(ci);
}

void CKiana::ApplyHitInfo(HitInfo info)
{
	// attack strength
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage:
		m_spStateMachine->ChangeState(Name_Hit_L);
		break;
	case HitInfo::Str_Low:
		m_spStateMachine->ChangeState(Name_Hit_L);
		break;
	case HitInfo::Str_High:
		m_spStateMachine->ChangeState(Name_Hit_H);
		break;
	case HitInfo::Str_Airborne:
		m_spStateMachine->ChangeState(Name_Hit_H);
		break;
	}

	// crowd control
}

void CKiana::UltraAtk(AttackOption index)
{
	if (!m_ultraMode)
		return;

	HitInfo info;
	switch (index)
	{
	case CKiana::ATK01:
		info.SetDamageRate(2.f);
		info.SetBreakDamage(100.f);
		info.SetStrengthType(_Hit_Info::Str_Low);
		info.SetCrowdControlType(_Hit_Info::CC_None);
		static_cast<CKiana_CatPaw_Atk01*>(m_spCatPaw_Atk01.get())->SetupPaw(this, info);

		m_spCatPaw_Atk01->SetIsEnabled(true);
		break;
	case CKiana::ATK02:
		info.SetDamageRate(2.f);
		info.SetBreakDamage(100.f);
		info.SetStrengthType(_Hit_Info::Str_Low);
		info.SetCrowdControlType(_Hit_Info::CC_None);
		static_cast<CKiana_CatPaw_Atk02*>(m_spCatPaw_Atk02.get())->SetupPaw(this, info);

		m_spCatPaw_Atk02->SetIsEnabled(true);
		m_spCatPaw_Atk02->GetTransform()->UpdateWorldMatrix();

		break;
	case CKiana::ATK03:
		info.SetDamageRate(2.f);
		info.SetBreakDamage(100.f);
		info.SetStrengthType(_Hit_Info::Str_Airborne);
		info.SetCrowdControlType(_Hit_Info::CC_None);
		static_cast<CKiana_CatPaw_Atk03*>(m_spCatPaw_Atk03.get())->SetupPaw(this, info);

		m_spCatPaw_Atk03->SetIsEnabled(true);
		m_spCatPaw_Atk03->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK04:
		info.SetDamageRate(2.f);
		info.SetBreakDamage(100.f);
		info.SetStrengthType(_Hit_Info::Str_Airborne);
		info.SetCrowdControlType(_Hit_Info::CC_None);
		static_cast<CKiana_CatPaw_Atk04*>(m_spCatPaw_Atk04.get())->SetupPaw(this, info);

		m_spCatPaw_Atk04->SetIsEnabled(true);
		m_spCatPaw_Atk04->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK05:
		info.SetDamageRate(2.f);
		info.SetBreakDamage(100.f);
		info.SetStrengthType(_Hit_Info::Str_High);
		info.SetCrowdControlType(_Hit_Info::CC_None);
		static_cast<CKiana_CatPaw_Atk05*>(m_spCatPaw_Atk05.get())->SetupPaw(this, info);

		m_spCatPaw_Atk05->SetIsEnabled(true);
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
		//m_spCatPaw_Ring_Atk01->SetIsEnabled(true);

		//pos = m_spTransform->GetPosition() + m_spTransform->GetForward() * 1.3f;
		//m_spCatPaw_Ring_Atk01->GetTransform()->SetPosition(pos);
		//m_spCatPaw_Ring_Atk01->GetTransform()->AddPositionY(-0.27f);
		//m_spCatPaw_Ring_Atk01->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		//m_spCatPaw_Ring_Atk01->GetTransform()->UpdateWorldMatrix();
		break;
	case CKiana::ATK02:
		//m_spCatPaw_Ring_Atk02->SetIsEnabled(true);

		//pos = m_spTransform->GetPosition() + m_spTransform->GetForward();

		//m_spCatPaw_Ring_Atk02->GetTransform()->SetPosition(pos);
		//m_spCatPaw_Ring_Atk02->GetTransform()->AddPositionY(-0.27f);
		//m_spCatPaw_Ring_Atk02->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
		//m_spCatPaw_Ring_Atk02->GetTransform()->UpdateWorldMatrix();
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

void CKiana::UseSkill(void)
{
	_float curSp = m_pStat->GetCurSp();
	curSp -= m_pStat->GetSkillCost();

	m_pStat->SetCurSp(curSp);

	m_skillTimer = 0.f;
}

void CKiana::UseUltra(void)
{
	m_ultraTimer = 0.f;
}
