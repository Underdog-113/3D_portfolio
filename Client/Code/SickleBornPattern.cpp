#include "stdafx.h"
#include "SickleBornPattern.h"

//#include "FSM_SickleC.h"
//#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

CSickleBornPattern::CSickleBornPattern()
{
}

CSickleBornPattern::~CSickleBornPattern()
{
}

void CSickleBornPattern::Pattern(Engine::CObject* pOwner)
{
	std::cout << "born" << std::endl;
}

SP(CSickleBornPattern) CSickleBornPattern::Create()
{
	SP(CSickleBornPattern) spInstance(new CSickleBornPattern, Engine::SmartDeleter<CSickleBornPattern>);

	return spInstance;
}