#include "stdafx.h"
#include "SickleDiePattern.h"

//#include "FSM_SickleC.h"
//#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

CSickleDiePattern::CSickleDiePattern()
{
}

CSickleDiePattern::~CSickleDiePattern()
{
}

void CSickleDiePattern::Pattern(Engine::CObject* pOwner)
{
	std::cout << "die" << std::endl;
}

SP(CSickleDiePattern) CSickleDiePattern::Create()
{
	SP(CSickleDiePattern) spInstance(new CSickleDiePattern, Engine::SmartDeleter<CSickleDiePattern>);

	return spInstance;
}