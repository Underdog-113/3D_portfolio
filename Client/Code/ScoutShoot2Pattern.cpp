#include "stdafx.h"
#include "ScoutShoot2Pattern.h"

#include "FSM_ScoutC.h"
#include "FSMDefine_Scout.h"
#include "MO_Scout.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBox.h"
#include "StageControlTower.h"

CScoutShoot2Pattern::CScoutShoot2Pattern()
{
}

CScoutShoot2Pattern::~CScoutShoot2Pattern()
{
}

void CScoutShoot2Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_ScoutC) fsm = pOwner->GetComponent<CFSM_ScoutC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	// ���� shoot2 ���°� �ƴϸ� ��븦 ����
	if (Name_SHOOT_2 != fsm->GetCurStateString())
	{
		static_cast<CMO_Scout*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// burst sound
// 	if (Name_Ganesha_Burst01 == fsm->GetCurStateString() &&
// 		0.3f <= fsm->GetDM()->GetAniTimeline() &&
// 		false == m_onSound)
// 	{
// 		PatternPlaySound(L"Ganesha_Laser.wav", pOwner);
// 		m_onSound = true;
// 	}
// 	// run start sound
// 	else if (Name_Ganesha_Run == fsm->GetCurStateString())
// 	{
// 		if (false == m_onRunStart)
// 		{
// 			PatternPlaySound(L"Ganesha_Run_Start.wav", pOwner);
// 			m_onRunStart = true;
// 		}
// 		else if (true == m_onRunStart && false == PatternSoundEnd(pOwner))
// 		{
// 			PatternRepeatSound(L"Ganesha_Run.wav", pOwner, 0.03f);
// 		}
// 	}

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� shoot2 ���¸�
		if (Name_SHOOT_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_F);
		}
		// ���� ��� ���¸� �̵� �ִϷ� ����
		else if (Name_IDLE == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_F);
		}
		// ���� �̵� ���̶��

		else if (Name_RUN_F == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// ���� �ڷ� �̵� ���̶��
		else if (Name_RUN_B == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && false == m_walkReady)
		{
			_float3 dir = tPos - mPos;

			mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
		// ���� �ڷ� �̵��� �����ٸ�
		else if (Name_RUN_B == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd() && true == m_walkReady)
		{
			fsm->ChangeState(Name_RUN_F);
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵�, ��� ���¶�� ����
		if ((Name_RUN_F == fsm->GetCurStateString() ||
			Name_IDLE == fsm->GetCurStateString() ||
			Name_RUN_B == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_SHOOT_2);
			//		//PatternPlaySound(L"Sickle_Skill_0.wav", pOwner);
			//static_cast<CMO_Scout*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.3f);
		}
		// shoot1 ���¶�� �ڷ� �̵� ���·� ����
		else if (Name_SHOOT_2 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_RUN_B);
		}
	}

	///************************* AttackBall */
	//// ���� ���� ���°�, ������ �� ���ú� �����
	//if (Name_SHOOT_1 == fsm->GetCurStateString() && 0.47f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	static_cast<CMO_Scout*>(pOwner)->UnActiveAttackBall();
	//}
	//// ���� ���� ���°�, ������ �� ���ú� ����
	//else if (Name_SHOOT_1 == fsm->GetCurStateString() && 0.37f <= fsm->GetDM()->GetAniTimeline())
	//{
	//	m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

	//	_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
	//	D3DXVec3Normalize(&look, &look);

	//	m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
	//	m_atkMat._41 += (m_atkDis * look.x / 1.8f);
	//	m_atkMat._43 += (m_atkDis * look.z / 1.8f);

	//	static_cast<CMO_Scout*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.34f);
	//}
}

SP(CScoutShoot2Pattern) CScoutShoot2Pattern::Create()
{
	SP(CScoutShoot2Pattern) spInstance(new CScoutShoot2Pattern, Engine::SmartDeleter<CScoutShoot2Pattern>);

	return spInstance;
}