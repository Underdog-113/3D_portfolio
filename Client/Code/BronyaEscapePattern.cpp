#include "stdafx.h"
#include "BronyaEscapePattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"
#include "StageControlTower.h"
#include "Bronya_Teleport_Ring.h"
#include "Bronya_Teleport_Laser.h"

CBronyaEscapePattern::CBronyaEscapePattern()
{
}

CBronyaEscapePattern::~CBronyaEscapePattern()
{
}

void CBronyaEscapePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	if (Name_Escape_Out != fsm->GetCurStateString())
	{
		static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);
	}

	// 이스케이프 외 애니메이션이 종료되었다면
	if (Name_Escape_In != fsm->GetCurStateString() &&
		Name_Escape_Out != fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// escape in 실행
		fsm->ChangeState(Name_Escape_Out);

		// effect
		SP(CBronya_Teleport_Ring) effect = std::dynamic_pointer_cast<CBronya_Teleport_Ring>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Teleport_Ring", true));
		effect->GetTransform()->SetPosition(mPos);
		effect->GetTransform()->AddPositionY(0.5f);

		
		m_vLaserOutEffect = std::dynamic_pointer_cast<CBronya_Teleport_Laser>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Teleport_Laser", true));
		m_vLaserOutEffect->GetTransform()->AddSizeX(-0.5f);
		m_vLaserOutEffect->GetTransform()->SetPosition(mPos);
		defaultEscapeEffectSizeX = m_vLaserOutEffect->GetTransform()->GetSize().x;
		m_onLaserOutEffect = true;
	}
	// escape in 상태 중 적절한 위치로 올라왔다면
	else if (Name_Escape_Out == fsm->GetCurStateString() &&
		0.76f <= fsm->GetDM()->GetAniTimeline() &&
		0.f >= m_lerpCurTimer &&
		false == m_onEscape)
	{
		// 애니메이션 정지
		fsm->GetDM()->GetAniCtrl()->SetSpeed(0.05f);
		m_onEscape = true;

		// 이스케이프 위치로 이동
		m_lerpStartPos = mPos;
		m_lerpEndPos = GetEscapePos(pOwner);
		m_lerpCurTimer = 0.f;
	}
	// escape in 상태 중 목표 위치로 이동 중이라면
	else if (Name_Escape_Out == fsm->GetCurStateString() &&
		0.05f >= fsm->GetDM()->GetAniCtrl()->GetSpeed() &&
		m_lerpCurTimer < m_lerpMaxTimer)
	{
		m_lerpCurTimer += GET_DT;

		if (m_lerpCurTimer >= m_lerpMaxTimer)
		{
			m_lerpCurTimer = m_lerpMaxTimer;
		}

		_float3 currentPos = GetLerpPosition(m_lerpStartPos, m_lerpEndPos, m_lerpCurTimer, 0.3f);
		pOwner->GetTransform()->SetPosition(currentPos);
	}
	// escape in 상태 중이면서 이동이 끝났다면
	else if (Name_Escape_Out == fsm->GetCurStateString() &&
		m_lerpCurTimer <= m_lerpMaxTimer &&
		true == m_onEscape)
	{
		// 애니메이션 재생
		fsm->ChangeState(Name_Escape_In);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onEscape = false;

		
		m_vLaserInEffect = std::dynamic_pointer_cast<CBronya_Teleport_Laser>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Teleport_Laser", true));
		m_vLaserInEffect->GetTransform()->AddSizeX(-0.5f);
		m_vLaserInEffect->GetTransform()->SetPosition(mPos);
		m_onLaserInEffect = true;
	}
	// escape in 상태가 끝났다면
	else if (Name_Escape_In == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		m_lerpCurTimer = 0.f;
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
	}

	/************************* Effect */
	if (true == m_onLaserOutEffect)
	{
		_float sizeX = m_vLaserOutEffect->GetTransform()->GetSize().x - (1.5f * GET_DT);

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() > 0)
		{
			static_cast<CMB_Bronya*>(pOwner)->SetAlpha(-1.3f * GET_DT);

			if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() <= 0.f)
			{
				static_cast<CMB_Bronya*>(pOwner)->SetAlpha(0.f);
			}

			_float alpha = static_cast<CMB_Bronya*>(pOwner)->GetAlpha();
		}

		if (0.f >= sizeX)
		{
			m_vLaserOutEffect->GetTransform()->SetSizeX(0.f);	
		}
		else
		{
			m_vLaserOutEffect->GetTransform()->SetSizeX(sizeX);
		}

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() <= 0.f &&
			m_vLaserOutEffect->GetTransform()->GetSize().x <= 0.f)
		{
			m_onLaserOutEffect = false;
			m_vLaserOutEffect->SetDeleteThis(true);
		}
	}

	if (true == m_onLaserInEffect)
	{
		_float sizeX = m_vLaserInEffect->GetTransform()->GetSize().x - (3.5f * GET_DT);

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() <= 0.f)
		{
			static_cast<CMB_Bronya*>(pOwner)->SetAlpha(1.3f * GET_DT);

			if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() >= 1.f)
			{
				static_cast<CMB_Bronya*>(pOwner)->SetAlpha(1.f);
			}

			_float alpha = static_cast<CMB_Bronya*>(pOwner)->GetAlpha();
		}

		if (0.f >= sizeX)
		{
			m_vLaserInEffect->GetTransform()->SetSizeX(0.f);
		}
		else
		{
			m_vLaserInEffect->GetTransform()->SetSizeX(sizeX);
		}

		if (static_cast<CMB_Bronya*>(pOwner)->GetAlpha() >= 1.f &&
			m_vLaserOutEffect->GetTransform()->GetSize().x <= 0.f)
		{
			m_onLaserOutEffect = false;
			m_vLaserOutEffect->SetDeleteThis(true);
		}
	}
}

SP(CBronyaEscapePattern) CBronyaEscapePattern::Create()
{
	SP(CBronyaEscapePattern) spInstance(new CBronyaEscapePattern, Engine::SmartDeleter<CBronyaEscapePattern>);

	return spInstance;
}

_float3 CBronyaEscapePattern::GetEscapePos(Engine::CObject* pOwner)
{
	_int cnt = static_cast<CMB_Bronya*>(pOwner)->GetMaxEscapePos() - 1;
	_int index = GetRandRange(0, cnt);

	return static_cast<CMB_Bronya*>(pOwner)->GetEscapePos()[index];
}
