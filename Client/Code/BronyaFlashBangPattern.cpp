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
	_float3 tPos = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform()->GetPosition(); // target pos
	_float3 mPos = pOwner->GetTransform()->GetPosition(); // monster pos
	_float len = D3DXVec3Length(&(tPos - mPos));
	SP(CFSM_BronyaC) fsm = pOwner->GetComponent<CFSM_BronyaC>();

	// ���� flash bang ���°� �ƴ϶�� ��� ����
	if (Name_Throw_3 != fsm->GetCurStateString())
	{
		static_cast<CMB_Bronya*>(pOwner)->ChaseTarget(tPos);
	}

	// 1. ��� ����
	// 2. �÷��ù�
	// 3. ���� �̽�������

	/************************* Fast Idle */
	if (Name_IDLE == fsm->GetCurStateString())
	{
		if (fsm->GetDM()->IsAnimationEnd())
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.f);
		}
		else
		{
			fsm->GetDM()->GetAniCtrl()->SetSpeed(1.7f);
		}
	}

	// ���� ��� ���°� �����ٸ�
	if (Name_IDLE == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		false == m_onThrow)
	{
		// flash bang ���·� ����
		fsm->ChangeState(Name_Throw_3);
		m_onThrow = true;

		return;
	}
	// ���� flash bang ���°� �����ٸ�
	else if (Name_Throw_3 == fsm->GetCurStateString() &&
		fsm->GetDM()->IsAnimationEnd() &&
		true == m_onThrow)
	{
		// ��� ���·� ����
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
			m_onFlashFade = false;

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

		_float3 handPos = { realMat._41, realMat._42, realMat._43 };

		SP(CBronya_FlashBang) flash = std::dynamic_pointer_cast<CBronya_FlashBang>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"Bronya_FlashBang", true));
		flash->GetTransform()->SetPosition(handPos);

		m_onFlashEffect = true;
		PatternPlaySound(L"Bronya_FlashBang.wav", pOwner);
	}
	// fade in
	else if (Name_Throw_3 == fsm->GetCurStateString() &&
		0.67f <= fsm->GetDM()->GetAniTimeline() &&
		false == m_onFlashFade)
	{
		_float3 camPos = Engine::GET_MAIN_CAM->GetTransform()->GetPosition();
		_float3 camDir = camPos - tPos;
		D3DXVec3Normalize(&camDir, &camDir);

		m_spFlashBang = std::dynamic_pointer_cast<Engine::CImageObject>(Engine::GET_CUR_SCENE->GetObjectFactory()->AddClone(L"ImageObject", true));
		m_spFlashBang->GetTexture()->AddTexture(L"White");
		m_spFlashBang->GetTexture()->SetAlpha(0.f);
		m_spFlashBang->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
		m_spFlashBang->GetRectTex()->SetIsOrtho(true);
		m_spFlashBang->GetTransform()->SetSize(4000, 1000, 1);
		m_spFlashBang->AddComponent<Engine::CFadeInOutC>()->SetSpeed(6.f);
		m_spFlashBang->GetComponent<Engine::CFadeInOutC>()->SetAutoDelete(false);
		m_spFlashBang->GetComponent<Engine::CFadeInOutC>()->SetIsFadeIn(true);

		///////////////
		//m_spFlashBang->GetComponent<Engine::CFadeInOutC>()->SetIsFadeIn(false);
		//m_spFlashBang->GetComponent<Engine::CFadeInOutC>()->SetFinish(false);

		m_onFlashFade = true;
	}
	else if (m_onFlashFade == true)
	{
		SP(Engine::CFadeInOutC) spFadeInOut = m_spFlashBang->GetComponent<Engine::CFadeInOutC>();
		_float curSpeed = spFadeInOut->GetSpeed();
		if(curSpeed > 0.5f)
			spFadeInOut->SetSpeed(curSpeed - 15 * GET_DT);

		if (spFadeInOut->GetFinish() == true)
		{
			m_onFlashFade = false;
			spFadeInOut->SetIsFadeIn(false);
			spFadeInOut->SetFinish(false);
		}
		
	}
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