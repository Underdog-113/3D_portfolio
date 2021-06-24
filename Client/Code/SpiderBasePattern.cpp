#include "stdafx.h"
#include "SpiderBasePattern.h"

#include "FSM_SpiderC.h"
#include "FSMDefine_Spider.h"
#include "MO_Spider.h"

#include "StageControlTower.h"
#include "Valkyrie.h"
#include "DynamicMeshData.h"
#include "AttackBall.h"
#include "AttackRange_Circle.h"

CSpiderBasePattern::CSpiderBasePattern()
{
}

CSpiderBasePattern::~CSpiderBasePattern()
{
}

void CSpiderBasePattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_SpiderC) fsm = pOwner->GetComponent<CFSM_SpiderC>();

	if (Name_Attack_1 != fsm->GetCurStateString())
	{
		static_cast<CMO_Spider*>(pOwner)->ChaseTarget(tPos);
	}

	// ��밡 ���� ���� ���̰�
	if (len > m_atkDis)
	{
		// ���� ��� ���¸� �̵� �ִϷ� ����
		if (Name_StandBy == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Forward);
		}
		// ���� �̵� ���̶��
		else if (Name_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
	}
	// ��밡 ���� ���� ���̰�
	else if (len <= m_atkDis)
	{
		// ���� �̵� ���¶�� ����
		if (Name_Walk_Forward == fsm->GetCurStateString() && fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Attack_1);
			SP(Engine::CObject) spMeshEffect
				= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"AttackRange_Circle", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");

			Engine::CSoundManager::GetInstance()->StopSound((_uint)Engine::EChannelID::GANESHA_JUMPBACK);
			Engine::CSoundManager::GetInstance()->StartSound(L"Ganesha_JumpBack.wav", (_uint)Engine::EChannelID::GANESHA_JUMPBACK);

			_float3 mPos = pOwner->GetTransform()->GetPosition();

			spMeshEffect->GetTransform()->SetPosition(mPos);
		}
	}

	// ����1 ���°� �Ϸ�Ǹ� attackball off �� ������Ʈ ����
	if (Name_Attack_1 == fsm->GetCurStateString() && 0.9f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Spider*>(pOwner)->UnActiveAttackBall();
		pOwner->SetDeleteThis(true);
	}
	// ����1 ���¶��
	else if (Name_Attack_1 == fsm->GetCurStateString() && 0.8f <= fsm->GetDM()->GetAniTimeline())
	{
		m_explosionPosMat = pOwner->GetTransform()->GetWorldMatrix();
		static_cast<CMO_Spider*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_explosionPosMat, 3.f);
	}
}

SP(CSpiderBasePattern) CSpiderBasePattern::Create()
{
	SP(CSpiderBasePattern) spInstance(new CSpiderBasePattern, Engine::SmartDeleter<CSpiderBasePattern>);

	return spInstance;
}