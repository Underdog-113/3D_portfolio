#include "stdafx.h"
#include "RobotDiePattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "AniCtrl.h"

CRobotDiePattern::CRobotDiePattern()
{
}

CRobotDiePattern::~CRobotDiePattern()
{
}

void CRobotDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	// 내가 hp가 0이 되면
	if (Name_Die != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		fsm->ChangeState(Name_Die);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.6f);
		PatternPlaySound(L"Robot_Dead.wav", pOwner);
	}
	// die 애니가 끝나면
	else if (Name_Die == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		pOwner->SetDeleteThis(true);
	}
}

SP(CRobotDiePattern) CRobotDiePattern::Create()
{
	SP(CRobotDiePattern) spInstance(new CRobotDiePattern, Engine::SmartDeleter<CRobotDiePattern>);

	return spInstance;
}