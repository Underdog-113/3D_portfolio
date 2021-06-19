#include "stdafx.h"
#include "SickleAtk02Pattern.h"

//#include "FSM_SickleC.h"
//#include "FSMDefine_Sickle.h"
#include "MO_Sickle.h"

CSickleAtk02Pattern::CSickleAtk02Pattern()
{
}

CSickleAtk02Pattern::~CSickleAtk02Pattern()
{
}

void CSickleAtk02Pattern::Pattern(Engine::CObject* pOwner)
{
	std::cout << "Atk02" << std::endl;
}

SP(CSickleAtk02Pattern) CSickleAtk02Pattern::Create()
{
	SP(CSickleAtk02Pattern) spInstance(new CSickleAtk02Pattern, Engine::SmartDeleter<CSickleAtk02Pattern>);

	return spInstance;
}