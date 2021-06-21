#include "stdafx.h"
#include "SpiderBornPattern.h"

//#include "FSM_SickleC.h"
//#include "FSMDefine_Sickle.h"
#include "MO_Spider.h"

CSpiderBornPattern::CSpiderBornPattern()
{
}

CSpiderBornPattern::~CSpiderBornPattern()
{
}

void CSpiderBornPattern::Pattern(Engine::CObject* pOwner)
{
	std::cout << "born" << std::endl;
}

SP(CSpiderBornPattern) CSpiderBornPattern::Create()
{
	SP(CSpiderBornPattern) spInstance(new CSpiderBornPattern, Engine::SmartDeleter<CSpiderBornPattern>);

	return spInstance;
}