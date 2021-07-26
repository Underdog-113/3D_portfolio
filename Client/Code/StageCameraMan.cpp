#include "stdafx.h"
#include "StageCameraMan.h"
#include "StageControlTower.h"
#include "ObjectFactory.h"
#include "EmptyObject.h"
#include "Valkyrie.h"
#include "CameraShake.h"

#include "WndApp.h"

CStageCameraMan::CStageCameraMan()
{
}


CStageCameraMan::~CStageCameraMan()
{
	delete m_pCameraShake;
}

void CStageCameraMan::Start()
{
	m_spCamera->SetTargetDist(MidShot);
	m_spCamera->SetMaxDistTPS(MidShot);
	m_spCamera->SetMode(Engine::ECameraMode::TPS_Custom);
	m_spCamera->SetLookAngleRight(MidAngle);


	m_spPivot = Engine::GET_CUR_SCENE->ADD_CLONE(L"EmptyObject", true, (_uint)Engine::ELayerID::Camera, L"CameraPivot");
	m_spPivot->AddComponent<Engine::CCollisionC>()->
		AddCollider(Engine::CAabbCollider::Create((_int)ECollisionID::FloorRay, _float3(0.25f, 0.25f, 0.25f)));
	m_spPivot->AddComponent<Engine::CDebugC>();
	m_spPivot->AddComponent<Engine::CShaderC>();
	m_spPivot->GetTransform()->SetPosition(CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition());
	m_dstPivotPos = m_spPivot->GetTransform()->GetPosition();
	
	m_spCamera->SetTarget(m_spPivot);
	m_spCamera->GetTransform()->SetPosition(m_spPivot->GetTransform()->GetPosition());

	m_rotateLerpStart = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetRotation().y;
	m_rotateYDst = m_rotateLerpStart;
	m_spCamera->SetLookAngleUp(m_rotateLerpStart);

	m_isStart = true;

	m_pCameraShake = new CCameraShake;
	m_pCameraShake->SetCamera(m_spCamera);
	
}

void CStageCameraMan::UpdateCameraMan()
{

	if(!m_isStart)
		Start();

	if (m_spCamera->GetMode() != Engine::ECameraMode::TPS_Custom)
		return;


	if (m_directorControl)
	{
		DirectorControlMode();
		return;
	}

	ReturnBeforShaking();

	if (!m_isSwitching)
	{
		PivotChasing();

		if (!MouseControlMode())
		{
			ManualControlMode();

			if (!m_manualControl)
				AutoControlMode();
		}
	}

	ApplyShaking();
}

void CStageCameraMan::DirectorControlMode()
{
	ReturnBeforShaking();

	if (m_isPivotChasing)
		PivotChasing_Director();

	ApplyShaking();

}

void CStageCameraMan::ReturnToMidShot()
{
	m_curShotType = Mid;
	m_nextShotType = Mid;
	m_curMaxDist = MidShot;
	m_dstMaxDist = MidShot;
	m_rotateXStart = MidAngle;
	m_rotateXDst = MidAngle;

	m_spCamera->SetTargetDist(m_dstMaxDist);
	m_spCamera->SetMaxDistTPS(m_dstMaxDist);

	m_spCamera->SetLookAngleRight(m_rotateXStart);
}

void CStageCameraMan::PivotChasing_Director()
{
	NonTargetChasing();

	if (m_isVertCorrecting)
		AppendPosYCorrecting();

	_float3 lerpPosition = GetLerpPosition(
		m_spPivot->GetTransform()->GetPosition(), m_dstPivotPos, GET_PLAYER_DT * m_chaseSpeed);

	if (D3DXVec3Length(&(m_dstPivotPos - lerpPosition)) < 0.01f)
	{
		lerpPosition = m_dstPivotPos;
	}
	m_spPivot->GetTransform()->SetPosition(lerpPosition);

}


void CStageCameraMan::PivotChasing()
{
	if (m_isTargeting)
	{
		OnTargetChasing();
		RotateCameraHorizontal();
	}
	else
	{
		NonTargetChasing();
	}

	if (m_isVertCorrecting)
		AppendPosYCorrecting();

	_float3 lerpPosition = GetLerpPosition(
		m_spPivot->GetTransform()->GetPosition(), m_dstPivotPos, GET_PLAYER_DT * m_chaseSpeed);


	if (D3DXVec3Length(&(m_dstPivotPos - lerpPosition)) < 0.01f)
	{
		lerpPosition = m_dstPivotPos;
	}
	m_spPivot->GetTransform()->SetPosition(lerpPosition);
}

