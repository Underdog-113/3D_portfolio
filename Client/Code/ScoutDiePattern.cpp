#include "stdafx.h"
#include "ScoutDiePattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CScoutDiePattern::CScoutDiePattern()
{
}

CScoutDiePattern::~CScoutDiePattern()
{
}

void CScoutDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	// ���� hp�� 0�� �Ǹ�
	if (Name_DIE != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		fsm->ChangeState(Name_DIE);
	}
	// die �ִϰ� ������
	else if (Name_DIE == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
	{
		for (_uint i = 0; i < 20; ++i)
		{
			SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MonsterDieParticle", true, (_uint)Engine::ELayerID::Effect);
			spObj->GetTransform()->SetPosition(pOwner->GetTransform()->GetPosition());
			spObj->GetTransform()->AddPositionY(0.5f);
		}
		PatternPlaySound(L"Scout_Dead.wav", pOwner);

		pOwner->SetDeleteThis(true);
	}
}

SP(CScoutDiePattern) CScoutDiePattern::Create()
{
	SP(CScoutDiePattern) spInstance(new CScoutDiePattern, Engine::SmartDeleter<CScoutDiePattern>);

	return spInstance;
}