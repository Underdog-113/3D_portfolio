#include "stdafx.h"
#include "BronyaAirbornePattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

CBronyaAirbornePattern::CBronyaAirbornePattern()
{
}

CBronyaAirbornePattern::~CBronyaAirbornePattern()
{
}

void CBronyaAirbornePattern::Pattern(Engine::CObject* pOwner)
{
}

SP(CBronyaAirbornePattern) CBronyaAirbornePattern::Create()
{
	SP(CBronyaAirbornePattern) spInstance(new CBronyaAirbornePattern, Engine::SmartDeleter<CBronyaAirbornePattern>);

	return spInstance;
}