void CStageCameraMan::NonTargetChasing()
{
	auto pCT = CStageControlTower::GetInstance();

	if (m_isChaseSpeedChange)
	{
		if (m_chaseSpeedIncreaseTimer < 1.f)
		{
			m_chaseSpeedIncreaseTimer += GET_PLAYER_DT;
			//m_chaseSpeed = GetLerpFloat(m_startChaseSpeed, m_endChaseSpeed, m_chaseSpeedIncreaseTimer);
		}
		else
		{
			m_chaseSpeed = m_endChaseSpeed;
			m_isChaseSpeedChange = false;
		}
	}

	_float3 actorPos = pCT->GetCurrentActor()->GetTransform()->GetPosition();
	_float3 pivotPos = m_spPivot->GetTransform()->GetPosition();

	if (actorPos == pivotPos)
		return;

	_float3 dir = actorPos - pivotPos;
	_float len = D3DXVec3Length(&dir);

	D3DXVec3Normalize(&dir, &dir);
	if (len > MaxChaseDistance)
		m_dstPivotPos = pivotPos + dir * MaxChaseDistance;
	else
		m_dstPivotPos = pCT->GetCurrentActor()->GetTransform()->GetPosition();
}

void CStageCameraMan::SetIsTargeting(bool value)
{
	m_isTargeting = value;
	m_targetingTimer = 0.f;

	if (value)
	{
		SetTargetShot();

		m_chaseSpeed = 15.f;
		m_isChaseSpeedChange = false;
	}
	else
	{
		SetMidShot();
		m_chaseSpeedIncreaseTimer = 0.f;
		m_startChaseSpeed = 5.f;
		m_endChaseSpeed = 15.f;
		m_chaseSpeed = m_startChaseSpeed;
		m_isChaseSpeedChange = true;
	}
}

void CStageCameraMan::ResetChaseSpeed()
{
	m_chaseSpeed = 7.f;
}

void CStageCameraMan::SetNearShot()
{
	if (m_curShotType == Near)
		return;

	if (m_curShotType == Change)
		m_curMaxDist = m_spCamera->GetMaxDistTPS();

	m_curShotType = Change;
	m_nextShotType = Near;
	m_dstMaxDist = NearShot;
	m_changeShotTimer = 0.f;
	m_changeShotSpeed = 0.5f;
	m_rotateXStart = m_spCamera->GetLookAngleRight();
	m_rotateXDst = NearAngle;
}

void CStageCameraMan::SetMidShot()
{
	if (m_curShotType == Mid)
		return;

	if (m_curShotType == Change && m_nextShotType == Far)
		return;

	if (m_curShotType == Change)
		m_curMaxDist = m_spCamera->GetMaxDistTPS();

	m_curShotType = Change;
	m_nextShotType = Mid;
	m_dstMaxDist = MidShot;
	m_changeShotTimer = 0.f;
	m_changeShotSpeed = 2.f;
	m_rotateXStart = m_spCamera->GetLookAngleRight();
	m_rotateXDst = MidAngle;
}

void CStageCameraMan::SetFarShot()
{
	if (m_curShotType == Far)
	{
		m_gotoNextShotTimer = 0.f;
		return;
	}
	if (m_curShotType == Change && m_nextShotType == Far)
		return;

	if (m_curShotType == Change)
		m_curMaxDist = m_spCamera->GetMaxDistTPS();

	m_curShotType = Change;
	m_nextShotType = Far;
	m_dstMaxDist = FarShot;
	m_changeShotTimer = 0.f;
	m_changeShotSpeed = 2.5f;
	m_rotateXStart = m_spCamera->GetLookAngleRight();
	m_rotateXDst = FarAngle;
}

