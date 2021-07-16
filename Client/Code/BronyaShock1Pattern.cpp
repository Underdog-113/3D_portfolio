#include "stdafx.h"
#include "BronyaShock1Pattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CBronyaShock1Pattern::CBronyaShock1Pattern()
{
	m_pAttackBallMat = new _mat;
}

CBronyaShock1Pattern::~CBronyaShock1Pattern()
{
	delete m_pAttackBallMat;
	m_pAttackBallMat = nullptr;
}

void CBronyaShock1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ��� ���°� �����ٸ�
		if (Name_IDLE == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// �̵� ���·� ����
			fsm->ChangeState(Name_Run);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� ��� ���¶��
		if (Name_IDLE == fsm->GetCurStateString() ||
			Name_Run == fsm->GetCurStateString())
		{
			// shock1 ���·� ����
			fsm->ChangeState(Name_Shock_1);
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.3f);
		}
	}

	/************************* Running */
	// ���� ��뿡�� �ٰ����� �ִٸ�
	if (Name_Run == fsm->GetCurStateString())
	{
		_float3 dir = tPos - mPos;

		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT * 18.f;
		pOwner->GetTransform()->SetPosition(mPos);
	}

	/************************* Shock1 End */
	// ���� shock1 ���°� �����ٸ�
	if (Name_Shock_1 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
		fsm->ChangeState(Name_IDLE);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		m_onAtkBall = false;
	}

	/************************* AttackBall */
	// ���� ���� ���°�, ������ �� ���ú� �����
	//if (Name_Shock_1 == fsm->GetCurStateString() &&
	//	0.47f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	static_cast<CMO_Sickle*>(pOwner)->UnActiveAttackBall();
	//}
	// ���� ���� ���°�, ������ �� ���ú� ����
	//else if (Name_Shock_1 == fsm->GetCurStateString() &&
	//	0.37f <= fsm->GetDM()->GetAniTimeline() &&
	//	false == m_onAtkBall)
	//{
	//	
	//	m_onAtkBall = true;
	//}
	if (!m_onAtkBall)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_R_Hand")->CombinedTransformMatrix;


		static_cast<CMB_Bronya*>(pOwner)->GetAttackBall()->SetOffset(_float3(1.f, 0.f, 0.f));
		static_cast<CMB_Bronya*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, m_pAttackBallMat, 0.35f);

		m_onAtkBall = true;
	}


	*m_pAttackBallMat = GetRHandMat(pOwner);

} 

SP(CBronyaShock1Pattern) CBronyaShock1Pattern::Create()
{
	SP(CBronyaShock1Pattern) spInstance(new CBronyaShock1Pattern, Engine::SmartDeleter<CBronyaShock1Pattern>);

	return spInstance;
}

_mat CBronyaShock1Pattern::GetRHandMat( Engine::CObject * pOwner)
{
	_mat combMat = *m_pRHand;
	_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	_mat realPosMat = combMat * pOwner->GetTransform()->GetWorldMatrix();

	return realPosMat;
}
