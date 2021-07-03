#include "stdafx.h"
#include "BronyaEscapePattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"
#include "MathHelper.h"

CBronyaEscapePattern::CBronyaEscapePattern()
{
}

CBronyaEscapePattern::~CBronyaEscapePattern()
{
}

void CBronyaEscapePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);


	if (Name_Escape_In != fsm->GetCurStateString())
	{
		static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);
	}

	// 이스케이프할 위치
	_float3 ePos = { 0.f, 0.f, 0.f };

	// 이스케이프 외 애니메이션이 종료되었다면
	if (Name_Escape_In != fsm->GetCurStateString() &&
		Name_Escape_Out != fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// escape in 실행
		fsm->ChangeState(Name_Escape_In);
	}
	// escape in 상태 중 적정한 위치에 도달하면
	else if (Name_Escape_In == fsm->GetCurStateString() &&
		0.38f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onEscape)
	{
		// 애니메이션 정지
		fsm->GetDM()->GetAniCtrl()->SetSpeed(0.f);
		m_onEscape = true;
	}
	// escape in 상태 중이면서 이동해야 한다면
	else if (Name_Escape_In == fsm->GetCurStateString() &&
		true == m_onEscape &&
		ePos != mPos)
	{
		// 이스케이프 위치로 이동
		//CMath::CMathHelper::GetInstance()->Lerp(mPos, ePos, 1.f, );
	}
	// escape in 상태 중이면서 이동이 끝났다면
	else if (Name_Escape_In == fsm->GetCurStateString() &&
		true == m_onEscape &&
		ePos == mPos)
	{
		// 애니메이션 재생
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onEscape = false;
	}
	// escape in 상태가 끝났다면
	else if (Name_Escape_In == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onEscape)
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
	}
}

SP(CBronyaEscapePattern) CBronyaEscapePattern::Create()
{
	SP(CBronyaEscapePattern) spInstance(new CBronyaEscapePattern, Engine::SmartDeleter<CBronyaEscapePattern>);

	return spInstance;
}