void CStageCameraMan::SetCustomShot(_float dstMaxDistance, _float changeSpeed, _float dstXAngle)
{
	if (m_curShotType == Change)
		m_curMaxDist = m_spCamera->GetMaxDistTPS();

	m_gotoNextShotTimer = 0.f;
	m_curShotType = Change;
	m_nextShotType = Custom;
	m_dstMaxDist = dstMaxDistance;
	m_changeShotTimer = 0.f;
	m_changeShotSpeed = changeSpeed;
	m_rotateXStart = m_spCamera->GetLookAngleRight();
	m_rotateXDst = dstXAngle;
}

void CStageCameraMan::SetTargetShot()
{
	if (m_curShotType == Target || m_curShotType == Change)
	{
		m_gotoNextShotTimer = 0.f;
		return;
	}
	
	m_curShotType = Target;
	m_nextShotType = Target;
	m_changeShotTimer = 0.f;
	m_changeShotSpeed = 2.f;
	m_rotateXStart = m_spCamera->GetLookAngleRight();
	m_rotateXDst = D3DXToRadian(15.f);

	auto pCT = CStageControlTower::GetInstance();

	_float3 cameraPos = m_spCamera->GetTransform()->GetPosition();
	_float3 pActor = pCT->GetCurrentActor()->GetTransform()->GetPosition();
	_float3 pTarget = pCT->GetCurrentTarget()->GetTransform()->GetPosition();

	_float3 camForward = pActor - cameraPos;
	camForward.y = 0.f;
	D3DXVec3Normalize(&camForward, &camForward);

	_float3 actorToTarget = pTarget - pActor;
	_float distance = D3DXVec3Length(&actorToTarget);
	actorToTarget.y = 0.f;
	D3DXVec3Normalize(&actorToTarget, &actorToTarget);

	_float dotValue;
	_float3 crossDir;
	dotValue = D3DXVec3Dot(&camForward, &actorToTarget);
	D3DXVec3Cross(&crossDir, &camForward, &actorToTarget);

	_float radAngle = acosf(dotValue);

	if (crossDir.y > 0.f)
	{
		if (radAngle > D3DXToRadian(30.f))
		{
			m_rotateLerpStart = m_spCamera->GetLookAngleUp();
			m_rotateYDst = m_rotateLerpStart + (radAngle - D3DXToRadian(30.f));
		}
	}
	else
	{
		if (radAngle > D3DXToRadian(30.f))
		{
			m_rotateLerpStart = m_spCamera->GetLookAngleUp();
			m_rotateYDst = m_rotateLerpStart + (radAngle - D3DXToRadian(30.f));
		}
	}

	if (distance > TargetWideLimitDist)
	{
		if (m_dstMaxDist < 6.f)
		{
			// wide
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = 6.f;
			m_changeShotTimer = 0.f;
			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = D3DXToRadian(15.f);
		}
	}
	else if (distance < TargetMidWideLimitDist)
	{
		if (m_dstMaxDist > 2.5f && m_changeShotTimer > 2.f)
		{
			// normal
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = 2.5f;
			m_changeShotTimer = 0.f;
			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = D3DXToRadian(15.f);
		}
	}
	else
	{
		if (m_dstMaxDist != 4.f && m_changeShotTimer > 2.f)
		{
			// midwide
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = 4.f;
			m_changeShotTimer = 0.f;
			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = D3DXToRadian(15.f);

		}
	}
}

