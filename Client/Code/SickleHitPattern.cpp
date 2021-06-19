#include "stdafx.h"
#include "SickleHitPattern.h"

//#include "FSM_SickleC.h"
//#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

CSickleHitPattern::CSickleHitPattern()
{
}

CSickleHitPattern::~CSickleHitPattern()
{
}

void CSickleHitPattern::Pattern(Engine::CObject* pOwner)
{
	std::cout << "hit" << std::endl;
}

SP(CSickleHitPattern) CSickleHitPattern::Create()
{
	SP(CSickleHitPattern) spInstance(new CSickleHitPattern, Engine::SmartDeleter<CSickleHitPattern>);

	return spInstance;
}