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

	// 1. ���ͷ� �̵�
	// 2. �ָ� ���
	// ------------- (���� �� ���� ����)
	// 3. ���� ��ġ�� ���� �̵�
	// 4. ��ǥ���� run
	// 5. ������� or ���� �������
	// 6. �ڷ� �̵�

	

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
	// ���� ��� ���°� ������, ���ͷ� �̵�������
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onShock)
	{
		// skill ultra ���·� ����
		fsm->ChangeState(Name_Skill_Ultra);
		// ó�� ������ shock ������ ���� (1 ~ 2)
		m_curPattern = GetRandRange(1, 2);
	}
	// ���� skill ultra ���°� �����ٸ�
	else if (Name_Skill_Ultra == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ���̴��� �����

		m_isReadyUltra = true;
		//
		fsm->ChangeState(Name_IDLE);
		m_onShock = true;

		// ������ �ݺ��� ������ ���� (2 ~ 4)
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

	// ���� �ݺ�
	switch (m_curPattern)
	{
	case 1:
		m_spShock1P->Pattern(pOwner);
		break;
	case 2:
		m_spShock2P->Pattern(pOwner);
		break;
	}

	// select�� false�� �ٲ��ٸ� (shock ������ �����ٸ�)
	if (false == pOwner->GetComponent<CPatternMachineC>()->GetOnSelect())
	{
		// ī��Ʈ�� �ϳ� ���̰�,
		--m_curCnt;
		std::cout << "========================" << std::endl;
		std::cout << "ī��Ʈ �ϳ� ����!" << std::endl;
		std::cout << "cnt: " << m_curCnt << std::endl;

		// ���� ī��Ʈ�� �����ִٸ� select�� true�� �����Ͽ� ������ ��� �̾��
		if (0 < m_curCnt)
		{
			// ���ο� shock ������ ��
			m_curPattern = GetRandRange(1, 2);
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(true);

			m_onStealthBack = true;
			m_onShock = false;
		}
		// ī��Ʈ�� ��� �����Ͽ��ٸ� (������ �����ٸ�)
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
	// �̽������� �� �ִϸ��̼��� ����Ǿ��ٸ�
	if (Name_Escape_In != spFSM->GetCurStateString() &&
		Name_Escape_Out != spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		// escape in ����
		spFSM->ChangeState(Name_Escape_Out);
	}
	// escape in ���� �� ������ ��ġ�� �ö�Դٸ�
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		0.76f <= spFSM->GetDM()->GetAniTimeline() &&
		0.f >= m_lerpCurTimer &&
		false == m_onCenter)
	{
		// �ִϸ��̼� ����
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onCenter = true;

		// ���ͷ� �̵�
		m_lerpStartPos = mPos;
		m_lerpEndPos = _float3(m_centerPos.x, mPos.y, m_centerPos.z);
		m_lerpCurTimer = 0.f;
	}
	// escape in ���� �� ��ǥ ��ġ�� �̵� ���̶��
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
	// escape in ���� ���̸鼭 �̵��� �����ٸ�
	else if (Name_Escape_Out == spFSM->GetCurStateString() &&
		m_lerpCurTimer <= m_lerpMaxTimer &&
		true == m_onCenter)
	{
		// �ִϸ��̼� ���
		spFSM->ChangeState(Name_Escape_In);
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onCenter = false;
	}
	// escape in ���°� �����ٸ�
	else if (Name_Escape_In == spFSM->GetCurStateString() &&
		spFSM->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
		spFSM->ChangeState(Name_IDLE);
		m_lerpCurTimer = 0.f;
		m_movedCenter = true;
	}
}