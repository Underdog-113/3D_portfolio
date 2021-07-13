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

	/************************* Sound */
	// 공격1 상태 중 사운드 재생
	if (Name_Attack_1 == fsm->GetCurStateString() &&
		0.8f > fsm->GetDM()->GetAniTimeline() &&
		true == pOwner->GetIsEnabled())
	{
		PatternRepeatSound(L"Spider_Boom_Ready.wav", pOwner, 0.1f);
	}

	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 대기 상태면 이동 애니로 변경
		if (Name_StandBy == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Walk_Forward);
			PatternPlaySound(L"Spider_Run", pOwner);
		}
		// 내가 이동 중이라면
		else if (Name_Walk_Forward == fsm->GetCurStateString())
		{
			_float3 dir = tPos - mPos;

			mPos += *D3DXVec3Normalize(&dir, &dir) * GET_DT;
			pOwner->GetTransform()->SetPosition(mPos);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 이동, 대기 상태라면 공격
		if ((Name_Walk_Forward == fsm->GetCurStateString() ||
			Name_StandBy == fsm->GetCurStateString()) &&
			fsm->GetDM()->IsAnimationEnd())
		{
			fsm->ChangeState(Name_Attack_1);

			// effect
			SP(Engine::CObject) spMeshEffect
				= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"AttackRange_Circle", true, (_int)Engine::ELayerID::Effect, L"MeshEffect");

			_float3 mPos = pOwner->GetTransform()->GetPosition();
			spMeshEffect->GetComponent<Engine::CTransformC>()->SetPosition(mPos);
			spMeshEffect->GetComponent<Engine::CTransformC>()->AddPositionY(0.1f);
			spMeshEffect->GetComponent<Engine::CTransformC>()->SetSize(_float3(0.2f, 0.2f, 0.2f));

			return;
		}
	}

	/************************* AttackBall */
	// 공격1 상태가 완료되면 attackball off 및 오브젝트 제거
	if (Name_Attack_1 == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline())
	{
		static_cast<CMO_Spider*>(pOwner)->UnActiveAttackBall();
		pOwner->SetIsEnabled(false);
		m_onEffect = true;

		// effect
		m_spSoftEffect
			= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SpiderExplosion", true);
		//m_spSoftEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Explosion");
		//m_spSoftEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Explosion");
		m_spSoftEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
		m_spSoftEffect->GetTransform()->SetPosition(mPos);
		//m_spSoftEffect->GetTransform()->SetPositionX(mPos.x - 0.1f);
		//m_spSoftEffect->GetTransform()->SetPositionY(mPos.y + 0.5f);
		//m_spSoftEffect->GetTransform()->SetSize(11.f, 9.f, 0.f);
	}
	// 공격1 상태라면
	else if (Name_Attack_1 == fsm->GetCurStateString() &&
		0.88f <= fsm->GetDM()->GetAniTimeline())
	{
		//pOwner->OnDisable();
		m_explosionPosMat = pOwner->GetTransform()->GetWorldMatrix();
		static_cast<CMO_Spider*>(pOwner)->ActiveAttackBall(1.f, HitInfo::Str_High, HitInfo::CC_None, &m_explosionPosMat, 2.f);

		if (false == m_onSound)
		{
			PatternPlaySound(L"Spider_Boom.wav", pOwner);
			m_onSound = true;
		}
	}
	
	/************************* Delete this */
	if (Name_Attack_1 == fsm->GetCurStateString() &&
		true == m_onEffect)
	{
		if (true == m_spSoftEffect->GetDeleteThis())
		{
			static_cast<CMO_Spider*>(pOwner)->GetStat()->SetCurHp(0.f);
			pOwner->SetDeleteThis(true);
			m_onEffect = false;
		}
	}
}

SP(CSpiderBasePattern) CSpiderBasePattern::Create()
{
	SP(CSpiderBasePattern) spInstance(new CSpiderBasePattern, Engine::SmartDeleter<CSpiderBasePattern>);

	return spInstance;
}