#include "stdafx.h"
#include "RobotDiePattern.h"

#include "FSM_RobotC.h"
#include "FSMDefine_Robot.h"
#include "MO_Robot.h"

#include "AniCtrl.h"

CRobotDiePattern::CRobotDiePattern()
{
}

CRobotDiePattern::~CRobotDiePattern()
{
}

void CRobotDiePattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_RobotC) fsm = pOwner->GetComponent<CFSM_RobotC>();

	/************************* Sound */
	if (Name_Die == fsm->GetCurStateString() &&
		0.46f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onSound)
	{
		PatternPlaySound(L"Robot_Dead.wav", pOwner);
		m_onSound = true;
	}

	/************************* Pattern */
	// 내가 hp가 0이 되면
	if (Name_Die != fsm->GetCurStateString() &&
		0 >= static_cast<CMonster*>(pOwner)->GetStat()->GetCurHp())
	{
		fsm->ChangeState(Name_Die);
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.6f);
	}
	// die 애니가 끝나면
	else if (Name_Die == fsm->GetCurStateString() &&
		0.95f <= fsm->GetDM()->GetAniTimeline())
	{
		fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		static_cast<CMO_Robot*>(pOwner)->GetPlane()->SetDeleteThis(true);
		pOwner->SetIsEnabled(false);
	}

	/************************* Effect */
	if (Name_Die == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() &&
		0.91f > fsm->GetDM()->GetAniTimeline())
	{
		_float3 mPos = pOwner->GetTransform()->GetPosition();

		m_spSoftEffect
			= Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"SpiderExplosion", true);
		m_spSoftEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Explosion");
		m_spSoftEffect->GetComponent<Engine::CTextureC>()->AddTexture(L"Explosion");
		m_spSoftEffect->GetComponent<Engine::CShaderC>()->AddShader((_int)EShaderID::SoftEffectShader);
		m_spSoftEffect->GetTransform()->SetPosition(mPos);
		m_spSoftEffect->GetTransform()->SetPositionX(mPos.x - 0.3f);
		m_spSoftEffect->GetTransform()->SetPositionY(mPos.y + 1.5f);
		m_spSoftEffect->GetTransform()->SetSize(16.f, 14.f, 0.f);
	}

	/************************* Delete this */
	if (Name_Die == fsm->GetCurStateString() &&
		0.97f <= fsm->GetDM()->GetAniTimeline())
	{
		if (true == m_spSoftEffect->GetDeleteThis())
		{
			pOwner->SetDeleteThis(true);
		}
	}
}

SP(CRobotDiePattern) CRobotDiePattern::Create()
{
	SP(CRobotDiePattern) spInstance(new CRobotDiePattern, Engine::SmartDeleter<CRobotDiePattern>);

	return spInstance;
}