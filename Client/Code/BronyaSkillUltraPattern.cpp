#include "stdafx.h"
#include "BronyaSkillUltraPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

//#include "BronyaEscapePattern.h"
//#include "BronyaShock1Pattern.h"

CBronyaSkillUltraPattern::CBronyaSkillUltraPattern()
{
}

CBronyaSkillUltraPattern::~CBronyaSkillUltraPattern()
{
}

void CBronyaSkillUltraPattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 1. 센터로 이동
	// 2. 주먹 쥐기
	// ------------- (위는 한 번만 실행)
	// 3. 랜덤 위치로 점프 이동
	// 4. 목표에게 run
	// 5. 내려찍기 or 점프 내려찍기
	// 6. 뒤로 이동


	/************************* Move Center */
	if (false == m_movedCenter)
	{
		MoveCenter(pOwner, fsm, mPos);
	}

	/************************* Ultra */
	// 내가 대기 상태가 끝났고, 센터로 이동했으면
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onShock)
	{
		// skill ultra 상태로 변경
		fsm->ChangeState(Name_Skill_Ultra);
	}
	// 내가 skill ultra 상태가 끝났다면
	else if (Name_Skill_Ultra == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 쉐이더로 사라짐
		//
		fsm->ChangeState(Name_IDLE);
		m_onShock = true;

		// 패턴을 반복할 개수를 정함 (2 ~ 4)
		m_curCnt = GetRandRange(m_minCnt, m_maxCnt);
	}
	// 내가 대기 상태가 끝났다면
	else if (true == m_onShock)
	{
		// m_curCnt가 0이 아닐 때 까지 패턴 반복
		if (0 >= m_curCnt)
		{
			switch (m_curPattern)
			{
			case 1:
				m_spShock1P->Pattern(pOwner);
				break;
			case 2:
				m_spShock2P->Pattern(pOwner);
				break;
			}
		}


		// 이동 패턴이 끝나면 아래 코드 추가
		// 이번에 Shock1을 실행할지 Shock2를 실행할지 정함,
		--m_curCnt;
		m_curPattern = GetRandRange(1, 2);

		
		for (_int i = 0; i < m_curCnt; ++i)
		{
			

			
		}
	}
} 

SP(CBronyaSkillUltraPattern) CBronyaSkillUltraPattern::Create()
{
	SP(CBronyaSkillUltraPattern) spInstance(new CBronyaSkillUltraPattern, Engine::SmartDeleter<CBronyaSkillUltraPattern>);

	return spInstance;
}

void CBronyaSkillUltraPattern::MoveCenter(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 mPos)
{
	//SP(CBronyaEscapePattern) spPattern = CBronyaEscapePattern::Create();

	//spPattern->Pattern(pOwner);

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
		m_lerpStartPos = mPos;
		m_lerpEndPos = _float3(0.f, mPos.y, 0.f);
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
		m_movedCenter = true;
	}
}

void CBronyaSkillUltraPattern::EscapeBack(Engine::CObject * pOwner, SP(CFSM_BronyaC) spFSM)
{

}
