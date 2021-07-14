#include "stdafx.h"
#include "RobotAttack2Pattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBox.h"
#include "StageControlTower.h"

CRobotAttack2Pattern::CRobotAttack2Pattern()
{
}

CRobotAttack2Pattern::~CRobotAttack2Pattern()
{
}

void CRobotAttack2Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// 내가 상대를 추적
	if (Name_Attack_2 != fsm->GetCurStateString())
	{
		static_cast<CMO_Robot*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	//// run start sound
	//if ((Name_WALK_FORWARD == fsm->GetCurStateString() ||
	//	 Name_RUN_B == fsm->GetCurStateString()) &&
	//	 true == m_onWalk)
	//{
	//	PatternRepeatSound(m_curMoveSound, pOwner, 0.4f);
	//}
	//else if ((Name_RUN_F == fsm->GetCurStateString() ||
	//		  Name_RUN_B == fsm->GetCurStateString()) &&
	//		  false == m_onWalk)
	//{
	//	PatternStopSound(pOwner);
	//}

	/************************* Range */
//	// 상대가 공격 거리를 벗어났다면
// 	if (len > m_atkDis)
// 	{
//		// 내가 Attack_2 상태면
//		if (Name_Attack_2 == fsm->GetCurStateString() &&
//			fsm->GetDM()->IsAnimationEnd())
//		{
//			fsm->ChangeState(Name_Walk_Backward);
//		}
//		// 내가 대기 상태면 이동 애니로 변경
//		else if (Name_StandBy == fsm->GetCurStateString() &&
//			fsm->GetDM()->IsAnimationEnd())
//		{
//			fsm->ChangeState(Name_Walk_Forward);
//		}
// 	}
//	// 상대가 이동 범위 안이고
//	else if (len <= m_atkDis)
//	{
//		// 내가 이동, 대기 상태가 끝났다면
//		if ((Name_StandBy == fsm->GetCurStateString() ||
//			Name_Walk_Forward == fsm->GetCurStateString()) &&
//			fsm->GetDM()->IsAnimationEnd())
//		{
//			fsm->ChangeState(Name_Attack_2);
//		}
//	}
//
//	/************************* Attack_2 */
//	// 내가 Attack_2 상태가 끝났다면
//	if (Name_Attack_2 == fsm->GetCurStateString() &&
//		fsm->GetDM()->IsAnimationEnd() &&
//		true == m_walkReady)
//	{
//		fsm->ChangeState(Name_Walk_Backward);
//		m_walkReady = false;
//	}
//// 	// 내가 Walk Backward 상태라면 
//// 	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
//// 		false == m_walkReady)
//// 	{
//// 		_float3 dir = tPos - mPos;
//// 		dir.y = 0;
//// 		D3DXVec3Normalize(&dir, &dir);
//// 
//// 		pOwner->GetTransform()->SetSlerpOn(true);
//// 		pOwner->GetTransform()->SetGoalForward(dir);
//// 	}
//	// 내가 Walk Backward 상태가 끝났다면
//	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
//		fsm->GetDM()->IsAnimationEnd() &&
//		true == m_walkReady)
//	{
//		fsm->ChangeState(Name_StandBy);
//		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
//	}
//
//	/************************* Walk */
//	// 내가 이동 중이라면
//	if (Name_Walk_Forward == fsm->GetCurStateString() &&
//		fsm->GetDM()->IsAnimationEnd())
//	{
//		_float3 dir = tPos - mPos;
//
//		mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
//		pOwner->GetTransform()->SetPosition(mPos);
//	}
//	// 내가 뒤로 이동 중이라면
//	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
//		fsm->GetDM()->IsAnimationEnd() &&
//		false == m_walkReady)
//	{
//		_float3 dir = tPos - mPos;
//
//		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
//		pOwner->GetTransform()->SetPosition(mPos);
//	}
//	// 내가 뒤로 이동이 끝났다면
//	else if (Name_Walk_Backward == fsm->GetCurStateString() &&
//		fsm->GetDM()->IsAnimationEnd() &&
//		true == m_walkReady)
//	{
//		fsm->ChangeState(Name_StandBy);
//		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
//	}



	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 공격2 상태가 끝났다면
		if (Name_Attack_2 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Backward);
		}
		// 내가 대기 상태가 끝났다면
		else if (Name_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Forward);
		}
		// 내가 이동 중이라면
		else if (Name_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동 중이라면
		else if (Name_Walk_Backward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// 내가 뒤로 이동이 끝났다면
		else if (Name_Walk_Backward == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd() &&
			true == m_walkReady)
		{
			fsm->ChangeState(Name_Walk_Forward);
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태가 끝났다면
		if ((Name_Walk_Forward == fsm->GetCurStateString() ||
			Name_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Attack_2);
			m_onEffect = false;
			return;
		}
		// 내가 공격1 상태가 끝났다면
		else if (Name_Attack_2 == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Backward);
			m_walkReady = false;
		}
	}

 	/************************* AttackBox */
	// attack2 상태가 완료되면 attackbox off
	if (Name_Attack_2 == fsm->GetCurStateString() && 
		0.7f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onAtkBall)
	{
		m_onAtkBall = false;
		static_cast<CMO_Robot*>(pOwner)->UnActiveAttackBall();
	}
	// attack2 상태라면
	else if (Name_Attack_2 == fsm->GetCurStateString() &&
		0.65f <= fsm->GetDM()->GetAniTimeline() &&
		0.7f > fsm->GetDM()->GetAniTimeline() &&
		false == m_onAtkBall)
	{
		m_onAtkBall = true;
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		static_cast<CMO_Robot*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 1.7f);
	}

	/************************* Effect */
	// attack2 상태라면
	if (Name_Attack_2 == fsm->GetCurStateString() &&
		0.7f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onEffect)
	{
		m_spImpactEffect = 
			Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Robot_Impact", true);

		m_spImpactEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Explosion");
		m_spImpactEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Explosion");
		m_spImpactEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
		m_spImpactEffect->GetTransform()->SetPosition(mPos);
		m_spImpactEffect->GetTransform()->SetRotationY(0.f);
		//m_spImpactEffect->GetTransform()->SetPositionX(mPos.x - 0.3f);
		//m_spImpactEffect->GetTransform()->SetPositionY(mPos.y + 1.5f);
		m_spImpactEffect->GetTransform()->SetSize(10.f, 10.f, 10.f);

		//// 주먹 뼈 찾기
		//m_pLeftUpperArm = &fsm->GetDM()->GetFrameByName("Bip001_L_Hand")->CombinedTransformMatrix;

		//_mat combMat = *m_pLeftUpperArm;
		//_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
		//combMat._41 -= rootMotionPos.x;
		//combMat._43 -= rootMotionPos.z;
		//_mat realPosMat = combMat * pOwner->GetTransform()->GetWorldMatrix();
		//_float3 pos = { realPosMat._41, realPosMat._42, realPosMat._43 };
		//m_spImpactEffect->GetTransform()->SetPosition(pos);
		//m_spImpactEffect->GetTransform()->AddPositionY(0.7f);

		m_spImpactEffect->GetTransform()->SetPosition(mPos);

		m_onEffect = true;
	}
}

SP(CRobotAttack2Pattern) CRobotAttack2Pattern::Create()
{
	SP(CRobotAttack2Pattern) spInstance(new CRobotAttack2Pattern, Engine::SmartDeleter<CRobotAttack2Pattern>);

	return spInstance;
}
