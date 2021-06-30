#include "stdafx.h"
#include "BronyaBornPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"

#include "DynamicMeshData.h"
#include "PatternMachineC.h"

CBronyaBornPattern::CBronyaBornPattern()
{
}

CBronyaBornPattern::~CBronyaBornPattern()
{
}

void CBronyaBornPattern::Pattern(Engine::CObject* pOwner)
{
	
}

SP(CBronyaBornPattern) CBronyaBornPattern::Create()
{
	SP(CBronyaBornPattern) spInstance(new CBronyaBornPattern, Engine::SmartDeleter<CBronyaBornPattern>);

	return spInstance;
}