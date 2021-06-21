#include "stdafx.h"
#include "ATBPattern.h"

CATBPattern::CATBPattern()
{
}

CATBPattern::~CATBPattern()
{
}

void CATBPattern::CoolTime(_float & curTime, _float maxTime, _bool & readyType)
{
	if (true == readyType)
		return;

	if (maxTime <= curTime)
	{
		readyType = true;
		curTime = 0.f;
		return;
	}

	curTime += GET_DT;
}
