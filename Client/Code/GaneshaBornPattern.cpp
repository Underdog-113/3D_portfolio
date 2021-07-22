#include "stdafx.h"
#include "GaneshaBornPattern.h"

#include "FSM_GaneshaC.h"
#include "FSMDefine_Ganesha.h"

#include "DynamicMeshData.h"
#include "PatternMachineC.h"
#include "Ganesha_Cinema_Dome.h"
#include "Bronya_Impact.h"
#include "Bronya_Impact_TripleRing.h"

#include "MovieDirector.h"

CGaneshaBornPattern::CGaneshaBornPattern()
{
}

CGaneshaBornPattern::~CGaneshaBornPattern()
{
}

void CGaneshaBornPattern::Pattern(Engine::CObject* pOwner)
{
	SP(CFSM_GaneshaC) fsm = pOwner->GetComponent<CFSM_GaneshaC>();
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos

	if (Name_Ganesha_Born == fsm->GetCurStateString() && 0.75f > fsm->GetDM()->GetAniTimeline())
	{
		pOwner->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(false);
		pOwner->GetComponent<Engine::CCollisionC>()->SetIsEnabled(false);
	}

	// 내가 born 상태이고, 애니가 끝났다면
	if (Name_Ganesha_Born == fsm->GetCurStateString() && fsm->GetDM()->GetAniTimeline() > 0.9)
	{
		pOwner->GetComponent<CPatternMachineC>()->SetOnBorn(true);
		fsm->ChangeState(Name_Ganesha_StandBy);

		pOwner->GetComponent<Engine::CRigidBodyC>()->SetIsEnabled(true);
		pOwner->GetComponent<Engine::CCollisionC>()->SetIsEnabled(true);
		m_bornStart = false;
		m_impactEffect = false;

		// movie
		CStageControlTower::GetInstance()->GetMovieDirector()->Cut();
		return;
	}

	/************************* Effect */
	// born 패턴을 시작하자마자 이펙트 생성
	if (false == m_bornStart)
	{
		m_spDomeEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Cinema_Dome", true);
		m_spCircleEffect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Ganesha_Cinema_Circle", true);

		m_spDomeEffect->GetTransform()->SetPosition(mPos);
		m_spCircleEffect->GetTransform()->SetPosition(mPos);
		m_bornStart = true;
	}
	
	// 내가 땅에서 튀어 나오면
	if (Name_Ganesha_Born == fsm->GetCurStateString() &&
		0.27f <= fsm->GetDM()->GetAniTimeline())
	{
		// dome, circle 이펙트 제거
		m_spDomeEffect->SetDeleteThis(true);
		m_spCircleEffect->SetDeleteThis(true);
	}

	// 내가 땅에 착지했을 때 이펙트 생성
	if (Name_Ganesha_Born == fsm->GetCurStateString() &&
		0.4f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_impactEffect)
	{
		SP(Engine::CObject) effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Impact", true);
		effect->GetTransform()->SetSize(_float3(3.f, 3.f, 3.f));
		effect->GetTransform()->SetPosition(mPos);
		effect->GetTransform()->AddPositionY(1.f);

		effect = Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_Impact_TripleRing", true);
		effect->GetTransform()->SetSize(_float3(9.f, 9.f, 9.f));
		effect->GetTransform()->SetPosition(mPos);
		m_impactEffect = true;
	}

}

SP(CGaneshaBornPattern) CGaneshaBornPattern::Create()
{
	SP(CGaneshaBornPattern) spInstance(new CGaneshaBornPattern, Engine::SmartDeleter<CGaneshaBornPattern>);

	return spInstance;
}