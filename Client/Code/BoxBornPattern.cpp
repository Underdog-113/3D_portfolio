#include "stdafx.h"
#include "BoxBornPattern.h"

CBoxBornPattern::CBoxBornPattern()
{
}

CBoxBornPattern::~CBoxBornPattern()
{
}

void CBoxBornPattern::Pattern(Engine::CObject* pOwner)
{
}

SP(CBoxBornPattern) CBoxBornPattern::Create()
{
	SP(CBoxBornPattern) spInstance(new CBoxBornPattern, Engine::SmartDeleter<CBoxBornPattern>);

	return spInstance;
}