void CStageCameraMan::ChangeShot()
{
	switch (m_curShotType)
	{
	case CStageCameraMan::Near:
		if (!CheckNoAction())
		{
			SetMidShot();
			return;
		}
		break;
	case CStageCameraMan::Mid:
		if (CheckNoAction())
		{
			m_gotoNextShotTimer += GET_PLAYER_DT;
			if (m_gotoNextShotTimer > 4.f)
			{
				m_gotoNextShotTimer = 0.f;
				SetNearShot();
			}
		}
		else
		{
			m_gotoNextShotTimer = 0.f;
		}
		break;
	case CStageCameraMan::Far:
		if (CheckNoAction())
		{
			m_gotoNextShotTimer += GET_PLAYER_DT;
			if (m_gotoNextShotTimer > 1.5f)
			{
				m_gotoNextShotTimer = 0.f;
				SetMidShot();
			}
		}
		break;
	case CStageCameraMan::Custom:
		if (CheckNoAction())
		{
			m_gotoNextShotTimer += GET_PLAYER_DT;
			if (m_gotoNextShotTimer > m_gotoNextShotWaitTime)
			{
				m_gotoNextShotWaitTime = 1.5f;
				m_gotoNextShotTimer = 0.f;
				SetMidShot();
			}
		}
		break;
	case CStageCameraMan::Target:
		{
			ChangeShotWhileTargeting();

			if (m_changeShotTimer < 1.f)
			{
				m_changeShotTimer += GET_PLAYER_DT * m_changeShotSpeed;
				if (m_changeShotTimer > 1.f)
				{
					m_curMaxDist = m_dstMaxDist;
					m_spCamera->SetTargetDist(m_dstMaxDist);
					m_spCamera->SetMaxDistTPS(m_dstMaxDist);
					break;
				}

				float inverseRate = 1.f - m_changeShotTimer;
				float sLerpTimer = 1.f - inverseRate * inverseRate;

				_float lerpPoint = FloatLerp(m_curMaxDist, m_dstMaxDist, sLerpTimer);
				m_spCamera->SetTargetDist(lerpPoint);
				m_spCamera->SetMaxDistTPS(lerpPoint);

				lerpPoint = FloatLerp(m_rotateXStart, m_rotateXDst, sLerpTimer);
				m_spCamera->SetLookAngleRight(lerpPoint);
			}
		}
		break;
	case CStageCameraMan::Change:
		if (m_nextShotType == Near && !CheckNoAction())
		{
			m_nextShotType = Mid;
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = MidShot;
			m_changeShotTimer = 0.f;
			m_changeShotSpeed = 2.f;

			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = MidAngle;
		}

		m_changeShotTimer += GET_PLAYER_DT * m_changeShotSpeed;
		if (m_changeShotTimer > 1.f)
		{
			m_curMaxDist = m_dstMaxDist;
			m_curShotType = m_nextShotType;
			m_spCamera->SetTargetDist(m_dstMaxDist);
			m_spCamera->SetMaxDistTPS(m_dstMaxDist);
			return;
		}

		float inverseRate = 1.f - m_changeShotTimer;
		float sLerpTimer = 1.f - inverseRate * inverseRate;

		_float lerpPoint = FloatLerp(m_curMaxDist, m_dstMaxDist, sLerpTimer);
		m_spCamera->SetTargetDist(lerpPoint);
		m_spCamera->SetMaxDistTPS(lerpPoint);

		lerpPoint = FloatLerp(m_rotateXStart, m_rotateXDst, sLerpTimer);
		m_spCamera->SetLookAngleRight(lerpPoint);
		break;
	}
}

void CStageCameraMan::ChangeShotWhileTargeting()
{
	if (m_changeShotTimer > 1.f)
		m_changeShotTimer += GET_PLAYER_DT * m_changeShotSpeed;

	auto pCT = CStageControlTower::GetInstance();
	auto spTarget = pCT->GetCurrentTarget();
	if (!spTarget || spTarget->GetDeleteThis())
		return;

	_float3 pActor = pCT->GetCurrentActor()->GetTransform()->GetPosition();
	_float3 pTarget = pCT->GetCurrentTarget()->GetTransform()->GetPosition();
	_float distance = D3DXVec3Length(&_float3(pTarget - pActor));
	
	if (distance > TargetWideLimitDist)
	{
		if (m_dstMaxDist < 6.f)
		{
			// wide
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = 6.f;
			m_changeShotTimer = 0.f;
			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = D3DXToRadian(15.f);
		}
	}
	else if (distance < TargetMidWideLimitDist)
	{
		if (m_dstMaxDist > 2.5f && m_changeShotTimer > 2.f)
		{
			// normal
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = 2.5f;
			m_changeShotTimer = 0.f;
			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = D3DXToRadian(15.f);
		}
	}
	else
	{
		if (m_dstMaxDist != 4.f && m_changeShotTimer > 2.f)
		{
			// midwide
			m_curMaxDist = m_spCamera->GetMaxDistTPS();
			m_dstMaxDist = 4.f;
			m_changeShotTimer = 0.f;
			m_rotateXStart = m_spCamera->GetLookAngleRight();
			m_rotateXDst = D3DXToRadian(15.f);

		}
	}

}

