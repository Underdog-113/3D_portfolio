#include "stdafx.h"
#include "NinzaAttack2Pattern.h"

#include "FSM_NinzaC.h"
#include "FSMDefine_Ninza.h"
#include "MO_Ninza.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"

CNinzaAttack2Pattern::CNinzaAttack2Pattern()
{
}

CNinzaAttack2Pattern::~CNinzaAttack2Pattern()
{
}

void CNinzaAttack2Pattern::Pattern(Engine::CObject* pOwner)
{
	
}

SP(CNinzaAttack2Pattern) CNinzaAttack2Pattern::Create()
{
	SP(CNinzaAttack2Pattern) spInstance(new CNinzaAttack2Pattern, Engine::SmartDeleter<CNinzaAttack2Pattern>);

	return spInstance;
}