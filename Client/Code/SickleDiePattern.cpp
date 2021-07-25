#include "stdafx.h"
#include "SickleDiePattern.h"

#include "FSM_SickleC.h"
#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CSickleDiePattern::CSickleDiePattern()
{
}

CSickleDiePattern::~CSickleDiePattern()
{
}

void CSickleDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_SickleC) fsm = pOwner->GetComponent<CFSM_SickleC>();

	// 내가 hp가 0이 되면
	if (Name_Sickle_Die != fsm->GetCurStateString() && 0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		fsm->ChangeState(Name_Sickle_Die);
	}
	// die 애니가 끝나면
	else if (Name_Sickle_Die == fsm->GetCurStateString() && 0.95f <= fsm->GetDM()->GetAniTimeline())
	{
		for (_uint i = 0; i < 20; ++i)
		{
			SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"MonsterDieParticle", true, (_uint)Engine::ELayerID::Effect);
			spObj->GetTransform()->SetPosition(pOwner->GetTransform()->GetPosition());
			spObj->GetTransform()->AddPositionY(0.5f);
		}
		PatternPlaySound(L"Sickle_Dead.wav", pOwner);

		pOwner->SetDeleteThis(true);
	}
}

SP(CSickleDiePattern) CSickleDiePattern::Create()
{
	SP(CSickleDiePattern) spInstance(new CSickleDiePattern, Engine::SmartDeleter<CSickleDiePattern>);

	return spInstance;
}