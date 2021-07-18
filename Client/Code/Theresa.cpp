#include "stdafx.h"
#include "Theresa.h"

#include "FSM_TheresaC.h"
#include "DynamicMeshData.h"
#include "StageControlTower.h"
#include "UILinker.h"

#include "AttackBox.h"
#include "Theresa_CrossBloodyHug.h"

#include "FSMDefine_Theresa.h"

CTheresa::CTheresa()
{
}


CTheresa::~CTheresa()
{
	OnDestroy();
}

SP(CTheresa) CTheresa::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CTheresa) spInstance(new CTheresa, Engine::SmartDeleter<CTheresa>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CTheresa::MakeClone(void)
{
	SP(CTheresa) spClone(new CTheresa, Engine::SmartDeleter<CTheresa>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();

	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();

	spClone->m_spStateMachine = spClone->GetComponent<CFSM_TheresaC>();
	return spClone;
}

void CTheresa::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_TheresaC>();
}

void CTheresa::Start(void)
{
	// status
	V_WarshipStat stat;

	m_pStat = new V_Theresa_Stat;
	m_pStat->SetType(V_Stat::THERESA);
	m_pStat->SetupStatus(&stat);

	__super::Start();
	m_spDebug = AddComponent<Engine::CDebugC>();

	m_vMeshContainers = m_spMesh->GetFirstMeshData_Dynamic()->GetMeshContainers();

	Off_Axe();
	Off_Sword();

	m_spMesh->OnRootMotion();

	m_spTransform->SetSize(0.75f, 0.75f, 0.75f);

	CreatePivotMatrix(&m_pRightHand_World, &m_pRightHand_Frame, "Bip001_Prop1");
	CreatePivotMatrix(&m_pLeftHand_World, &m_pLeftHand_Frame, "Bip001_Prop2");
	CreatePivotMatrix(&m_pAxePivot_World, &m_pAxePivot_Frame, "Cross_T6_Bone019");

	CreateAttackBall(&m_pAttackBall_LeftHand);
	CreateAttackBall(&m_pAttackBall_RightHand);
	CreateAttackBall(&m_pAttackBall_Axe);
	CreateAttackBall(&m_pAttackBall_AxeStick);
	CreateAttackBall(&m_pAttackBall_AxeImpact);

	CreateCross();

	if (m_isWait)
	{
		__super::FixedUpdate();
		__super::Update();
		__super::LateUpdate();
		SetIsEnabled(false);
	}
	m_yDefaultOffset = 0.4f;	// 변경금지
}

void CTheresa::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTheresa::Update(void)
{
	__super::Update();

	UpdatePivotMatrix(m_pRightHand_World, m_pRightHand_Frame);
	UpdatePivotMatrix(m_pLeftHand_World, m_pLeftHand_Frame);
	UpdatePivotMatrix(m_pAxePivot_World, m_pAxePivot_Frame);
}

void CTheresa::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTheresa::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CTheresa::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void CTheresa::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void CTheresa::OnDestroy(void)
{
	__super::OnDestroy();

	SAFE_DELETE(m_pLeftHand_World)
	SAFE_DELETE(m_pRightHand_World)
	SAFE_DELETE(m_pAxePivot_World)

	SAFE_DELETE(m_pStat)
}

void CTheresa::OnEnable(void)
{
	__super::OnEnable();
}

void CTheresa::OnDisable(void)
{
	__super::OnDisable();
}

void CTheresa::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CTheresa::ApplyHitInfo(HitInfo info)
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
}

void CTheresa::On_Sword(void)
{
	m_vMeshContainers[Sword_0]->hide = false;
	m_vMeshContainers[Sword_1]->hide = false;
}

void CTheresa::Off_Sword(void)
{
	m_vMeshContainers[Sword_0]->hide = true;
	m_vMeshContainers[Sword_1]->hide = true;
}

void CTheresa::On_Axe(void)
{
	m_vMeshContainers[Axe_0]->hide = false;
	m_vMeshContainers[Axe_1]->hide = false;
	m_vMeshContainers[Axe_2]->hide = false;
}

void CTheresa::Off_Axe(void)
{
	m_vMeshContainers[Axe_0]->hide = true;
	m_vMeshContainers[Axe_1]->hide = true;
	m_vMeshContainers[Axe_2]->hide = true;
}

void CTheresa::SetChargeMode(bool value)
{
	m_chargeMode = value;
}


void CTheresa::UseSkill(void)
{
	_float curSp = m_pStat->GetCurSp();
	curSp -= m_pStat->GetSkillCost();

	m_pStat->SetCurSp(curSp);

	m_skillTimer = 0.f;

	//test
	m_pCrossBloodyHug->SetIsEnabled(true);
	m_pCrossBloodyHug->GetTransform()->SetPosition(m_spTransform->GetPosition() + _float3(0.f, 1.7f, 0.f));
	m_pCrossBloodyHug->GetTransform()->AddPosition(m_spTransform->GetForward() * 1.5f);
	m_pCrossBloodyHug->GetTransform()->SetRotationY(m_spTransform->GetRotation().y);
	m_pCrossBloodyHug->SetFallStartY(m_spTransform->GetPosition().y + 1.7f);
	m_pCrossBloodyHug->SetFallEndY(m_spTransform->GetPosition().y);

}

void CTheresa::UseUltra(void)
{
	_float curSp = m_pStat->GetCurSp();
	curSp -= m_pStat->GetUltraCost();

	m_pStat->SetCurSp(curSp);

	m_ultraTimer = 0.f;
}

void CTheresa::CreateCross(void)
{
	auto spCross = GetScene()->ADD_CLONE(L"Theresa_CrossBloodyHug", true, (_uint)ELayerID::Player, L"CrossBloodyHug");
	m_pCrossBloodyHug = static_cast<CTheresa_CrossBloodyHug*>(spCross.get());
	m_pCrossBloodyHug->SetIsEnabled(false);

	m_pCrossBloodyHug->GetTransform()->SetSize(0.75f, 0.75f, 0.75f);
	m_pCrossBloodyHug->SetTheresa(this);
}
