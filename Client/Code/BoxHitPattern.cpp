#include "stdafx.h"
#include "BoxHitPattern.h"

CBoxHitPattern::CBoxHitPattern()
{
}

CBoxHitPattern::~CBoxHitPattern()
{
}

void CBoxHitPattern::Pattern(Engine::CObject* pOwner)
{
}

SP(CBoxHitPattern) CBoxHitPattern::Create()
{
	SP(CBoxHitPattern) spInstance(new CBoxHitPattern, Engine::SmartDeleter<CBoxHitPattern>);

	return spInstance;
}