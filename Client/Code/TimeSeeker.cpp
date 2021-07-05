#include "stdafx.h"
#include "TimeSeeker.h"

#include "Valkyrie.h"
#include "MeshC.h"
#include "DynamicMeshData.h"
#include "AniCtrl.h"

CTimeSeeker::CTimeSeeker()
{
}


CTimeSeeker::~CTimeSeeker()
{
}

void CTimeSeeker::UpdateTimeSeeker()
{
	PlayPerfectEvadeMode();
}

void CTimeSeeker::OnPerfectEvadeMode()
{
	if (m_perfectEvadeMode)
		return;

	m_perfectEvadeMode = true;
	m_slowAll = true;
	m_slowTimer = 0.f;

	Engine::CFRC::GetInstance()->SetDtCoef(0.1f);

	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	pActor->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetIsAdvanceByPure(false);
}

void CTimeSeeker::PlayPerfectEvadeMode()
{
	if (m_perfectEvadeMode)
	{
		m_slowTimer += GET_PURE_DT;
		if (m_slowTimer > 3.f)
		{
			m_perfectEvadeMode = false;
			Engine::CFRC::GetInstance()->SetDtCoef(1.f);
		}
		else if (m_slowTimer > 0.5f)
		{
			m_slowAll = false;
			auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
			pActor->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetIsAdvanceByPure(true);
		}
	}
}

_float CTimeSeeker::GetPlayerDeltaTime()
{
	if (m_slowAll)
		return GET_DT;

	return GET_PURE_DT;
}
