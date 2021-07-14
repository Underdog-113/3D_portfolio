#include "stdafx.h"
#include "BoxDiePattern.h"

#include "Monster.h"

CBoxDiePattern::CBoxDiePattern()
{
}

CBoxDiePattern::~CBoxDiePattern()
{
}

void CBoxDiePattern::Pattern(Engine::CObject* pOwner)
{
	// ���� hp�� 0�� �Ǹ�
	if (0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		pOwner->SetDeleteThis(true);
	}
}

SP(CBoxDiePattern) CBoxDiePattern::Create()
{
	SP(CBoxDiePattern) spInstance(new CBoxDiePattern, Engine::SmartDeleter<CBoxDiePattern>);

	return spInstance;
}