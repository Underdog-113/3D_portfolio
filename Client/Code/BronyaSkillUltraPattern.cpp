#include "stdafx.h"
#include "BronyaSkillUltraPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "Valkyrie.h" 
#include "AniCtrl.h"
#include "AttackBall.h"
#include "Bronya_Weapon.h"

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

	

	ReadyUltra(pOwner, fsm, mPos);
	PlayEscapePattern(pOwner, fsm, mPos);
	PlayShockPattern(pOwner, fsm, mPos);
	PlayStealthBackPattern(pOwner, fsm, mPos);
	PlayFastIDLEPattern(pOwner, fsm, mPos);
} 

SP(CBronyaSkillUltraPattern) CBronyaSkillUltraPattern::Create()
{
	SP(CBronyaSkillUltraPattern) spInstance(new CBronyaSkillUltraPattern, Engine::SmartDeleter<CBronyaSkillUltraPattern>);

	return spInstance;
}

void CBronyaSkillUltraPattern::ReadyUltra(Engine::CObject* pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos)
{
	static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);

	if (true == m_onUltraReady)
	{
		return;
	}

	/************************* Move Center */
	if (false == m_movedCenter)
	{
		MoveCenter(pOwner, fsm, mPos);
	}

	if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() > 0.1f && m_isReadyUltra)
	{
		static_cast<CMB_Bronya*>(pOwner)->SetAlpha(-3.3f * GET_DT);
		m_spWeapon = static_cast<CMB_Bronya*>(pOwner)->GetWeapon();
		std::dynamic_pointer_cast<CBronya_Weapon>(m_spWeapon)->SetAlpha(-3.3f * GET_DT);
	}

	/************************* Ready Ultra */
	// 내가 대기 상태가 끝났고, 센터로 이동했으면
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onShock)
	{
		// skill ultra 상태로 변경
		fsm->ChangeState(Name_Skill_Ultra);
		// 처음 시작할 shock 패턴을 정함 (1 ~ 2)
		m_curPattern = GetRandRange(1, 2);
	}
	// 내가 skill ultra 상태가 끝났다면
	else if (Name_Skill_Ultra == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 쉐이더로 사라짐

		m_isReadyUltra = true;
		//
		fsm->ChangeState(Name_IDLE);
		m_onShock = true;

		// 패턴을 반복할 개수를 정함 (2 ~ 4)
		m_curCnt = GetRandRange(m_minCnt, m_maxCnt);

		m_onUltraReady = true;
	}
}

void CBronyaSkillUltraPattern::PlayShockPattern(Engine::CObject * pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos)
{
	if (false == m_onShock)
	{
		return;
	}

	if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() <= 0.1f)
	{
		static_cast<CMB_Bronya*>(pOwner)->SetAlpha(1.f);
		m_spWeapon = static_cast<CMB_Bronya*>(pOwner)->GetWeapon();
		std::dynamic_pointer_cast<CBronya_Weapon>(m_spWeapon)->SetAlpha(1.f);
	}

	// 패턴 반복
	switch (m_curPattern)
	{
	case 1:
		m_spShock1P->Pattern(pOwner);
		break;
	case 2:
		m_spShock2P->Pattern(pOwner);
		break;
	}

	// select가 false로 바꼈다면 (shock 패턴이 끝났다면)
	if (false == pOwner->GetComponent<CPatternMachineC>()->GetOnSelect())
	{
		// 카운트를 하나 줄이고,
		--m_curCnt;
		std::cout << "========================" << std::endl;
		std::cout << "카운트 하나 줄음!" << std::endl;
		std::cout << "cnt: " << m_curCnt << std::endl;

		// 아직 카운트가 남아있다면 select를 true로 변경하여 패턴을 계속 이어나감
		if (0 < m_curCnt)
		{
			// 새로운 shock 패턴을 고름
			m_curPattern = GetRandRange(1, 2);
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(true);

			m_onStealthBack = true;
			m_onShock = false;
		}
		// 카운트를 모두 소진하였다면 (패턴이 끝났다면)
		else
		{
			m_onStealthBack = false;
			m_onEscape = false;
			m_onShock = false;
			m_onCenter = false;
			m_onUltraReady = false;
			m_movedCenter = false;
			m_isReadyUltra = false;
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);

			return;
		}
	}
}

void CBronyaSkillUltraPattern::PlayEscapePattern(Engine::CObject * pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos)
{
	if (false == m_onEscape)
	{
		return;
	}

	

	m_spEscapeBackP->Pattern(pOwner);

	if (false == pOwner->GetComponent<CPatternMachineC>()->GetOnSelect())
	{
		std::cout << "Escape!" << std::endl;
		std::cout << "========================" << std::endl;
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(true);

		m_onEscape = false;
		m_onShock = true;
	}
}

void CBronyaSkillUltraPattern::PlayStealthBackPattern(Engine::CObject * pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos)
{
	if (false == m_onStealthBack)
	{
		return;
	}

	if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() > 0.1f)
	{
		static_cast<CMB_Bronya*>(pOwner)->SetAlpha(-3.3f * GET_DT);
		m_spWeapon = static_cast<CMB_Bronya*>(pOwner)->GetWeapon();
		std::dynamic_pointer_cast<CBronya_Weapon>(m_spWeapon)->SetAlpha(-3.3f * GET_DT);
	}

	m_spStealthBackP->Pattern(pOwner);

	if (false == pOwner->GetComponent<CPatternMachineC>()->GetOnSelect())
	{
		std::cout << "StealthBack!" << std::endl;
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(true);

		m_onStealthBack = false;
		m_onEscape = true;
	}
}

void CBronyaSkillUltraPattern::PlayFastIDLEPattern(Engine::CObject * pOwner, SP(CFSM_BronyaC) fsm, _float3 mPos)
{
	if (Name_IDLE == fsm->GetCurStateString() &&
		0.7f < fsm->GetDM()->GetAniTimeline())
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
	}
	else if (Name_IDLE == fsm->GetCurStateString())
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(4.f);
	}
}

void CBronyaSkillUltraPattern::MoveCenter(Engine::CObject* pOwner, SP(CFSM_BronyaC) spFSM, _float3 mPos)
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
		false == m_onCenter)
	{
		// 애니메이션 정지
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onCenter = true;

		// 센터로 이동
		m_lerpStartPos = mPos;
		m_lerpEndPos = _float3(m_centerPos.x, mPos.y, m_centerPos.z);
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
		true == m_onCenter)
	{
		// 애니메이션 재생
		spFSM->ChangeState(Name_Escape_In);
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onCenter = false;
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