void CStageCameraMan::OnAttackDirectionCorrecting()
{
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();

	_float3 actorForward = pActor->GetTransform()->GetForward();
	actorForward.y = 0.f;
	D3DXVec3Normalize(&actorForward, &actorForward);
	_float3 camForward = m_spCamera->GetTransform()->GetForward();
	camForward.y = 0.f;
	D3DXVec3Normalize(&camForward, &camForward);

	float angleSynchroRate = D3DXVec3Dot(&actorForward, &camForward);
	angleSynchroRate = GET_MATH->RoundOffRange(angleSynchroRate, 1);

	if (angleSynchroRate > 0.99f)
	{
		m_isAttackCorrecting = false;
		return;
	}

	_float3 crossVector = ZERO_VECTOR;
	D3DXVec3Cross(&crossVector, &camForward, &actorForward);
	if (crossVector.y > 0.f)
	{
		// right
		m_attackCorrectingAngle = D3DXToRadian(10.f);
	}
	else
	{
		// left

		m_attackCorrectingAngle = -D3DXToRadian(10.f);
	}

	m_attackCorrectingTimer = 0.f;
	m_isAttackCorrecting = true;
}

void CStageCameraMan::AppendAttackDirectionCorrecting()
{
	if (!m_isAttackCorrecting)
		return;

	m_attackCorrectingTimer += GET_PLAYER_DT * 2.f;

	if (m_attackCorrectingTimer > 1.f)
	{
		m_isAttackCorrecting = false;
		return;
	}

	m_rotateYDst += m_attackCorrectingAngle * GET_PLAYER_DT * 2.f;
}

void CStageCameraMan::OnTargetChasing()
{
	auto pCT = CStageControlTower::GetInstance();
	
	m_targetingTimer += GET_PLAYER_DT;

	if (m_targetingTimer > 3.f || !pCT->GetCurrentTarget())
	{
		SetIsTargeting(false);
		m_targetingTimer = 0.f;
		return;
	}

	_float3 actorPos = pCT->GetCurrentActor()->GetTransform()->GetPosition();
	_float3 targetPos = pCT->GetCurrentTarget()->GetTransform()->GetPosition();

	_float3 dir = targetPos - actorPos;
	_float distance = D3DXVec3Length(&dir) * m_targetingMidRatio;

	D3DXVec3Normalize(&dir, &dir);
	m_dstPivotPos = actorPos + dir * distance;
	
}

void CStageCameraMan::AppendHorizontalCorrecting()
{
	
	//D3DXQuaternionSlerp()
	if (m_isTargeting)
		return;

	_float rotateAngle = 45.f;
	bool isCorrecting = false;


	if (Engine::IMKEY_PRESS(StageKey_Move_Left))
	{
		if (m_prevMoveKey != StageKey_Move_Left)
		{
			m_rotateLerpStart = m_spCamera->GetLookAngleUp();
			m_speedIncreaseTimer = 0.f;
		}
		isCorrecting = true;
		m_rotateYDst -= D3DXToRadian(rotateAngle) * GET_PLAYER_DT * m_speedIncreaseTimer;
		m_prevMoveKey = StageKey_Move_Left;
	}

	if (Engine::IMKEY_PRESS(StageKey_Move_Right))
	{
		if (m_prevMoveKey != StageKey_Move_Right)
		{
			m_rotateLerpStart = m_spCamera->GetLookAngleUp();
			m_speedIncreaseTimer = 0.f;
		}
		isCorrecting = true;
		m_rotateYDst += D3DXToRadian(rotateAngle) * GET_PLAYER_DT * m_speedIncreaseTimer;
		m_prevMoveKey = StageKey_Move_Right;
	}

	if (!isCorrecting)
	{
		if (m_speedIncreaseTimer > 0.f)
		{
			m_speedIncreaseTimer -= GET_PLAYER_DT * 2.f;

			if(m_prevMoveKey == StageKey_Move_Left)
				m_rotateYDst -= D3DXToRadian(rotateAngle) * GET_PLAYER_DT * m_speedIncreaseTimer;
			else if (m_prevMoveKey == StageKey_Move_Right)
				m_rotateYDst += D3DXToRadian(rotateAngle) * GET_PLAYER_DT * m_speedIncreaseTimer;
		}
		else
		{
			m_speedIncreaseTimer = 0.f;
			return;
		}
	}
	else
	{
		if (m_speedIncreaseTimer < 1.f)
			m_speedIncreaseTimer += GET_PLAYER_DT * 1.f;
		else
			m_speedIncreaseTimer = 1.f;

	}

	RotateCameraHorizontal();
}

