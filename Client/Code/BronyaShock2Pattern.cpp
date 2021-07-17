#include "stdafx.h"
#include "BronyaShock2Pattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CBronyaShock2Pattern::CBronyaShock2Pattern()
{
	m_pAttackBallMat = new _mat;
}

CBronyaShock2Pattern::~CBronyaShock2Pattern()
{
	delete m_pAttackBallMat;
	m_pAttackBallMat = nullptr;
}

void CBronyaShock2Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 대기 상태가 끝났다면
		if (Name_IDLE == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 이동 상태로 변경
			fsm->ChangeState(Name_Run);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 대기 상태라면
		if (Name_IDLE == fsm->GetCurStateString() ||
			Name_Run == fsm->GetCurStateString())
		{
			// shock2 상태로 변경
			fsm->ChangeState(Name_Shock_2);
			m_onAtkBall = false;
			m_offAtkBall = false;
			return;
		}
	}

	/************************* Running */
	// 내가 상대에게 다가가고 있다면
	if (Name_Run == fsm->GetCurStateString())
	{
		_float3 dir = tPos - mPos;

		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT * 18.f;
		pOwner->GetTransform()->SetPosition(mPos);
	}

	/************************* Shock2 End */
	// 내가 shock1 상태가 끝났다면
	if (Name_Shock_2 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}

	/************************* AttackBall */
	// 내가 공격 상태고, 적절할 때 어택볼 숨기기
	if (Name_Shock_2 == fsm->GetCurStateString() &&
		0.75f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_offAtkBall)
	{
		static_cast<CMB_Bronya*>(pOwner)->UnActiveAttackBall();
		m_offAtkBall = true;
	}
	// 내가 공격 상태고, 적절할 때 어택볼 생성
	else if (Name_Shock_2 == fsm->GetCurStateString() &&
		0.7f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onAtkBall)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_L_Forearm")->CombinedTransformMatrix;
		static_cast<CMB_Bronya*>(pOwner)->GetAttackBall()->SetOffset(_float3(0.8f, 0.f, -0.3f));
		static_cast<CMB_Bronya*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, m_pAttackBallMat, 1.8f);
		m_onAtkBall = true;
	}

	if (true == m_onAtkBall)
	{
		GetRHandMat(pOwner, m_pAttackBallMat);
	}
} 

SP(CBronyaShock2Pattern) CBronyaShock2Pattern::Create()
{
	SP(CBronyaShock2Pattern) spInstance(new CBronyaShock2Pattern, Engine::SmartDeleter<CBronyaShock2Pattern>);

	return spInstance;
}

void CBronyaShock2Pattern::GetRHandMat(Engine::CObject * pOwner, _mat * pAtkBall)
{
	_mat combMat = *m_pRHand;
	_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	*pAtkBall = combMat * pOwner->GetTransform()->GetWorldMatrix();
}
