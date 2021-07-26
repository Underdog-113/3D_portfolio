#include "stdafx.h"
#include "BronyaFlashBangPattern.h"

#include "FSM_BronyaC.h"
#include "FSMDefine_Bronya.h"
#include "MB_Bronya.h"

#include "Valkyrie.h"
#include "AniCtrl.h"

#include "Bronya_FlashBang.h"
#include "MovieDirector.h"
//#include "ImageObject.h"

CBronyaFlashBangPattern::CBronyaFlashBangPattern()
{
}

CBronyaFlashBangPattern::~CBronyaFlashBangPattern()
{
}

void CBronyaFlashBangPattern::Pattern(Engine::CObject* pOwner)
{
	m_tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(m_tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	// 내가 flash bang 상태가 아니라면 상대 추적
	if (Name_Throw_3 != fsm->GetCurStateString())
	{
		static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(m_tPos);
	}

	// 1. 대기 상태
	// 2. 플래시뱅
	// 3. 랜덤 이스케이프

	/************************* Fast Idle */
	if (Name_IDLE == fsm->GetCurStateString())
	{
		if (fsm->GetDM()->IsAnimationEnd())
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		}
		else
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(2.f);
		}
	}

	// 내가 대기 상태가 끝났다면
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onThrow)
	{
		// flash bang 상태로 변경
		fsm->ChangeState(Name_Throw_3);
		m_onThrow = true;

		static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(true);

		return;
	}
	// 내가 flash bang 상태가 끝났다면
	else if (Name_Throw_3 == fsm->GetCurStateString() &&
		0.9f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onThrow)
	{
		// 대기 상태로 변경
		fsm->ChangeState(Name_IDLE);
	}
	else if (true == m_onThrow)
	{
		m_spEscapeP->Pattern(pOwner);

		if (false == pOwner->GetComponent<CPatternMachineC>()->GetOnSelect())
		{
			std::cout << "Escape!" << std::endl;
			std::cout << "========================" << std::endl;
			m_onThrow = false;
			m_onFlashEffect = false;
			m_onCC = false;
			m_onFlashFadeIn = false;

			static_cast<CMonster*>(pOwner)->GetStat()->SetOnPatternShield(false);

			return;
		}
	}

	/************************* effect */
	if (Name_Throw_3 == fsm->GetCurStateString() &&
		0.55f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onFlashEffect)
	{
		_mat realMat;
		D3DXMatrixIdentity(&realMat);

		m_pRHand = &fsm->GetDM()->GetFrameByName("Bip002_R_Hand")->CombinedTransformMatrix;
		GetRHandMat(pOwner, &realMat);

		m_handPos = { realMat._41, realMat._42, realMat._43 };

		SP(CBronya_FlashBang) flash = std::dynamic_pointer_cast<CBronya_FlashBang>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_FlashBang", true));
		flash->GetTransform()->SetPosition(m_handPos);

		m_onFlashEffect = true;
	}
	// fade in
	else if (Name_Throw_3 == fsm->GetCurStateString() &&
		0.7f <= fsm->GetDM()->GetAniTimeline() &&
		true == m_onThrow &&
		false == m_onFlashFadeIn)
	{
		CStageControlTower::GetInstance()->GetMovieDirector()->StartTake_WhiteFadeOneTake(0.8f, 1.2f, 1.2f, 1.5f);

		//m_spFlashBang = std::dynamic_pointer_cast<Engine::CImageObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ImageObject", true));
		//m_spFlashBang->GetTexture()->AddTexture(L"White");
		//m_spFlashBang->GetTexture()->SetAlpha(0.f);
		//m_spFlashBang->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
		//m_spFlashBang->GetRectTex()->SetIsOrtho(true);
		//m_spFlashBang->GetTransform()->SetSize(4000, 1000, 1);
		//m_spFlashBang->AddComponent<Engine::CFadeInOutC>()->SetSpeed(2.f);
		//m_spFlashBang->GetComponent<Engine::CFadeInOutC>()->SetAutoDelete(false);
		//m_spFlashBang->GetComponent<Engine::CFadeInOutC>()->SetIsFadeIn(true);

		m_onFlashFadeIn = true;
	}
	
	//if (true == m_onFlashFadeIn)
	//{
	//	SP(Engine::CFadeInOutC) spFadeInOut = m_spFlashBang->GetComponent<Engine::CFadeInOutC>();
	//	_float curSpeed = spFadeInOut->GetSpeed();

	//	if (curSpeed > 1.7f)
	//		spFadeInOut->SetSpeed(curSpeed + 2 * GET_DT);

	//	if (spFadeInOut->GetFinish() == true)
	//	{
	//		m_onFlashFadeIn = false;
	//		m_onFlashFadeOut = true;
	//	}
	//	
	//}
	//else if (true == m_onFlashFadeOut)
	//{
	//	SP(Engine::CFadeInOutC) spFadeInOut = m_spFlashBang->GetComponent<Engine::CFadeInOutC>();
	//	_float curSpeed = spFadeInOut->GetSpeed();

	//	if (curSpeed > 1.3f)
	//		spFadeInOut->SetSpeed(curSpeed - 15 * GET_DT);

	//	if (spFadeInOut->GetFinish() == true)
	//	{
	//		m_onFlashFadeOut = false;
	//		spFadeInOut->SetIsFadeIn(false);
	//		spFadeInOut->SetFinish(false);
	//	}

	//	if (curSpeed > 3.f &&
	//		false == m_onCC)
	//	{
	//		// 반사
	//		BlowOutFlash();
	//	}
	//}


}

SP(CBronyaFlashBangPattern) CBronyaFlashBangPattern::Create()
{
	SP(CBronyaFlashBangPattern) spInstance(new CBronyaFlashBangPattern, Engine::SmartDeleter<CBronyaFlashBangPattern>);

	return spInstance;
}

void CBronyaFlashBangPattern::GetRHandMat(Engine::CObject * pOwner, _mat * pAtkBall)
{
	_mat combMat = *m_pRHand;
	_float3 rootMotionPos = pOwner->GetComponent<Engine::CMeshC>()->GetRootMotionPos();
	combMat._41 -= rootMotionPos.x;
	combMat._43 -= rootMotionPos.z;

	*pAtkBall = combMat * pOwner->GetTransform()->GetWorldMatrix();
}

void CBronyaFlashBangPattern::BlowOutFlash()
{
	_float3 tForward = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetForward();
	tForward.y = 0;
	D3DXVec3Normalize(&tForward, &tForward);

	_float3 lightPos = m_handPos;
	lightPos.y = 0;

	_float3 dir = lightPos - m_tPos;
	D3DXVec3Normalize(&dir, &dir);

	_float dot = D3DXVec3Dot(&tForward, &dir);
	GET_MATH->RoundOffRange(dot, 1);

	// stun
	if (abs(acos(dot)) < PI / 2)
	{
		CStageControlTower::GetInstance()->GetCurrentActor()->SetStunState(1.f);

		std::cout << ": " << abs(acos(dot)) * 180 / PI << std::endl;
		std::cout << "Stun!" << std::endl;
	}
	// no stun
	else
	{
		std::cout << ": " << abs(acos(dot)) * 180 / PI << std::endl;
		std::cout << "Miss!" << std::endl;
	}
	m_onCC = true;
}