void CStageCameraMan::RotateCameraHorizontal()
{
	_float angle = m_rotateYDst - m_rotateLerpStart;
	if (angle < 0.5f)
	{
		m_rotateLerpStart = m_rotateYDst;
		m_spCamera->SetLookAngleUp(m_rotateYDst);
		return;
	}

	_float p1 = m_rotateLerpStart;
	_float p2 = m_rotateYDst;

	_float p1Weight = p1 * sinf(angle * (1.f - GET_PLAYER_DT)) / sinf(angle);
	_float p2Weight = p2 * sinf(angle * GET_PLAYER_DT) / sinf(angle);


	_float lerpPoint = p1Weight + p2Weight;

	m_spCamera->SetLookAngleUp(lerpPoint);
	if (m_speedIncreaseTimer == 1.f)
		m_rotateLerpStart = lerpPoint;
}

void CStageCameraMan::AppendPosYCorrecting()
{
	auto pCT = CStageControlTower::GetInstance();

	_float curYOffset = pCT->GetCurrentActor()->GetMesh()->GetHalfYOffset();

	_uint curValkyrie = pCT->GetCurrentActor()->GetStat()->GetType();

	if (m_prevValkyrie == curValkyrie)
	{
		_float curActorY = pCT->GetCurrentActor()->GetTransform()->GetPosition().y;
		_float realYPos = curYOffset - pCT->GetCurrentActor()->GetDefaultOffset();

		m_dstPivotPos.y = curActorY + realYPos;

	}
	else
	{
		m_prevValkyrie = curValkyrie;
	}
	m_prevYOffset = curYOffset;

}

bool CStageCameraMan::MouseControlMode()
{
	if (Engine::IMKEY_PRESS(MOUSE_RIGHT))
	{
		m_spCamera->SetRightClicked(true);
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_rotateYDst = m_spCamera->GetLookAngleUp();

		ChangeShot();
		SetIsTargeting(false);
		return true;
	}
	else
	{
		m_spCamera->SetRightClicked(false);
		return false;
	}
}

void CStageCameraMan::ManualControlMode()
{
	ShowMouseCursor();

	m_manualControl = false;


	if (Engine::IMKEY_PRESS(StageKey_CamRotateLeft))
	{
		m_rotateYDst -= m_rotateSpeed;
		m_enterAutoTimer = 0.f;

		m_rotateLerpTimer = 0.5f;
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
		m_isTargeting = false;
	}
	if (Engine::IMKEY_PRESS(StageKey_CamRotateRight))
	{
		m_rotateYDst += m_rotateSpeed;
		m_enterAutoTimer = 0.f;


		m_rotateLerpTimer = 0.5f;
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		m_manualControl = true;
		m_isTargeting = false;
	}

	m_rotateLerpTimer += GET_PLAYER_DT;
	if (m_rotateLerpTimer > 1.f)
	{
		m_spCamera->SetLookAngleUp(m_rotateYDst);
		m_rotateLerpStart = m_spCamera->GetLookAngleUp();
		return;
	}

	float inverseRate = 1.f - m_rotateLerpTimer;
	float sLerpTimer = 1.f - inverseRate * inverseRate;

	RotateCameraHorizontal();
}

void CStageCameraMan::AutoControlMode()
{
	HideMouseCursor();

	if (m_enterAutoTimer < 1.f)
	{
		m_enterAutoTimer += GET_PLAYER_DT;
		m_speedIncreaseTimer = 0.f;
		return;
	}

	AppendHorizontalCorrecting();
	AppendAttackDirectionCorrecting();

	ChangeShot();
	
}

void CStageCameraMan::ReturnBeforShaking()
{
	auto camTr = m_spCamera->GetTransform();

	if (m_pCameraShake->IsShaking())
	{
		camTr->AddPosition(-m_pCameraShake->GetLocationOscilation());
		camTr->SetPosition(m_noShakeRot);
	}
}

