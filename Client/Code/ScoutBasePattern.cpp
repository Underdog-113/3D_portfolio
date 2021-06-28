#include "stdafx.h"
#include "ScoutBasePattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StageControlTower.h"
#include "Valkyrie.h"

CScoutBasePattern::CScoutBasePattern()
{
}

CScoutBasePattern::~CScoutBasePattern()
{
}

void CScoutBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	//CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// ���� ������ �̵��ϴ°� �ƴϸ� ����� �ٶ�
	if (Name_RUN_L != fsm->GetCurStateString() &&
		Name_RUN_R != fsm->GetCurStateString())
	{
		static_cast<CMO_Scout*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Set Move Count */
	// �̹� ���� ���� �� �� �̵��� �ٲ� ���� ����
	if (0 == m_moveCnt && true == m_walkReady)
	{
		m_moveCnt = GetRandRange(1, m_maxMoveCnt);
	}

	if (true == m_walkReady && 
		Name_IDLE != fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		return;
	}

	/************************* Choose Move Dir */
	// �̵� ��Ÿ���� �Ǿ��ٸ� ���� �̵� �ൿ���� ����
	if (true == m_walkReady &&
		Name_IDLE == fsm->GetCurStateString())
	{
		_int index = GetRandRange(2, 5);
		m_walkReady = false;

		switch (index)
		{
		case 2:
			m_curState = Name_RUN_L;
			break;
		case 3:
			m_curState = Name_RUN_R;
			break;
		case 4:
			m_curState = Name_RUN_F;
			break;
		case 5:
			m_curState = Name_RUN_B;
			break;
		}
	}

	// ���� ��� ���¸� �̵� ���·� ����
	if (Name_IDLE == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(m_curState);
		--m_moveCnt;
	}
	// ���� ������ �̵� ���̶��
	else if (Name_RUN_F == fsm->GetCurStateString())
	{
		_float3 dir = tPos - mPos;

		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// ���� �ڷ� �̵� ���̶��
	else if (Name_RUN_B == fsm->GetCurStateString())
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// ���� �������� �̵� ���̶��
	else if (Name_RUN_L == fsm->GetCurStateString())
	{
		mPos.x += GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// ���� ���������� �̵� ���̶��
	else if (Name_RUN_R == fsm->GetCurStateString())
	{
		mPos.x -= GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
}

SP(CScoutBasePattern) CScoutBasePattern::Create()
{
	SP(CScoutBasePattern) spInstance(new CScoutBasePattern, Engine::SmartDeleter<CScoutBasePattern>);

	return spInstance;
}