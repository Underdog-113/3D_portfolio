#include "stdafx.h"
#include "OJ_Box.h"

_uint COJ_Box::m_s_uniqueID = 0;

COJ_Box::COJ_Box()
{
}

COJ_Box::~COJ_Box()
{
	OnDestroy();
}

SP(Engine::CObject) COJ_Box::MakeClone(void)
{
	SP(COJ_Box) spClone(new COJ_Box, Engine::SmartDeleter<COJ_Box>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	
	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();
	spClone->m_spPatternMachine = spClone->GetComponent<CPatternMachineC>();

	return spClone;
}

void COJ_Box::Awake(void)
{
	__super::Awake();

	m_spPatternMachine->AddNecessaryPatterns(CBoxBornPattern::Create(), 
											 CBoxDiePattern::Create(), 
											 CBoxBasePattern::Create(),
											 CBoxHitPattern::Create());
}

void COJ_Box::Start(void)
{
	__super::Start();

	//m_spTransform->SetSize(1.3f, 1.3f, 1.3f);
	//m_spTransform->SetRotationY(D3DXToRadian(90));

	BaseStat stat;
	stat.SetBaseHp(200.f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);
	m_pStat->SetOnSuperArmor(true);
	m_pStat->SetOnBPShield(true);

	m_pSuperArmor->SetHitL(true);
	m_pSuperArmor->SetHitH(true);
	m_pSuperArmor->SetAirborne(true);
	m_pSuperArmor->SetStun(true);
}

void COJ_Box::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void COJ_Box::Update(void)
{
	__super::Update();

	UpdatePivotMatrices();
}

void COJ_Box::LateUpdate(void)
{
	__super::LateUpdate();
}

void COJ_Box::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}

void COJ_Box::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}

void COJ_Box::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void COJ_Box::OnDestroy(void)
{
	__super::OnDestroy();
}

void COJ_Box::OnEnable(void)
{
	__super::OnEnable();
}

void COJ_Box::OnDisable(void)
{
	__super::OnDisable();
}

void COJ_Box::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void COJ_Box::ApplyHitInfo(HitInfo info)
{
	__super::ApplyHitInfo(info);

	// attack strength
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage: // hit 모션 없는 대미지
		break;
	case HitInfo::Str_Low:
		break;
	case HitInfo::Str_High:
		break;
	case HitInfo::Str_Airborne:
		break;
	}

	// crowd control
	switch (info.GetCrowdControlType())
	{
	case HitInfo::CC_None:
		break;
	case HitInfo::CC_Stun:
		break;
	case HitInfo::CC_Sakura:
		break;
	case HitInfo::CC_Airborne:
		break;
	}
}

void COJ_Box::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForwardUp(dir, UP_VECTOR);
}

void COJ_Box::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

void COJ_Box::UpdatePivotMatrices(void)
{
}

void COJ_Box::MonsterDead()
{
	GetComponent<CPatternMachineC>()->SetOnDie(true);
}

SP(COJ_Box) COJ_Box::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(COJ_Box) spInstance(new COJ_Box, Engine::SmartDeleter<COJ_Box>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
