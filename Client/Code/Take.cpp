#include "stdafx.h"
#include "..\Header\Take.h"

#include "Shot.h"

CTake::CTake()
{
}


CTake::~CTake()
{
	m_shotMap.clear();
}

void CTake::StartTake(_bool fixCamera)
{
	CStageControlTower::GetInstance()->SetDirectorMode(fixCamera);
	m_playTimer = 0.f;
	m_editMode = false;
}

void CTake::ActTake()
{
	if (Engine::IMKEY_PRESS(KEY_SHIFT))
		Engine::CFRC::GetInstance()->SetFastLoad(6.f);
	else
		Engine::CFRC::GetInstance()->SetFastLoad(1.f);

	if (m_editMode)
		ActTake_EditMode();
	else
		ActTake_NormalMode();
}

void CTake::ActTake_EditMode()
{
	if (Engine::IMKEY_PRESS(KEY_CONTROL))
	{
		if (Engine::IMKEY_PRESS(KEY_LEFT))
		{
			MovePreviousFrame();
		}
		if (Engine::IMKEY_PRESS(KEY_RIGHT))
		{
			MoveNextFrame();
		}
	}
	else
	{
		if (Engine::IMKEY_DOWN(KEY_LEFT))
		{
			MovePreviousFrame();
		}
		if (Engine::IMKEY_DOWN(KEY_RIGHT))
		{
			MoveNextFrame();
		}
	}
}

void CTake::ActTake_NormalMode()
{
	_uint shotEnd = 0;

	for (auto iter : m_shotMap)
	{
		if (iter.second->CheckOnTake(m_playTimer))
			iter.second->Action();

		if (iter.second->CheckShotEnd(m_playTimer))
			++shotEnd;
	}

	if (!m_editMode && shotEnd < m_shotMap.size())
	{
		m_playTimer += GET_PURE_DT;
	}

	if (shotEnd == m_shotMap.size())
	{
		CStageControlTower::GetInstance()->GetMovieDirector()->CutCurrentTake();
	}
}

void CTake::EndTake()
{
	CStageControlTower::GetInstance()->SetDirectorMode(false);
	Engine::CFRC::GetInstance()->SetFastLoad(1.f);

// 
// 	for (auto iter : m_shotMap)
// 	{
// 		iter.second->Rollback();
// 	}
}

void CTake::MoveNextFrame()
{
	m_playTimer += 0.0167f;

	_uint shotEnd = 0;

	for (auto iter : m_shotMap)
	{
		if (iter.second->CheckOnTake(m_playTimer))
			iter.second->Action();

		if (iter.second->CheckShotEnd(m_playTimer))
			++shotEnd;
	}

	if (shotEnd == m_shotMap.size())
	{
		m_playTimer -= 0.0167f;
	}
}

void CTake::MovePreviousFrame()
{
	m_playTimer -= 0.0167f;

	if (m_playTimer < 0.f)
	{
		m_playTimer = 0.f;
	}

	for (auto iter : m_shotMap)
	{
		if (iter.second->CheckOnTake(m_playTimer))
			iter.second->Action();

		iter.second->CheckShotRollback(m_playTimer);
	}
}

void CTake::EndShot(CShot * pShot)
{
}

void CTake::AddShot(std::wstring name, CShot * pShot)
{
	m_shotMap.emplace(name, pShot);
}

void CTake::ReadyShot(std::wstring name, _float startTimeline, _float endTimeline, void * pDesc, _float readyTimeline)
{
	auto pShot = m_shotMap[name];

	pShot->Ready(this, startTimeline, endTimeline, pDesc, readyTimeline);
}

