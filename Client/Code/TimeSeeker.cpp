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
	PlayAttackImpactSlow();

	PlaySlowExceptPlayer();
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
	m_prevColoring = (_uint)CStageControlTower::GetInstance()->GetEnvType();
	CStageControlTower::GetInstance()->SetEnvType(CStageControlTower::PerfectEvade);
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
			CStageControlTower::GetInstance()->SetEnvType((CStageControlTower::Env_Type)m_prevColoring);
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

void CTimeSeeker::OnAttackImpactSlow()
{
	m_slowAll = true;
	m_isAttackImpactSlow = true;
	m_slowTimer = 0.f;

	Engine::CFRC::GetInstance()->SetDtCoef(0.1f);

	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	pActor->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetIsAdvanceByPure(false);
}

void CTimeSeeker::PlayAttackImpactSlow()
{
	if (m_isAttackImpactSlow)
	{
		m_slowTimer += GET_PURE_DT;
		if (m_slowTimer > 0.1f)
		{
			m_isAttackImpactSlow = false;
			Engine::CFRC::GetInstance()->SetDtCoef(1.f);
			auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
			pActor->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetIsAdvanceByPure(true);
		}
	}
}


void CTimeSeeker::OnSlowExceptPlayer()
{
	m_slowAll = false;
	m_isSlowExceptPlayer = true;

	Engine::CFRC::GetInstance()->SetDtCoef(0.1f);

	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	pActor->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetIsAdvanceByPure(true);
}

void CTimeSeeker::OffSlowExceptPlayer()
{
	m_isSlowExceptPlayer = false;

	Engine::CFRC::GetInstance()->SetDtCoef(1.f);

	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	pActor->GetComponent<Engine::CMeshC>()->GetFirstMeshData_Dynamic()->GetAniCtrl()->SetIsAdvanceByPure(false);
}

void CTimeSeeker::PlaySlowExceptPlayer()
{
	if (m_isSlowExceptPlayer)
	{
		m_slowTimer += GET_PURE_DT;
		if (m_slowTimer > 3.f)
		{
			m_isSlowExceptPlayer = false;
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
