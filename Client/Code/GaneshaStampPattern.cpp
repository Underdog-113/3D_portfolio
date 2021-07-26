#include "stdafx.h"
#include "GaneshaStampPattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"
#include "MB_Ganesha.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

CGaneshaStampPattern::CGaneshaStampPattern()
{
}

CGaneshaStampPattern::~CGaneshaStampPattern()
{
}

void CGaneshaStampPattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();

	CoolTime(m_atkTime, m_atkCool, m_atkReady);
	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	if (Name_Ganesha_Stamp != fsm->GetCurStateString())
	{
		static_cast<CMB_Ganesha*>(pOwner)->ChaseTarget(tPos);
	}

	// stamp sound
	if (Name_Ganesha_Stamp == fsm->GetCurStateString() &&
		0.3f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternPlaySound(L"Ganesha_Stamp.wav", pOwner);
		m_onSound = true;
	}
	else if (Name_Ganesha_Stamp == fsm->GetCurStateString() &&
		0.05f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternRepeatSound(L"Ganesha_StandUp.wav", pOwner, 0.35f);
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

	// ��밡 stamp ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� stamp ���¸�
		if (Name_Ganesha_Stamp == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Ganesha_Jump_Back);
			PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
			m_onSound = false;
			m_onRunStart = false;
		}
		// ���� ��� ���¸� �̵� �ִϷ� ����
		else if (Name_Ganesha_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
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
	// ��밡 stamp ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵� ���¶�� stamp
		if ((Name_Ganesha_Run == fsm->GetCurStateString() ||
			Name_Ganesha_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);
			fsm->ChangeState(Name_Ganesha_Stamp);
			m_onEffect = true;
			return;
		}
	}

	// ���� stamp ���¶�� �ڷ� �̵�
	if (Name_Ganesha_Stamp == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);
		fsm->ChangeState(Name_Ganesha_Jump_Back);
		PatternPlaySound(L"Ganesha_JumpBack.wav", pOwner);
		m_walkReady = false;
		m_onSound = false;
		m_onRunStart = false;
		static_cast<CMonster*>(pOwner)->DeleteEffect(Effects::stamp);
		//m_spEffect->SetDeleteThis(true);
	}
	// ���� �ڷ� �̵� ���̶��
	else if (Name_Ganesha_Jump_Back == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_walkReady)
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
			pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);
		}

		// effect
		_float fX = 0;
		for (_int i = 0; i < 8; ++i)
		{
			SP(Engine::CObject) spObj = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_SmokeEff", true);

			// Ganesha Pos X + fX 
			spObj->GetTransform()->SetPositionX(mPos.x + fX - 0.3f);
			spObj->GetTransform()->SetPositionY(mPos.y + 0.1f);
			spObj->GetTransform()->SetPositionZ(mPos.z + (rand() % 2) - 0.5f);
			fX += 0.5f;
		}
	}

	// ���� stamp ���°�, ������ �� ���ú� �����
	if (Name_Ganesha_Stamp == fsm->GetCurStateString() &&
		0.5f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMB_Ganesha*>(pOwner)->UnActiveAttackBall();
	}
	// ���� stamp ���°�, ������ �� ���ú� ����
	else if (Name_Ganesha_Stamp == fsm->GetCurStateString() &&
		0.4f <= fsm->GetDM()->GetAniTimeline())
	{
		m_atkMat = pOwner->GetTransform()->GetWorldMatrix();

		_float3 look = _float3(m_atkMat._31, m_atkMat._32, m_atkMat._33);
		D3DXVec3Normalize(&look, &look);

		m_atkMat._42 += pOwner->GetComponent<Engine::CMeshC>()->GetHalfYOffset();
		m_atkMat._41 += (m_atkDis * look.x * 0.4f);
		m_atkMat._43 += (m_atkDis * look.z * 0.4f);

		static_cast<CMB_Ganesha*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_atkMat, 0.9f);
	}

	/************************* Effect */
	if (Name_Ganesha_Stamp == fsm->GetCurStateString() &&
		0.37f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onEffect)
	{
		m_onEffect = false;
		SP(Engine::CObject) effect =
			Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Impact_Eff", true);

		effect->GetTransform()->SetPosition(mPos);		
		effect->GetTransform()->SetSize(3.f, 3.f, 3.f);
		static_cast<CMonster*>(pOwner)->AddEffect(effect);
	} 
}

SP(CGaneshaStampPattern) CGaneshaStampPattern::Create()
{
	SP(CGaneshaStampPattern) spInstance(new CGaneshaStampPattern, Engine::SmartDeleter<CGaneshaStampPattern>);

	return spInstance;
}