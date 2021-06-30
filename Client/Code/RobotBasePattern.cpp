#include "stdafx.h"
#include "RobotBasePattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"

CRobotBasePattern::CRobotBasePattern()
{
}

CRobotBasePattern::~CRobotBasePattern()
{
}

void CRobotBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	if (nullptr == fsm || false == fsm->GetDM())
		return;

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	if (Name_Attack_1_Left != fsm->GetCurStateString())
	{
		static_cast<CMO_Robot*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
 		// 내가 공격1 상태가 끝났다면
 		if (Name_Attack_1_Left == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
 		{
 			fsm->ChangeState(Name_Walk_Backward);
 		}
		// 내가 대기 상태가 끝났다면
		else if (Name_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Forward);
		}
		// 내가 이동 중이라면
		else if (Name_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동 중이라면
		else if (Name_Walk_Backward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동이 끝났다면
		else if (Name_Walk_Backward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			fsm->ChangeState(Name_Walk_Forward);
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태가 끝났다면
		if ((Name_Walk_Forward == fsm->GetCurStateString() ||
			Name_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Attack_1_Left);
			//PatternPlaySound(L"Sickle_Skill_0.wav", pOwner);
		}
		// 내가 공격1 상태가 끝났다면
		else if (Name_Attack_1_Left == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Backward);
			m_walkReady = false;
		}
	}

	/************************* AttackBall */
	// 내가 공격 상태고, 적절할 때 어택볼 숨기기
	if (Name_Attack_1_Left == fsm->GetCurStateString() && 0.47f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Robot*>(pOwner)->UnActiveAttackBall();
	}
	// 내가 공격 상태고, 적절할 때 어택볼 생성
	else if (Name_Attack_1_Left == fsm->GetCurStateString() && 0.37f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x / 1.7f);
		m_atkMat._43 += (m_atkDis * look.z / 1.7f);

		static_cast<CMO_Robot*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.4f);
	}
}

SP(CRobotBasePattern) CRobotBasePattern::Create()
{
	SP(CRobotBasePattern) spInstance(new CRobotBasePattern, Engine::SmartDeleter<CRobotBasePattern>);

	return spInstance;
}