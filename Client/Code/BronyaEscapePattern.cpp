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

	static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);

	// �̽��������� ��ġ
	_float3 ePos = { 0.f, 0.f, 0.f };

	// ���� �̽������� �� �ִϸ��̼��� ����Ǿ��ٸ�
	if (Name_Escape_In != fsm->GetCurStateString() &&
		Name_Escape_Out != fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// escape in ����
		fsm->ChangeState(Name_Escape_In);
	}
	// ���� escape in ���� �� ������ ��ġ�� �����ϸ�
	else if (Name_Escape_In == fsm->GetCurStateString() &&
		0.37f <= fsm->GetDM()->GetAniTimeline())
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(0.f);
	}


	/************************* Shock1 End */
	// ���� escape out ���°� �����ٸ�
	if (Name_Escape_Out == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// ��� ���·� ����
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}
}

SP(CBronyaEscapePattern) CBronyaEscapePattern::Create()
{
	SP(CBronyaEscapePattern) spInstance(new CBronyaEscapePattern, Engine::SmartDeleter<CBronyaEscapePattern>);

	return spInstance;
}