void CStageCameraMan::ApplyShaking()
{
	auto camTr = m_spCamera->GetTransform();

	if (m_pCameraShake->IsShaking())
	{
		m_pCameraShake->PlayShake();

		m_noShakePos = m_spCamera->GetShakePosOffset();
		m_noShakeRot = camTr->GetRotation();	// 회전값 기억

		m_spCamera->SetShakePosOffset(m_pCameraShake->GetLocationOscilation());

		_float3 rotOscilation = m_pCameraShake->GetRotateOscilation();
		camTr->AddRotation(rotOscilation);

		m_spCamera->SetLookAngleRight(m_spCamera->GetLookAngleRight() + rotOscilation.x);
		m_spCamera->SetLookAngleUp(m_spCamera->GetLookAngleUp() + rotOscilation.y);
		m_spCamera->SetLookAngleForward(m_spCamera->GetLookAngleForward() + rotOscilation.z);
		// 이거 하고 나서 카메라 트랜스폼 업데이트 해야함
	}
	else
	{
		m_spCamera->SetShakePosOffset(ZERO_VECTOR);
	}
}

void CStageCameraMan::ShakeCamera_Low(_float3 eventPos)
{
	m_pCameraShake->Preset_LowAttack(eventPos);
}

void CStageCameraMan::ShakeCamera_Kiana_ForwardAttack()
{
	m_pCameraShake->Preset_Kiana_ForwardAttack();
}

void CStageCameraMan::ShakeCamera_Kiana_Claw5()
{
	m_pCameraShake->Preset_Kiana_Claw5();
}

void CStageCameraMan::ShakeCamera_Kiana_Run()
{
}

void CStageCameraMan::ShakeCamera_Theresa_Charge1Impact(_float3 eventPos)
{
	m_pCameraShake->Preset_Theresa_Charge1Impact(eventPos);
}

void CStageCameraMan::ShakeCamera_Theresa_Charge2Impact(_float3 eventPos)
{
	m_pCameraShake->Preset_Theresa_Charge2Impact(eventPos);
}

void CStageCameraMan::ShakeCamera_Theresa_CrossImpact(_float3 eventPos)
{
	m_pCameraShake->Preset_Theresa_CrossImpact(eventPos);
}


bool CStageCameraMan::CheckNoAction()
{
	if (!Engine::IMKEY_PRESS(StageKey_Move_Forward) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Left) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Right) &&
		!Engine::IMKEY_PRESS(StageKey_Move_Back) &&
		!Engine::IMKEY_PRESS(StageKey_Attack) &&
		!Engine::IMKEY_PRESS(StageKey_Evade) &&
		!Engine::IMKEY_PRESS(StageKey_WeaponSkill) &&
		!Engine::IMKEY_PRESS(StageKey_Switch_1) &&
		!Engine::IMKEY_PRESS(StageKey_Switch_2) &&
		!Engine::IMKEY_PRESS(StageKey_Ult))
	{
		return true;
	}
	return false;
}

void CStageCameraMan::ShowMouseCursor()
{
	if (Engine::CInputManager::GetInstance()->GetMousePosDelta() != ZERO_VECTOR)
	{
		m_hideCursorTimer = 0.f;
		if (!m_cursorOn)
		{
			m_cursorOn = true;
			ShowCursor(true);
		}
	}
}

void CStageCameraMan::HideMouseCursor()
{
	m_hideCursorTimer += GET_PLAYER_DT;

	if (m_cursorOn && m_hideCursorTimer > 3.f)
	{
		m_cursorOn = false;
		ShowCursor(false);
		if (m_whyCursorOffOneMore)
		{
			m_whyCursorOffOneMore = false;
			ShowCursor(false);
		}
	}
}

void CStageCameraMan::SetCamera(SP(Engine::CCamera) spCamera)
{
	m_spCamera = spCamera;
}

void CStageCameraMan::SetIsVertCorrecting(_bool value)
{
	m_isVertCorrecting = value;

	if (value)
	{
		_float curYOffset = CStageControlTower::GetInstance()->GetCurrentActor()->GetMesh()->GetHalfYOffset();
		m_prevYOffset = curYOffset;
	}
}
