#include "stdafx.h"
#include "..\Header\MO_Sickle.h"

#include "FSM_SickleC.h"
#include "PatternMachineC.h"

#include "AttackBall.h"

_uint CMO_Sickle::m_s_uniqueID = 0;

CMO_Sickle::CMO_Sickle()
{
}

CMO_Sickle::~CMO_Sickle()
{
	OnDestroy();
}

SP(Engine::CObject) CMO_Sickle::MakeClone(void)
{
	SP(CMO_Sickle) spClone(new CMO_Sickle, Engine::SmartDeleter<CMO_Sickle>);
	__super::InitClone(spClone);

	spClone->m_spTransform = spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spMesh = spClone->GetComponent<Engine::CMeshC>();
	spClone->m_spGraphics = spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spShader = spClone->GetComponent<Engine::CShaderC>();
	spClone->m_spTexture = spClone->GetComponent<Engine::CTextureC>();
	
	spClone->m_spRigidBody = spClone->GetComponent<Engine::CRigidBodyC>();
	spClone->m_spCollision = spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spDebug = spClone->GetComponent<Engine::CDebugC>();

	return spClone;
}

void CMO_Sickle::Awake(void)
{
	__super::Awake();

	m_spStateMachine = AddComponent<CFSM_SickleC>();
}

void CMO_Sickle::Start(void)
{
	__super::Start();

	m_spTransform->SetSize(1.7f, 1.7f, 1.7f);
	m_spTransform->SetRotationY(D3DXToRadian(90));

	m_spMesh->OnRootMotion();

	BaseStat stat;
	stat.SetBaseHp(217.f);
	stat.SetBaseAtk(36.f);
	stat.SetBaseDef(12.f);

	stat.SetGrowHp(6.f);
	stat.SetGrowAtk(1.5f);
	stat.SetGrowDef(0.5f);

	//stat.SetType(BaseStat::Mecha);
	m_pStat->SetupStatus(&stat);

	m_pAttackBall = std::dynamic_pointer_cast<CAttackBall>(m_pScene->GetObjectFactory()->AddClone(L"AttackBall", true)).get();
	m_pAttackBall->GetTransform()->SetSize(13.f, 13.f, 13.f);
	m_pAttackBall->SetOffset(_float3(0, 1, 0));
	m_pAttackBall->SetOwner(this);
	
	FindRightHand();
}

void CMO_Sickle::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CMO_Sickle::Update(void)
{
	__super::Update();

	UpdatePivotMatrices();
}

void CMO_Sickle::LateUpdate(void)
{
	__super::LateUpdate();
	
}


void CMO_Sickle::PreRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PreRender(m_spGraphics, pEffect);
}


void CMO_Sickle::Render(LPD3DXEFFECT pEffect)
{
	m_spMesh->Render(m_spGraphics, pEffect);
}


void CMO_Sickle::PostRender(LPD3DXEFFECT pEffect)
{
	m_spMesh->PostRender(m_spGraphics, pEffect);
}

void CMO_Sickle::OnDestroy(void)
{
	delete m_pRightHand_World;

	__super::OnDestroy();
}

void CMO_Sickle::OnEnable(void)
{
	__super::OnEnable();
}

void CMO_Sickle::OnDisable(void)
{
	__super::OnDisable();
}

void CMO_Sickle::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}

void CMO_Sickle::ApplyHitInfo(HitInfo info)
{
	// attack strength
	switch (info.GetStrengthType())
	{
	case HitInfo::Str_Damage:
		break;
	case HitInfo::Str_Low:
		this->GetComponent<CPatternMachineC>()->SetOnHitL(true);
		break;
	case HitInfo::Str_High:
		this->GetComponent<CPatternMachineC>()->SetOnHitH(true);
		break;
	case HitInfo::Str_Airborne:
		break;
	}

	// crowd control
}

void CMO_Sickle::FindRightHand()
{
	m_pRightHand_Frame = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameByName(/*"Bip001_R_Finger12"*/"Bone030");
	m_pRightHand_BoneOffset = m_spMesh->GetFirstMeshData_Dynamic()->GetFrameOffsetMatrix(/*"Bip001_R_Finger12"*/"Bone030");

	m_pRightHand_World = new _mat;
	*m_pRightHand_World = *m_pRightHand_BoneOffset * m_pRightHand_Frame->CombinedTransformMatrix;

	
	m_pAttackBall->SetParentMatrix(m_pRightHand_World);
}

void CMO_Sickle::ChaseTarget(_float3 targetPos)
{
	_float3 dir = targetPos - m_spTransform->GetPosition();
	dir.y = 0;
	D3DXVec3Normalize(&dir, &dir);

	m_spTransform->SetForward(dir);
}

void CMO_Sickle::SetStatus(BaseStat stat)
{
	if (!m_pStat)
		m_pStat = new M_Stat;

	m_pStat->SetupStatus(&stat);
}

void CMO_Sickle::UpdatePivotMatrices(void)
{
	if (m_pRightHand_World)
	{
		//_float3 offset = _float3(0.f, 0.00173f, 0.005370005f);
		//_float3 offset = _float3(0.f, 0.f, 0.f);

		//D3DXVec3Normalize(&offset, &offset);
		//_mat offsetMat;
		//D3DXMatrixIdentity(&offsetMat);
		//D3DXMatrixTranslation(&offsetMat, offset.x, offset.y, offset.z);

		//_mat combMat = offsetMat * m_pRightHand_Frame->CombinedTransformMatrix;
		//
		//_float3 rootMotionPos = m_spMesh->GetRootMotionPos();
		//combMat._41 -= rootMotionPos.x;
		////combMat._42 -= rootMotionPos.y;
		//combMat._43 -= rootMotionPos.z;

		//*m_pRightHand_World = combMat * m_spTransform->GetWorldMatrix();

		_mat combMat = m_pRightHand_Frame->CombinedTransformMatrix;
		_float3 rootMotionPos = m_spMesh->GetRootMotionPos();
		combMat._41 -= rootMotionPos.x;
		combMat._43 -= rootMotionPos.z;

		*m_pRightHand_World = combMat * m_spTransform->GetWorldMatrix();
	}
}

SP(CMO_Sickle) CMO_Sickle::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMO_Sickle) spInstance(new CMO_Sickle, Engine::SmartDeleter<CMO_Sickle>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}
