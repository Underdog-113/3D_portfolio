#include "stdafx.h"
#include "BoxBasePattern.h"

CBoxBasePattern::CBoxBasePattern()
{
}

CBoxBasePattern::~CBoxBasePattern()
{
}

void CBoxBasePattern::Pattern(Engine::CObject* pOwner)
{
}

SP(CBoxBasePattern) CBoxBasePattern::Create()
{
	SP(CBoxBasePattern) spInstance(new CBoxBasePattern, Engine::SmartDeleter<CBoxBasePattern>);

	return spInstance;
}