#include "stdafx.h"
#include "BronyaThrow1Pattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "StateMachineC.h"
#include "Valkyrie.h" 
#include "DynamicMeshData.h"
#include "AniCtrl.h"
#include "PatternMachineC.h"
#include "AttackBall.h"

#include "BronyaGrenade.h"

CBronyaThrow1Pattern::CBronyaThrow1Pattern()
{
	m_pAttackBallMat = new _mat;
}

CBronyaThrow1Pattern::~CBronyaThrow1Pattern()
{
	Engine::SafeDelete(m_pAttackBallMat);
}

void CBronyaThrow1Pattern::Pattern(Engine::CObject* pOwner)
{
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	CoolTime(m_walkTime, m_walkCool, m_walkReady);

	/************************* Fast Idle */
	if (Name_IDLE == fsm->GetCurStateString() &&
		false == m_onFastIdle)
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(2.f);
		m_onFastIdle = true;
	}
	else if (Name_IDLE != fsm->GetCurStateString() &&
		true == m_onFastIdle)
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		m_onFastIdle = false;
	}

	/************************* Fast Run */
	if (Name_Run == fsm->GetCurStateString())
	{
		_float3 dir = tPos - mPos;
		D3DXVec3Normalize(&dir, &dir);

		pOwner->GetTransform()->AddPosition(dir * 0.15f);
	}


	/************************* Range */
	// 상대가 공격 범위 밖이고
	if (len > m_atkDis)
	{
		// 내가 대기 상태가 끝났다면
		if (Name_IDLE == fsm->GetCurStateString() &&
			fsm->GetDM()->IsAnimationEnd())
		{
			// 이동 상태로 변경
			fsm->ChangeState(Name_Run);
		}
	}
	// 상대가 공격 범위 안이고
	else if (len <= m_atkDis)
	{
		// 내가 대기 상태라면
		if (Name_IDLE == fsm->GetCurStateString() ||
			Name_Run == fsm->GetCurStateString())
		{
			// throw2 상태로 변경
			fsm->ChangeState(Name_Throw_2);
			m_onAtkBall = false;
			m_onSmokeEffect = false;

			return;
		}
	}

	/************************* throw2 */
	// throw2 상태가 끝날 때 쯤 스모크 이펙트 생성
	if (Name_Throw_2 == fsm->GetCurStateString() &&
		0.5f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSmokeEffect)
	{
		// smoke effect
		for (_int i = 0; i < 3; ++i)
		{
			_int iRand = rand() % 4;

			switch (iRand)
			{
			case 0:
				SetupSmokeEffectPos(L"fx_snowfield_fog03", mPos, 0.3f);
				break;
			case 1:
				SetupSmokeEffectPos(L"fx_snowfield_fog03", mPos, 0.7f);
				break;
			case 2:
				SetupSmokeEffectPos(L"fx_snowfield_fog03", mPos, 0.2f);
				break;
			case 3:
				SetupSmokeEffectPos(L"fx_snowfield_fog03", mPos, 0.2f);
				break; 			
			}
		}

		m_onSmokeEffect = true;

		return;
	}
	// throw2 상태가 끝났다면
	else if (Name_Throw_2 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// throw1 상태로 변경
		fsm->ChangeState(Name_Throw_1);
		return;
	}

	/************************* throw1 End */
	// 내가 throw1 상태가 끝났다면
	if (Name_Throw_1 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd())
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
		pOwner->GetComponent<CPatternMachineC>()->SetOnSelect(false);

		return;
	}

	/************************* throw grenade */
	if (Name_Throw_1 == fsm->GetCurStateString() &&
		0.48f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onAtkBall)
	{
		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_R_Hand")->CombinedTransformMatrix;
		GetRHandMat(pOwner, m_pAttackBallMat);

		for (_int i = 0; i < m_grenadeCnt; ++i)
		{
			auto& grenade = static_cast<CMB_Bronya*>(pOwner)->GetGrenades()[i];

			grenade->SetIndex(i);
			grenade->GetTransform()->SetPosition(_float3(m_pAttackBallMat->_41, m_pAttackBallMat->_42, m_pAttackBallMat->_43));

			m_dir = mPos - tPos;
			D3DXVec3Normalize(&m_dir, &m_dir);

			grenade->GetTransform()->SetForward(m_dir);
			grenade->SetDir(-m_dir);
			grenade->SetIsEnabled(true);
			grenade->GetRigidBody()->SetUseGravity(true);
			grenade->GetRigidBody()->SetIsEnabled(true);
			grenade->GetCollision()->SetIsEnabled(true);
		}

		m_onAtkBall = true;
		PatternPlaySound(L"Bronya_Grenade_1.wav", pOwner);
	}

}

SP(CBronyaThrow1Pattern) CBronyaThrow1Pattern::Create()
{
	SP(CBronyaThrow1Pattern) spInstance(new CBronyaThrow1Pattern, Engine::SmartDeleter<CBronyaThrow1Pattern>);

	return spInstance;
}

void CBronyaThrow1Pattern::GetRHandMat(Engine::CObject * pOwner, _mat * pAtkBall)
{
	_mat combMat = *m_pRHand;
	_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	*pAtkBall = combMat * pOwner->GetTransform()->GetWorldMatrix();
}

void CBronyaThrow1Pattern::SetupSmokeEffectPos(std::wstring texName, _float3 mPos, _float addY)
{
	SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_RandomSmoke", true);
	_float3 pos = { mPos.x + _float(rand() % 3 - 1.5f),
					mPos.y + _float(rand() % 1) + addY,
					mPos.z + _float(rand() % 3) };

	effect->GetTransform()->SetPosition(pos);
	effect->GetComponent<Engine::CTextureC>()->AddTexture(texName);
	effect->GetComponent<Engine::CTextureC>()->AddTexture(texName);
}
