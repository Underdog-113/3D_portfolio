#include "stdafx.h"
#include "ATBPattern.h"

#include "Monster.h"

CATBPattern::CATBPattern()
{
}

CATBPattern::~CATBPattern()
{
}

void CATBPattern::CoolTime(_float & curTime, _float maxTime, _bool & readyType)
{
	if (true == readyType)
		return;

	if (maxTime <= curTime)
	{
		readyType = true;
		curTime = 0.f;
		return;
	}

	curTime += GET_DT;
}

void CATBPattern::PatternPlaySound(_TCHAR* fileName, Engine::CObject* pOwner)
{
	EChannelID id = static_cast<CMonster*>(pOwner)->GetChannelID();

	Engine::CSoundManager::GetInstance()->StopSound((_uint)id);
	Engine::CSoundManager::GetInstance()->StartSound(fileName, (_uint)id);
}

void CATBPattern::PatternStopSound(Engine::CObject * pOwner)
{
	EChannelID id = static_cast<CMonster*>(pOwner)->GetChannelID();

	Engine::CSoundManager::GetInstance()->StopSound((_uint)id);
}

void CATBPattern::PatternRepeatSound(_TCHAR* fileName, Engine::CObject * pOwner, _float interval)
{
	EChannelID id = static_cast<CMonster*>(pOwner)->GetChannelID();

	if (m_accTime >= interval)
	{
		Engine::CSoundManager::GetInstance()->StopSound((_uint)id);
		Engine::CSoundManager::GetInstance()->StartSound(fileName, (_uint)id);
		m_accTime = 0.f;
	}
	m_accTime += GET_DT;
}

void CATBPattern::SetPrequency(Engine::CObject * pOwner, _float * frequency)
{
	EChannelID id = static_cast<CMonster*>(pOwner)->GetChannelID();

	Engine::CSoundManager::GetInstance()->GetChannelFrequency((_uint)id, frequency);
}

_bool CATBPattern::PatternSoundEnd(Engine::CObject * pOwner)
{
	EChannelID id = static_cast<CMonster*>(pOwner)->GetChannelID();

	return Engine::CSoundManager::GetInstance()->IsPlaying((_uint)id);
}
