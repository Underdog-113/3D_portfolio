#include "stdafx.h"
#include "BronyaBasePattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CBronyaBasePattern::CBronyaBasePattern()
{
}

CBronyaBasePattern::~CBronyaBasePattern()
{
}

void CBronyaBasePattern::Pattern(Engine::CObject* pOwner)
{
	
} 

SP(CBronyaBasePattern) CBronyaBasePattern::Create()
{
	SP(CBronyaBasePattern) spInstance(new CBronyaBasePattern, Engine::SmartDeleter<CBronyaBasePattern>);

	return spInstance;
}