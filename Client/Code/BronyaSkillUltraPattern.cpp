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

	// 1. ���ͷ� �̵�
	// 2. �ָ� ���
	// ------------- (���� �� ���� ����)
	// 3. ���� ��ġ�� ���� �̵�
	// 4. ��ǥ���� run
	// 5. ������� or ���� �������
	// 6. �ڷ� �̵�


	/************************* Move Center */
	if (false == m_movedCenter)
	{
		MoveCenter(pOwner, fsm, mPos);
	}

	/************************* Ultra */
	// ���� ��� ���°� ������, ���ͷ� �̵�������
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onShock)
	{
		// skill ultra ���·� ����
		fsm->ChangeState(Name_Skill_Ultra);
	}
	// ���� skill ultra ���°� �����ٸ�
	else if (Name_Skill_Ultra == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ���̴��� �����
		//
		fsm->ChangeState(Name_IDLE);
		m_onShock = true;

		// ������ �ݺ��� ������ ���� (2 ~ 4)
		m_curCnt = GetRandRange(m_minCnt, m_maxCnt);
	}
	// ���� ��� ���°� �����ٸ�
	else if (true == m_onShock)
	{
		// m_curCnt�� 0�� �ƴ� �� ���� ���� �ݺ�
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


		// �̵� ������ ������ �Ʒ� �ڵ� �߰�
		// �̹��� Shock1�� �������� Shock2�� �������� ����,
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
		false == m_onEscape)
	{
		// �ִϸ��̼� ����
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onEscape = true;

		// ���ͷ� �̵�
		m_lerpStartPos = mPos;
		m_lerpEndPos = _float3(0.f, mPos.y, 0.f);
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
		true == m_onEscape)
	{
		// �ִϸ��̼� ���
		spFSM->ChangeState(Name_Escape_In);
		spFSM->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onEscape = false;
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

void CBronyaSkillUltraPattern::EscapeBack(Engine::CObject * pOwner, SP(CFSM_BronyaC) spFSM)
{

}
