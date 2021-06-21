#include "stdafx.h"
#include "SpiderDiePattern.h"

//#include "FSM_SickleC.h"
//#include "FSMDefine_Sickle.h"
#include "MO_Spider.h"

CSpiderDiePattern::CSpiderDiePattern()
{
}

CSpiderDiePattern::~CSpiderDiePattern()
{
}

void CSpiderDiePattern::Pattern(Engine::CObject* pOwner)
{
	std::cout << "die" << std::endl;
}

SP(CSpiderDiePattern) CSpiderDiePattern::Create()
{
	SP(CSpiderDiePattern) spInstance(new CSpiderDiePattern, Engine::SmartDeleter<CSpiderDiePattern>);

	return spInstance;
}