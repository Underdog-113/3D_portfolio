#include "stdafx.h"
#include "GaneshaAirbornePattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

CGaneshaAirbornePattern::CGaneshaAirbornePattern()
{
}

CGaneshaAirbornePattern::~CGaneshaAirbornePattern()
{
}

void CGaneshaAirbornePattern::Pattern(Engine::CObject* pOwner)
{
}

SP(CGaneshaAirbornePattern) CGaneshaAirbornePattern::Create()
{
	SP(CGaneshaAirbornePattern) spInstance(new CGaneshaAirbornePattern, Engine::SmartDeleter<CGaneshaAirbornePattern>);

	return spInstance;
}