#include "stdafx.h"
#include "GaneshaBasePattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CGaneshaBasePattern::CGaneshaBasePattern()
{
}

CGaneshaBasePattern::~CGaneshaBasePattern()
{
}

void CGaneshaBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	if (Name_Ganesha_Attack01 != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	/************************* Sound */
	// attack sound
	if (Name_Ganesha_Attack01 == fsm->GetCurStateString() &&
		0.4f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternPlaySound(L"Ganesha_Upper.wav", pOwner);
		m_onSound = true;
	}
	// run start sound
	else if (Name_Ganesha_Run == fsm->GetCurStateString())
	{
		if (false == m_onRunStart)
		{
			PatternPlaySound(L"Ganesha_Run_Start.wav", pOwner);
			m_onRunStart = true;
		}
		else if (true == m_onRunStart && false == PatternSoundEnd(pOwner))
		{
			PatternRepeatSound(L"Ganesha_Run.wav", pOwner, 0.03f);
		}
	}

	/************************* Range */
	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ����1 ���¸�
		if (Name_Ganesha_Attack01 == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
			PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
			m_onSound = false;
			m_onRunStart = false;
		}
		// ���� ��� ���¸� �̵� �ִϷ� ����
		else if (Name_Ganesha_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Run);
		}
		// ���� �̵� ���̶��
		else if (Name_Ganesha_Run == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵�, ��� ���¶�� ����
		if ((Name_Ganesha_Run == fsm->GetCurStateString() ||
			Name_Ganesha_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Attack01);
			PatternStopSound(pOwner);
		}
	}

	/************************* JumpBack */
	// ���� ����1 ���¶�� �ڷ� �̵� ���·� ����
	if (Name_Ganesha_Attack01 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
		m_walkReady = false;
		m_onSound = false;
		m_onRunStart = false;
	}
	// ���� �ڷ� �̵� ���̶��
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() && false == m_walkReady)
	{
		_float3 dir = tPos - mPos;

		mPos -= *D3DXVec3Normalize(&dir, &dir) * GET_DT;
		pOwner->GetTransform()->SetPosition(mPos);
	}
	// ���� �ڷ� �̵��� �����ٸ�
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_walkReady)
	{
		++m_jumpCnt;

		if (2 != m_jumpCnt)
		{
			m_walkReady = false;
		}
		else
		{
			fsm->ChangeState(Name_Ganesha_StandBy);
			m_jumpCnt = 0;
			pOwner->GetComponent<CPatternMachineC>()->SetOnBase(false);
		}

		// effect
		_float fX = 0;
		for (_int i = 0; i < 8; ++i)
		{
		 	SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_SmokeEff", true);
		 
		 	// Ganesha Pos X + fX 
		 	spObj->GetTransform()->SetPositionX(mPos.x + fX - 1.3f);
			spObj->GetTransform()->SetPositionY(mPos.y + 0.1f);
		 	spObj->GetTransform()->SetPositionZ(mPos.z + (rand() % 2) - 1.f );			
		 	fX += 0.5f;
		}
	}

	/************************* AttackBall */
	// ���� ���� ���°�, ������ �� ���ú� �����
	if (Name_Ganesha_Attack01 == fsm->GetCurStateString() && 0.59f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	}
	// ���� ���� ���°�, ������ �� ���ú� ����
	else if (Name_Ganesha_Attack01 == fsm->GetCurStateString() && 0.49f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x * 1.f);
		m_atkMat._43 += (m_atkDis * look.z * 1.f);

		static_cast<CMB_Ganesha*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_Low, HitInfo::CC_None, &m_atkMat, 0.45f);
		//static_cast<Engine::CSphereCollider*>(static_cast<CMB_Ganesha*>(pOwner)->GetAttackBall()->GetCollision()->GetColliders()[0].get())->SetRadius(0.3f);
	}
} 

SP(CGaneshaBasePattern) CGaneshaBasePattern::Create()
{
	SP(CGaneshaBasePattern) spInstance(new CGaneshaBasePattern, Engine::SmartDeleter<CGaneshaBasePattern>);

	return spInstance;
}