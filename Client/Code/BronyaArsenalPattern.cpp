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

	// 1. ���ͷ� escape
	// 2. �������� escape
	// 3. ���� ����

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
	// ���� ��� ���°� ������, corner�� �̵�������
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onArsenal)
	{
		// Arsenal Charge ���·� ����
		fsm->ChangeState(Name_Arsenal_Charge);
	}
	// ���� Arsenal Charge ���°� �����ٸ�
	else if (Name_Arsenal_Charge == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// Arsenal Loop ���·� ����
		fsm->ChangeState(Name_Arsenal_Loop);
		m_atkReady = false;
	}
	// ���� Arsenal Loop�� ������, ��Ÿ�ӵ� �����ٸ�
	else if (Name_Arsenal_Loop == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_atkReady)
	{
		// Arsenal End ���·� ����
		fsm->ChangeState(Name_Arsenal_End);
	}
	// ���� Arsenal End ���°� �����ٸ�
	else if (Name_Arsenal_End == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
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
		m_lerpStartPos = monPos;
		m_lerpEndPos = _float3(endPos);
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
		moved = true;
	}
}
