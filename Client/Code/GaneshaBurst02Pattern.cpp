#include "stdafx.h"
#include "GaneshaBurst02Pattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachine.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CGaneshaBurst02Pattern::CGaneshaBurst02Pattern()
{
}

CGaneshaBurst02Pattern::~CGaneshaBurst02Pattern()
{
}

void CGaneshaBurst02Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 burst2 상태가 아니면 상대를 추적
	if (Name_Ganesha_Burst02 != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	// 상대가 burst2 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 burst2 상태면
		if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
		}
		// 내가 대기 상태면 이동 애니로 변경
		else if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Run);
		}
		// 내가 이동 중이라면
		else if (Name_Ganesha_Run == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
	}
	// 상대가 burst2 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동 상태라면 burst2
		if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Burst02);
			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::GANESHA_JUMPBACK);
			Engine::CSoundManager::GetInstance()->StartSound(L"Ganesha_Burst02.wav", (_uint)Engine::EChannelID::GANESHA_BARRIER);
		}
	}

	// 내가 burst2 상태라면 뒤로 이동
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		m_walkReady = false;
	}
	// 내가 뒤로 이동 중이라면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// 내가 뒤로 이동이 끝났다면
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline() && true == m_walkReady)
	{
		++m_jumpCnt;

		if (2 != m_jumpCnt)
		{
			m_walkReady = false;
		}
		else
		{
			fsm->ChangeState(Name_Ganesha_StandBy);
			m_jumpCnt = 0;
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}

	// 내가 burst 상태고, 적절할 때 어택볼 숨기기
	if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && 0.65f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	}
	// 내가 burst 상태고, 적절할 때 어택볼 생성
	else if (Name_Ganesha_Burst02 == fsm->GetCurStateString() && 0.55f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();
		static_cast<CMB_Ganesha*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 3.4f);
		// 폭발 범위의 콜라이더 크기 정함
		//static_cast<Engine::CSphereCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetRadius(3.4f);
	}
}

SP(CGaneshaBurst02Pattern) CGaneshaBurst02Pattern::Create()
{
	SP(CGaneshaBurst02Pattern) spInstance(new CGaneshaBurst02Pattern, Engine::SmartDeleter<CGaneshaBurst02Pattern>);

	return spInstance;
}