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
#include "StageControlTower.h"

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

	if (Name_Escape_Out != fsm->GetCurStateString())
	{
		static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);
	}

	// �̽������� �� �ִϸ��̼��� ����Ǿ��ٸ�
	if (Name_Escape_In != fsm->GetCurStateString() &&
		Name_Escape_Out != fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// escape in ����
		fsm->ChangeState(Name_Escape_Out);
	}
	// escape in ���� �� ������ ��ġ�� �ö�Դٸ�
	else if (Name_Escape_Out == fsm->GetCurStateString() &&
		0.76f <= fsm->GetDM()->GetAniTimeline() &&
		0.f >= m_lerpCurTimer &&
		false == m_onEscape)
	{
		// �ִϸ��̼� ����
		fsm->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onEscape = true;

		// ��ǥ ��ġ ���
		_float x = (_float)GetRandRange(-20, 20);
		_float z = (_float)GetRandRange(-20, 20);

		// �̽������� ��ġ�� �̵�
		m_lerpStartPos = mPos;
		m_lerpEndPos = _float3(x, mPos.y, z);
		m_lerpCurTimer = 0.f;
	}
	// escape in ���� �� ��ǥ ��ġ�� �̵� ���̶��
	else if (Name_Escape_Out == fsm->GetCurStateString() &&
		0.05f >= fsm->GetDM()->GetAniCtrl()->GetSpeed() &&
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
	else if (Name_Escape_Out == fsm->GetCurStateString() &&
		m_lerpCurTimer <= m_lerpMaxTimer &&
		true == m_onEscape)
	{
		// �ִϸ��̼� ���
		fsm->ChangeState(Name_Escape_In);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onEscape = false;
	}
	// escape in ���°� �����ٸ�
	else if (Name_Escape_In == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
		fsm->ChangeState(Name_IDLE);
		m_lerpCurTimer = 0.f;
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}
}

SP(CBronyaEscapePattern) CBronyaEscapePattern::Create()
{
	SP(CBronyaEscapePattern) spInstance(new CBronyaEscapePattern, Engine::SmartDeleter<CBronyaEscapePattern>);

	return spInstance;
}