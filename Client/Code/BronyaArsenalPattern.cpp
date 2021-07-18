#include "stdafx.h"
#include "BronyaArsenalPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CBronyaArsenalPattern::CBronyaArsenalPattern()
{
}

CBronyaArsenalPattern::~CBronyaArsenalPattern()
{
}

void CBronyaArsenalPattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);

	// 1. 센터로 escape
	// 2. 구석으로 escape
	// 3. 패턴 실행

	/************************* Move Center */
	if (false == m_movedCenter)
	{
		_float3 endPos = { 92.9913f, mPos.y, -4.6115f };
		EscapePos(pOwner, fsm, mPos, endPos, m_movedCenter);
	}

	/************************* Move Corner */
	if (true == m_movedCenter && false == m_movedCorner)
	{
		_float3 endPos = { 91.9447f, mPos.y, -8.55992f };
		pOwner->GetTransform()->SetRotationY(D3DXToRadian(180));
		EscapePos(pOwner, fsm, mPos, endPos, m_movedCorner);
	}

	/************************* Arsenal */
	// 내가 대기 상태가 끝났고, corner로 이동했으면
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onArsenal)
	{
		// Arsenal Charge 상태로 변경
		fsm->ChangeState(Name_Arsenal_Charge);
	}
	// 내가 Arsenal Charge 상태가 끝났다면
	else if (Name_Arsenal_Charge == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// Arsenal Loop 상태로 변경
		fsm->ChangeState(Name_Arsenal_Loop);
		m_atkReady = false;
	}
	// 내가 Arsenal Loop가 끝났고, 쿨타임도 끝났다면
	else if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_atkReady)
	{
		// Arsenal End 상태로 변경
		fsm->ChangeState(Name_Arsenal_End);
	}
	// 내가 Arsenal End 상태가 끝났다면
	else if (Name_Arsenal_End == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		m_movedCenter = m_movedCorner = false;
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}
} 

SP(CBronyaArsenalPattern) CBronyaArsenalPattern::Create()
{
	SP(CBronyaArsenalPattern) spInstance(new CBronyaArsenalPattern, Engine::SmartDeleter<CBronyaArsenalPattern>);

	return spInstance;
}

void CBronyaArsenalPattern::EscapePos(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 monPos, _float3 endPos, _bool& moved)
{
	// 이스케이프 외 애니메이션이 종료되었다면
	if (Name_Escape_In != spFSM->GetCurStateString() &&
		Name_Escape_Out != spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		// escape in 실행
		spFSM->ChangeState(Name_Escape_Out);
	}
	// escape in 상태 중 적절한 위치로 올라왔다면
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		0.76f <= spFSM->GetDM()->GetAniTimeline() &&
		0.f >= m_lerpCurTimer &&
		false == m_onEscape)
	{
		// 애니메이션 정지
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onEscape = true;

		// 센터로 이동
		m_lerpStartPos = monPos;
		m_lerpEndPos = _float3(endPos);
		m_lerpCurTimer = 0.f;
	}
	// escape in 상태 중 목표 위치로 이동 중이라면
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		0.05f >= spFSM->GetDM()->GetAniCtrl()->GetSpeed() &&
		m_lerpCurTimer < m_lerpMaxTimer)
	{
		m_lerpCurTimer += GET_DT;

		if (m_lerpCurTimer >= m_lerpMaxTimer)
		{
			m_lerpCurTimer = m_lerpMaxTimer;
		}

		_float3 currentPos = GetLerpPosition(m_lerpStartPos, m_lerpEndPos, m_lerpCurTimer, 0.3f);
		pOwner->GetTransform()->SetPosition(currentPos);
	}
	// escape in 상태 중이면서 이동이 끝났다면
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		m_lerpCurTimer <= m_lerpMaxTimer &&
		true == m_onEscape)
	{
		// 애니메이션 재생
		spFSM->ChangeState(Name_Escape_In);
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onEscape = false;
	}
	// escape in 상태가 끝났다면
	else if (Name_Escape_In == spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		spFSM->ChangeState(Name_IDLE);
		m_lerpCurTimer = 0.f;
		moved = true;
	}
}
