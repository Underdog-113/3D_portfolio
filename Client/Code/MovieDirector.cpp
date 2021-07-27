#include "stdafx.h"
#include "..\Header\MovieDirector.h"

#include "WndApp.h"
#include "FadeInOutC.h"
#include "Take.h"
#include "Valkyrie.h"

#include "Shot_WhiteFadeIn.h"
#include "Shot_WhiteFadeOut.h"
#include "Shot_BlackFadeIn.h"
#include "Shot_BlackFadeOut.h"
#include "Shot_RotateAround.h"
#include "Shot_RotateYaw.h"
#include "Shot_RotatePitch.h"
#include "Shot_RotatePitch_Spline.h"
#include "Shot_RotateRoll.h"
#include "Shot_PushIn.h"
#include "Shot_PushOut.h"
#include "Shot_FixPivot.h"
#include "Shot_ActorVictory.h"
#include "Shot_GaneshaBorn.h"
#include "Shot_BronyaBorn.h"
#include "Shot_Shake.h"
#include "Shot_SlowAll.h"
#include "Shot_ReturnCameraToActor.h"

#include "SplineCurve.h"

CMovieDirector::CMovieDirector()
{
}


CMovieDirector::~CMovieDirector()
{
	SAFE_DELETE(m_pShot_WhiteFadeIn)
	SAFE_DELETE(m_pShot_WhiteFadeOut)

	SAFE_DELETE(m_pShot_BlackFadeIn)
	SAFE_DELETE(m_pShot_BlackFadeIn_SubCh1)
	SAFE_DELETE(m_pShot_BlackFadeIn_SubCh2)
	SAFE_DELETE(m_pShot_BlackFadeOut)
	SAFE_DELETE(m_pShot_BlackFadeOut_SubCh1)
	SAFE_DELETE(m_pShot_BlackFadeOut_SubCh2)

	SAFE_DELETE(m_pShot_RotateAround)
	SAFE_DELETE(m_pShot_RotateYaw)
	SAFE_DELETE(m_pShot_RotateYaw_SubCh1)
	SAFE_DELETE(m_pShot_RotateYaw_SubCh2)
	SAFE_DELETE(m_pShot_RotatePitch)
	SAFE_DELETE(m_pShot_RotatePitch_SubCh1)
	SAFE_DELETE(m_pShot_RotatePitch_Spline)
	SAFE_DELETE(m_pShot_RotatePitch_Spline_SubCh1)
	SAFE_DELETE(m_pShot_RotateRoll)

	SAFE_DELETE(m_pShot_PushIn)
	SAFE_DELETE(m_pShot_PushIn_SubCh1)
	SAFE_DELETE(m_pShot_PushOut)
	SAFE_DELETE(m_pShot_PushOut_SubCh1)
	SAFE_DELETE(m_pShot_MovePivot)
	SAFE_DELETE(m_pShot_MovePivot_SubCh1)
	SAFE_DELETE(m_pShot_MovePivot_SubCh2)
	SAFE_DELETE(m_pShot_MovePivot_SubCh3)
	SAFE_DELETE(m_pShot_MovePivot_SubCh4)

	SAFE_DELETE(m_pShot_Shake)
	SAFE_DELETE(m_pShot_SlowAll)
	SAFE_DELETE(m_pShot_ReturnCameraToActor)

	SAFE_DELETE(m_pShot_Victory)
	SAFE_DELETE(m_pShot_GaneshaBorn)
	SAFE_DELETE(m_pShot_BronyaBorn)


	SAFE_DELETE(m_pGaneshaShakeChannel)
		

	SAFE_DELETE(m_pGaneshaPitchCurve_1st)
	SAFE_DELETE(m_pGaneshaPitchCurve_2nd)

	for (auto iter : m_takeMap)
	{
		SAFE_DELETE(iter.second)
	}

	m_takeMap.clear();
}

void CMovieDirector::Start()
{
	Create_FadeImages();

	Create_AllShots();

	Create_AllTakes();


	m_onAir = false;

	m_isStart = true;

}

void CMovieDirector::UpdateDirector()
{
	if (!m_isStart)
		Start();

	if (m_onAir)
		m_pCurTake->ActTake();


	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_1))
		CutCurrentTake();

	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_3))
	{
		StartTake_KianaVictory();
		//StartTake_SakuraVictory();
		//StartTake_GaneshBorn();
		//StartTake_WhiteFadeOut(0.f, 0.5f);
	}


	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_4))
	{
		StartTake_TheresaVictory();
		//StartTake_SakuraVictory();
		//StartTake_GaneshBorn();
		//m_pCurTake->SetEditMode(true);

		//StartTake_WhiteFadeIn(0.f, 1.f);
	}
	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_5))
	{
		//StartTake_KianaVictory();
		StartTake_SakuraVictory();
		//StartTake_GaneshBorn();
		//StartTake_WhiteFadeOut(0.f, 0.5f);
	}
// 	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_1))
// 		CStageControlTower::GetInstance()->SetDirectorMode(true);
// 	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_2))
// 		CStageControlTower::GetInstance()->SetDirectorMode(false);

}


void CMovieDirector::Create_FadeImages()
{
	m_spBlackFadeImage
		= std::dynamic_pointer_cast<Engine::CImageObject>(Engine::GET_CUR_SCENE->ADD_CLONE(L"ImageObject", true));
	m_spBlackFadeImage->GetTexture()->AddTexture(L"FadeBlack");
	m_spBlackFadeImage->GetTransform()->SetPositionZ(0);
	m_spBlackFadeImage->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
	m_spBlackFadeImage->GetRectTex()->SetIsOrtho(true);
	m_spBlackFadeImage->GetTransform()->SetSize((_float)Engine::CWndApp::GetInstance()->GetWndWidth(), (_float)Engine::CWndApp::GetInstance()->GetWndWidth(), 1);
	m_spBlackFadeImage->AddComponent<Engine::CFadeInOutC>();

	m_pBlackFade = m_spBlackFadeImage->GetComponent<Engine::CFadeInOutC>().get();
	m_pBlackFade->SetAutoMode(false);
	m_pBlackFade->SetAlpha(0.f);


	m_spWhiteFadeImage
		= std::dynamic_pointer_cast<Engine::CImageObject>(Engine::GET_CUR_SCENE->ADD_CLONE(L"ImageObject", true));
	m_spWhiteFadeImage->GetTexture()->AddTexture(L"White");
	m_spWhiteFadeImage->GetTransform()->SetPositionZ(0);
	m_spWhiteFadeImage->GetShader()->AddShader((_int)Engine::EShaderID::RectTexShader);
	m_spWhiteFadeImage->GetRectTex()->SetIsOrtho(true);
	m_spWhiteFadeImage->GetTransform()->SetSize((_float)Engine::CWndApp::GetInstance()->GetWndWidth(), (_float)Engine::CWndApp::GetInstance()->GetWndWidth(), 1);
	m_spWhiteFadeImage->AddComponent<Engine::CFadeInOutC>();

	m_pWhiteFade = m_spWhiteFadeImage->GetComponent<Engine::CFadeInOutC>().get();
	m_pWhiteFade->SetAutoMode(false);
	m_pWhiteFade->SetAlpha(0.f);


	m_spBlackFadeImage->SetIsEnabled(false);
	m_spWhiteFadeImage->SetIsEnabled(false);
}

void CMovieDirector::Create_AllShots()
{
	m_pShot_WhiteFadeIn = new CShot_WhiteFadeIn;
	m_pShot_WhiteFadeOut = new CShot_WhiteFadeOut;

	m_pShot_BlackFadeIn = new CShot_BlackFadeIn;
	m_pShot_BlackFadeIn_SubCh1 = new CShot_BlackFadeIn;
	m_pShot_BlackFadeIn_SubCh2 = new CShot_BlackFadeIn;
	m_pShot_BlackFadeOut = new CShot_BlackFadeOut;
	m_pShot_BlackFadeOut_SubCh1 = new CShot_BlackFadeOut;
	m_pShot_BlackFadeOut_SubCh2 = new CShot_BlackFadeOut;

	m_pShot_RotateAround = new CShot_RotateAround;
	m_pShot_RotateYaw = new CShot_RotateYaw;
	m_pShot_RotateYaw_SubCh1 = new CShot_RotateYaw;
	m_pShot_RotateYaw_SubCh2 = new CShot_RotateYaw;
	m_pShot_RotatePitch = new CShot_RotatePitch;
	m_pShot_RotatePitch_SubCh1 = new CShot_RotatePitch;
	m_pShot_RotatePitch_Spline = new CShot_RotatePitch_Spline;
	m_pShot_RotatePitch_Spline_SubCh1 = new CShot_RotatePitch_Spline;
	m_pShot_RotateRoll = new CShot_RotateRoll;

	m_pShot_PushIn = new CShot_PushIn;
	m_pShot_PushIn_SubCh1 = new CShot_PushIn;
	m_pShot_PushOut = new CShot_PushOut;
	m_pShot_PushOut_SubCh1 = new CShot_PushOut;
	m_pShot_MovePivot = new CShot_MovePivot;
	m_pShot_MovePivot_SubCh1 = new CShot_MovePivot;
	m_pShot_MovePivot_SubCh2 = new CShot_MovePivot;
	m_pShot_MovePivot_SubCh3 = new CShot_MovePivot;
	m_pShot_MovePivot_SubCh4 = new CShot_MovePivot;
	
	m_pShot_Shake = new CShot_Shake;
	m_pShot_SlowAll = new CShot_SlowAll;
	m_pShot_ReturnCameraToActor = new CShot_ReturnCameraToActor;

	m_pShot_Victory = new CShot_ActorVictory;
	m_pShot_GaneshaBorn = new CShot_GaneshaBorn;
	m_pShot_BronyaBorn = new CShot_BronyaBorn;
}

void CMovieDirector::Create_AllTakes()
{
	CreateTake_WhiteFadeOneTake();
	CreateTake_WhiteFadeIn();
	CreateTake_WhiteFadeOut();
	CreateTake_BlackFadeIn();
	CreateTake_BlackFadeOut();
	CreateTake_WinningSlow();

	CreateTake_Failure();
	CreateTake_KianaVictory();
	CreateTake_TheresaVictory();
	CreateTake_SakuraVictory();
	CreateTake_GaneshaBorn();
	CreateTake_BronyaBorn();
}

void CMovieDirector::CreateTake_WhiteFadeOneTake()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);
	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);

	m_takeMap.emplace(TakeName_SimpleWhiteFadeOneTake, pTake);
}

void CMovieDirector::CreateTake_WhiteFadeIn()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);

	m_takeMap.emplace(TakeName_SimpleWhiteFadeIn, pTake);
}

void CMovieDirector::CreateTake_WhiteFadeOut()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);

	m_takeMap.emplace(TakeName_SimpleWhiteFadeOut, pTake);
}

void CMovieDirector::CreateTake_BlackFadeIn()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_BlackFadeIn, m_pShot_BlackFadeIn);

	m_takeMap.emplace(TakeName_SimpleBlackFadeIn, pTake);
}

void CMovieDirector::CreateTake_BlackFadeOut()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_BlackFadeOut, m_pShot_BlackFadeOut);

	m_takeMap.emplace(TakeName_SimpleBlackFadeOut, pTake);
}

void CMovieDirector::CreateTake_WinningSlow()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_SlowAll, m_pShot_SlowAll);
	pTake->AddShot(ShotName_RotateAround, m_pShot_RotateAround);

	m_takeMap.emplace(TakeName_WinningSlow, pTake);
}

void CMovieDirector::CreateTake_Failure()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);
	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);
	pTake->AddShot(ShotName_BlackFadeIn, m_pShot_BlackFadeIn);
	pTake->AddShot(ShotName_RotateAround, m_pShot_RotateAround);

	m_takeMap.emplace(TakeName_Failure, pTake);
}

void CMovieDirector::CreateTake_KianaVictory()
{
	CTake* pTake = new CTake;
			
	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);
	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);

	pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);
	pTake->AddShot(ShotName_RotatePitch, m_pShot_RotatePitch);
	pTake->AddShot(ShotName_RotatePitch_SubCh1, m_pShot_RotatePitch_SubCh1);

	pTake->AddShot(ShotName_MovePivot, m_pShot_MovePivot);
	pTake->AddShot(ShotName_MovePivot_SubCh1, m_pShot_MovePivot_SubCh1);
	pTake->AddShot(ShotName_PushOut, m_pShot_PushOut);
	pTake->AddShot(ShotName_PushOut_SubCh1, m_pShot_PushOut_SubCh1);

	pTake->AddShot(ShotName_RotateYaw_SubCh1, m_pShot_RotateYaw_SubCh1);
	pTake->AddShot(ShotName_Victory, m_pShot_Victory);

	m_takeMap.emplace(TakeName_KianaVictory, pTake);
}

void CMovieDirector::CreateTake_TheresaVictory()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);
	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);

	pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);
	pTake->AddShot(ShotName_RotatePitch, m_pShot_RotatePitch);
	pTake->AddShot(ShotName_PushIn, m_pShot_PushIn);
	pTake->AddShot(ShotName_PushOut, m_pShot_PushOut);
	
	pTake->AddShot(ShotName_MovePivot, m_pShot_MovePivot);
	//pTake->AddShot(ShotName_MovePivot_SubCh1, m_pShot_MovePivot_SubCh1);
	pTake->AddShot(ShotName_RotateRoll, m_pShot_RotateRoll);

	pTake->AddShot(ShotName_RotateYaw_SubCh1, m_pShot_RotateYaw_SubCh1);
	pTake->AddShot(ShotName_Victory, m_pShot_Victory);

	m_takeMap.emplace(TakeName_TheresaVictory, pTake);
}

void CMovieDirector::CreateTake_SakuraVictory()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);
	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);

	pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);
	pTake->AddShot(ShotName_RotateYaw_SubCh1, m_pShot_RotateYaw_SubCh1);
	pTake->AddShot(ShotName_RotatePitch, m_pShot_RotatePitch);
	pTake->AddShot(ShotName_RotateRoll, m_pShot_RotateRoll);

	pTake->AddShot(ShotName_PushOut, m_pShot_PushOut);
	pTake->AddShot(ShotName_MovePivot, m_pShot_MovePivot);

	pTake->AddShot(ShotName_Victory, m_pShot_Victory);

	m_takeMap.emplace(TakeName_SakuraVictory, pTake);
}

void CMovieDirector::CreateTake_GaneshaBorn()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_MovePivot, m_pShot_MovePivot);
	pTake->AddShot(ShotName_GaneshaBorn, m_pShot_GaneshaBorn);

	pTake->AddShot(ShotName_BlackFadeIn, m_pShot_BlackFadeIn);
	pTake->AddShot(ShotName_BlackFadeOut, m_pShot_BlackFadeOut);

	// start ~ before jump
	pTake->AddShot(ShotName_PushIn, m_pShot_PushIn);
	pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);
	
	// jump ~ land
	pTake->AddShot(ShotName_RotatePitch_Spline, m_pShot_RotatePitch_Spline);
	m_pGaneshaPitchCurve_1st = new CSplineCurve;
	m_pGaneshaPitchCurve_1st->AddPoint(_float3(0.f, 10.f, 0.f));
	m_pGaneshaPitchCurve_1st->AddPoint(_float3(0.55f, 12.5f, 0.f));
	m_pGaneshaPitchCurve_1st->AddPoint(_float3(0.8f, 15.f, 0.f));
	m_pGaneshaPitchCurve_1st->AddPoint(_float3(0.87f, -30.f, 0.f));
	CSplineCurve::Desc desc;
	m_pGaneshaPitchCurve_1st->CreateCurve(&desc);
	
	pTake->AddShot(ShotName_RotatePitch_Spline_SubCh1, m_pShot_RotatePitch_Spline_SubCh1);
	m_pGaneshaPitchCurve_2nd = new CSplineCurve;
	m_pGaneshaPitchCurve_2nd->AddPoint(_float3(0.f, -30.f, 0.f));
	m_pGaneshaPitchCurve_2nd->AddPoint(_float3(0.2f, 10.f, 0.f));
	m_pGaneshaPitchCurve_2nd->AddPoint(_float3(0.4f, 0.f, 0.f));
	m_pGaneshaPitchCurve_2nd->AddPoint(_float3(0.6f, 7.f, 0.f));
	m_pGaneshaPitchCurve_2nd->AddPoint(_float3(0.8f, 4.5f, 0.f));
	m_pGaneshaPitchCurve_2nd->AddPoint(_float3(1.f, 5.f, 0.f));
	m_pGaneshaPitchCurve_2nd->CreateCurve(&desc);

	pTake->AddShot(ShotName_MovePivot_SubCh1, m_pShot_MovePivot_SubCh1);
	pTake->AddShot(ShotName_MovePivot_SubCh2, m_pShot_MovePivot_SubCh2);
	// land ~ end

	pTake->AddShot(ShotName_PushIn_SubCh1, m_pShot_PushIn_SubCh1);
	pTake->AddShot(ShotName_PushOut_SubCh1, m_pShot_PushOut_SubCh1);
	pTake->AddShot(ShotName_RotateYaw_SubCh1, m_pShot_RotateYaw_SubCh1);

	pTake->AddShot(ShotName_Shake, m_pShot_Shake);	
	CreateGanshaBornShakeChannel();

	pTake->AddShot(ShotName_MovePivot_SubCh3, m_pShot_MovePivot_SubCh3);
	pTake->AddShot(ShotName_BlackFadeIn_SubCh1, m_pShot_BlackFadeIn_SubCh1);
	pTake->AddShot(ShotName_BlackFadeOut_SubCh1, m_pShot_BlackFadeOut_SubCh1);
	pTake->AddShot(ShotName_ReturnCameraToActor, m_pShot_ReturnCameraToActor);

	m_takeMap.emplace(TakeName_GaneshaBorn, pTake);
}

void CMovieDirector::CreateTake_BronyaBorn()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_MovePivot, m_pShot_MovePivot);
	pTake->AddShot(ShotName_BronyaBorn, m_pShot_BronyaBorn);
	pTake->AddShot(ShotName_RotatePitch, m_pShot_RotatePitch);

	// 1st right side view
	pTake->AddShot(ShotName_BlackFadeIn, m_pShot_BlackFadeIn);
	pTake->AddShot(ShotName_MovePivot_SubCh1, m_pShot_MovePivot_SubCh1);
	pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);
	pTake->AddShot(ShotName_PushOut, m_pShot_PushOut);
	pTake->AddShot(ShotName_BlackFadeOut, m_pShot_BlackFadeOut);

	// 2nd left side view
	pTake->AddShot(ShotName_BlackFadeIn_SubCh1, m_pShot_BlackFadeIn_SubCh1);
	pTake->AddShot(ShotName_MovePivot_SubCh2, m_pShot_MovePivot_SubCh2);
	pTake->AddShot(ShotName_PushIn, m_pShot_PushIn);
	pTake->AddShot(ShotName_RotateYaw_SubCh1, m_pShot_RotateYaw_SubCh1);
	pTake->AddShot(ShotName_BlackFadeOut_SubCh1, m_pShot_BlackFadeOut_SubCh1);

	// 3rd front side view
	pTake->AddShot(ShotName_BlackFadeIn_SubCh2, m_pShot_BlackFadeIn_SubCh2);
	pTake->AddShot(ShotName_MovePivot_SubCh3, m_pShot_MovePivot_SubCh3);
	pTake->AddShot(ShotName_RotateYaw_SubCh2, m_pShot_RotateYaw_SubCh2);
	pTake->AddShot(ShotName_PushOut_SubCh1, m_pShot_PushOut_SubCh1);
	pTake->AddShot(ShotName_BlackFadeOut_SubCh2, m_pShot_BlackFadeOut_SubCh2);

	// enddd
	pTake->AddShot(ShotName_MovePivot_SubCh4, m_pShot_MovePivot_SubCh4);
	pTake->AddShot(ShotName_ReturnCameraToActor, m_pShot_ReturnCameraToActor);

	m_takeMap.emplace(TakeName_BronyaBorn, pTake);
}


void CMovieDirector::CreateGanshaBornShakeChannel()
{
	m_pGaneshaShakeChannel = new ShakeChannel;

	m_pGaneshaShakeChannel->m_distanceRate = 1.f;

	m_pGaneshaShakeChannel->m_timer = 0.f;

	m_pGaneshaShakeChannel->m_duration = 2.f;
	m_pGaneshaShakeChannel->m_blendInTime = 0.2f;
	m_pGaneshaShakeChannel->m_blendOutTime = 0.2f;

	CStageControlTower::GetInstance()->GetCameraMan()->GetCameraShake()->ResetAllMember(m_pGaneshaShakeChannel);

	m_pGaneshaShakeChannel->m_xWave.amplitude = 0.02f;
	m_pGaneshaShakeChannel->m_xWave.frequency = 20.f;
	m_pGaneshaShakeChannel->m_xWave.offset = 0.f;

	m_pGaneshaShakeChannel->m_yWave.amplitude = 0.08f;
	m_pGaneshaShakeChannel->m_yWave.frequency = 20.f;
	m_pGaneshaShakeChannel->m_yWave.offset = 0.f;

}

void CMovieDirector::StartTake_WhiteFadeOneTake(_float startOut, _float endOut, _float startIn, _float endIn)
{
	auto pTake = m_takeMap[TakeName_SimpleWhiteFadeOneTake];
	m_spWhiteFadeImage->SetIsEnabled(true);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, startOut, endOut, &wfo_desc, startOut);

	CShot_WhiteFadeIn::Desc wfi_desc;
	wfi_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeIn, startIn, endIn, &wfi_desc, startIn);

	m_pCurTake = pTake;

	m_pCurTake->StartTake(false);
	m_onAir = true;
}

void CMovieDirector::StartTake_WhiteFadeIn(_float startTime, _float endTime)
{
	auto pTake = m_takeMap[TakeName_SimpleWhiteFadeIn];
	m_spWhiteFadeImage->SetIsEnabled(true);


	CShot_WhiteFadeIn::Desc wfi_desc;
	wfi_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeIn, startTime, endTime, &wfi_desc, startTime);
	
	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_WhiteFadeOut(_float startTime, _float endTime)
{
	auto pTake = m_takeMap[TakeName_SimpleWhiteFadeOut];
	m_spWhiteFadeImage->SetIsEnabled(true);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, startTime, endTime, &wfo_desc, startTime);
	
	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_BlackFadeIn()
{
	auto pTake = m_takeMap[TakeName_SimpleBlackFadeIn];
	m_spBlackFadeImage->SetIsEnabled(true);

	CShot_BlackFadeIn::Desc bli_desc;
	bli_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn, 0.f, 0.5f, &bli_desc, 0.f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_BlackFadeOut()
{
	auto pTake = m_takeMap[TakeName_SimpleBlackFadeOut];
	m_spBlackFadeImage->SetIsEnabled(true);

	CShot_BlackFadeOut::Desc blo_desc;
	blo_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeOut, 0.f, 0.5f, &blo_desc, 0.f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_WinningSlow()
{
	auto pTake = m_takeMap[TakeName_WinningSlow];

	CShot_SlowAll::Desc slow_desc;
	pTake->ReadyShot(ShotName_SlowAll, 0.f, 3.f, &slow_desc, 0.f);

	CShot_RotateAround::Desc ra_desc;
	ra_desc.startRadianRotate = CStageControlTower::GetInstance()->GetCameraMan()->GetCamera()->GetLookAngleUp();
	ra_desc.rotateSpeed = 0.05f;
	ra_desc.isEndless = false;
	pTake->ReadyShot(ShotName_RotateAround, 0.f, 5.f, &ra_desc, 0.f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_Failure()
{
	auto pTake = m_takeMap[TakeName_Failure];
	m_spBlackFadeImage->SetIsEnabled(true);
	m_spWhiteFadeImage->SetIsEnabled(true);

	CShot_WhiteFadeIn::Desc wfi_desc;
	wfi_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeIn, 0.6f, 1.1f, &wfi_desc, 0.6f);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, 0.f, 0.5f, &wfo_desc, 0.f);

	CShot_BlackFadeIn::Desc bfi_desc;
	bfi_desc.pBlackFade = m_pBlackFade;
	bfi_desc.alphaLimit = 0.5f;
	pTake->ReadyShot(ShotName_BlackFadeIn, 0.5f, 0.6f, &bfi_desc, 0.5f);

	CShot_RotateAround::Desc ra_desc;
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	ra_desc.offset = pActor->GetTransform()->GetRight() * 0.5f;
	ra_desc.rotateSpeed = 12.f;
	pTake->ReadyShot(ShotName_RotateAround, 0.5f, 100.f, &ra_desc, 0.5f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_Victory()
{
	switch (CStageControlTower::GetInstance()->GetCurrentActor()->GetStat()->GetType())
	{
	case V_Stat::KIANA:
		StartTake_KianaVictory();
		break;
	case V_Stat::THERESA:
		StartTake_TheresaVictory();
		break;
	case V_Stat::SAKURA:
		StartTake_SakuraVictory();
		break;
	default:
		break;
	}

}

void CMovieDirector::StartTake_KianaVictory()
{
	auto pTake = m_takeMap[TakeName_KianaVictory];
	m_spBlackFadeImage->SetIsEnabled(false);
	m_spWhiteFadeImage->SetIsEnabled(true);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, 0.f, 0.5f, &wfo_desc, 0.f);

	CShot_WhiteFadeIn::Desc wfi_desc;
	wfi_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeIn, 0.6f, 1.1f, &wfi_desc, 0.6f);

	// right hand up
	CShot_RotateYaw::Desc ry_desc;
	ry_desc.startEulerAngle = 100.f;
	ry_desc.endEulerAngle = 8.f;
	pTake->ReadyShot(ShotName_RotateYaw, 0.6f, 2.1f, &ry_desc, 0.6f);

	CShot_RotatePitch::Desc rp_desc;
	rp_desc.startEulerAngle = 10.f;
	rp_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotatePitch, 1.45f, 1.65f, &rp_desc, 0.6f);

	CShot_MovePivot::Desc mp_desc;
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	mp_desc.startOffset = pActor->GetTransform()->GetUp() * -0.15f + pActor->GetTransform()->GetRight() * 0.1f;;
	mp_desc.endOffset = pActor->GetTransform()->GetUp() * 0.08f + pActor->GetTransform()->GetRight() * 0.05f;
	pTake->ReadyShot(ShotName_MovePivot, 1.45f, 1.65f, &mp_desc, 0.6f);

	CShot_PushOut::Desc po_desc;
	po_desc.startDistance = 0.2f;
	po_desc.endDistance = 0.5f;
	pTake->ReadyShot(ShotName_PushOut, 1.45f, 1.65f, &po_desc, 0.6f);

	// right hand left
	CShot_RotatePitch::Desc rp_sub1_desc;
	rp_sub1_desc.startEulerAngle = 0.f;
	rp_sub1_desc.endEulerAngle = -10.f;
	pTake->ReadyShot(ShotName_RotatePitch_SubCh1, 2.1f, 2.3f, &rp_sub1_desc, 2.1f);

	CShot_MovePivot::Desc mp_sub1_desc;
	mp_sub1_desc.startOffset = mp_desc.endOffset;
	mp_sub1_desc.endOffset = pActor->GetTransform()->GetUp() * 0.07f + pActor->GetTransform()->GetRight() * -0.115f;
	pTake->ReadyShot(ShotName_MovePivot_SubCh1, 2.1f, 2.3f, &mp_sub1_desc, 2.1f);
	
	CShot_PushOut::Desc po_sub1_desc;
	po_sub1_desc.startDistance = po_desc.endDistance;
	po_sub1_desc.endDistance = 0.6f;
	pTake->ReadyShot(ShotName_PushOut_SubCh1, 2.1f, 2.3f, &po_sub1_desc, 2.1f);

	CShot_RotateYaw::Desc ry2_desc;
	ry2_desc.startEulerAngle = ry_desc.endEulerAngle;
	ry2_desc.endEulerAngle = 10.f;
	pTake->ReadyShot(ShotName_RotateYaw_SubCh1, 2.3f, 10.6f, &ry2_desc, 2.3f);


	CShot_ActorVictory::Desc av_desc;
	pTake->ReadyShot(ShotName_Victory, 0.6f, 10.f, &av_desc, 0.6f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_TheresaVictory()
{
	auto pTake = m_takeMap[TakeName_TheresaVictory];
	m_spBlackFadeImage->SetIsEnabled(false);
	m_spWhiteFadeImage->SetIsEnabled(true);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, 0.f, 0.5f, &wfo_desc, 0.f);

	CShot_WhiteFadeIn::Desc wfi_desc;
	wfi_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeIn, 0.6f, 1.1f, &wfi_desc, 0.6f);

	CShot_RotateYaw::Desc ry_desc;
	ry_desc.startEulerAngle = 150.f;
	ry_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateYaw, 0.6f, 3.f, &ry_desc, 0.6f);

	CShot_RotatePitch::Desc rp_desc;
	rp_desc.startEulerAngle = -5.f;
	rp_desc.endEulerAngle = 5.f;
	pTake->ReadyShot(ShotName_RotatePitch, 0.6f, 3.f, &rp_desc, 0.6f);

	CShot_PushIn::Desc pi_desc;
	pi_desc.startDistance = 1.6f;
	pi_desc.endDistance = 0.6f;
	pTake->ReadyShot(ShotName_PushIn, 0.6f, 3.f, &pi_desc, 0.6f);

	CShot_PushOut::Desc po_desc;
	po_desc.startDistance = pi_desc.endDistance;
	po_desc.endDistance = 0.6f;
	pTake->ReadyShot(ShotName_PushOut, 3.f, 3.f, &po_desc, 3.f);

	CShot_MovePivot::Desc mp_desc;
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	mp_desc.startOffset = pActor->GetTransform()->GetUp() * -0.3f + pActor->GetTransform()->GetForward() * -0.15f;/*pActor->GetTransform()->GetUp() * -0.3f + pActor->GetTransform()->GetForward() * 0.1f;*/
	//mp_desc.endOffset = pActor->GetTransform()->GetUp() * -0.3f + pActor->GetTransform()->GetForward() * -0.15f;
	mp_desc.endOffset = pActor->GetTransform()->GetUp() * -0.01f + pActor->GetTransform()->GetRight() * -0.115f;
	pTake->ReadyShot(ShotName_MovePivot, 1.f, 3.f, &mp_desc, 0.6f);

	CShot_RotateRoll::Desc rr_desc;
	rr_desc.startEulerAngle = -10.f;
	rr_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateRoll, 1.f, 3.f, &rr_desc, 0.6f);
	
// 	CShot_MovePivot::Desc mp_sub1_desc;
// 	mp_sub1_desc.startOffset = mp_desc.endOffset;
// 	mp_sub1_desc.endOffset = pActor->GetTransform()->GetUp() * -0.05f + pActor->GetTransform()->GetRight() * -0.115f;
// 	pTake->ReadyShot(ShotName_MovePivot_SubCh1, 1.6f, 3.f, &mp_sub1_desc, 1.6f);

	CShot_RotateYaw::Desc ry2_desc;
	ry2_desc.startEulerAngle = ry_desc.endEulerAngle;
	ry2_desc.endEulerAngle = -5.f;
	pTake->ReadyShot(ShotName_RotateYaw_SubCh1, 3.f, 10.6f, &ry2_desc, 3.f);


	CShot_ActorVictory::Desc av_desc;
	pTake->ReadyShot(ShotName_Victory, 0.6f, 10.f, &av_desc, 0.6f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_SakuraVictory()
{
	auto pTake = m_takeMap[TakeName_SakuraVictory];
	m_spBlackFadeImage->SetIsEnabled(false);
	m_spWhiteFadeImage->SetIsEnabled(true);

	CShot_WhiteFadeIn::Desc wfi_desc;
	wfi_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeIn, 0.6f, 1.1f, &wfi_desc, 0.6f);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, 0.f, 0.5f, &wfo_desc, 0.f);

	CShot_RotateYaw::Desc ry_desc;
	ry_desc.startEulerAngle = -90.f;
	ry_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateYaw, 0.6f, 3.6f, &ry_desc, 0.6f);

	CShot_RotateYaw::Desc ry2_desc;
	ry2_desc.startEulerAngle = 0.f;
	ry2_desc.endEulerAngle = 5.f;
	pTake->ReadyShot(ShotName_RotateYaw_SubCh1, 3.6f, 10.6f, &ry2_desc, 3.6f);

	CShot_RotatePitch::Desc rp_desc;
	rp_desc.startEulerAngle = 0.f;
	rp_desc.endEulerAngle = -5.f;
	pTake->ReadyShot(ShotName_RotatePitch, 2.6f, 3.6f, &rp_desc, 0.6f);

	CShot_RotateRoll::Desc rr_desc;
	rr_desc.startEulerAngle = -5.f;
	rr_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateRoll, 2.6f, 3.6f, &rr_desc, 0.6f);

 	CShot_PushOut::Desc po_desc;
 	po_desc.startDistance = 0.3f;
 	po_desc.endDistance = 0.6f;
 	pTake->ReadyShot(ShotName_PushOut, 0.6f, 2.1f, &po_desc, 0.6f);
	
	CShot_MovePivot::Desc mp_desc;
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	mp_desc.startOffset = pActor->GetTransform()->GetUp() * 0.15f + pActor->GetTransform()->GetRight() * 0.1f;
	mp_desc.endOffset = pActor->GetTransform()->GetUp() * 0.11f + pActor->GetTransform()->GetRight() * -0.15f;
	pTake->ReadyShot(ShotName_MovePivot, 0.6f, 3.6f, &mp_desc, 0.6f);


	CShot_ActorVictory::Desc av_desc;
	pTake->ReadyShot(ShotName_Victory, 0.6f, 10.f, &av_desc, 0.6f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::StartTake_GaneshBorn()
{
	auto pTake = m_takeMap[TakeName_GaneshaBorn];
	m_spBlackFadeImage->SetIsEnabled(true);


	CShot_MovePivot::Desc mp_desc;
	mp_desc.pTargetTransform = Engine::GET_CUR_SCENE->FindObjectWithKey(L"MB_Ganesha")->GetTransform().get();
// 	fp_desc.startOffset = pActor->GetTransform()->GetUp() * 0.15f + pActor->GetTransform()->GetRight() * 0.1f;
// 	fp_desc.endOffset = pActor->GetTransform()->GetUp() * 0.11f + pActor->GetTransform()->GetRight() * -0.15f;
	pTake->ReadyShot(ShotName_MovePivot, 0.5f, 1.f, &mp_desc, 0.5f);
	
	CShot_GaneshaBorn::Desc gb_desc;
	pTake->ReadyShot(ShotName_GaneshaBorn, 0.43f, 10.1f, &gb_desc, 0.43f);
	
	// start ~ before jump
	CShot_BlackFadeOut::Desc blo_desc;
	blo_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeOut, 0.f, 0.43f, &blo_desc, 0.f);

	CShot_BlackFadeIn::Desc bfi_desc;
	bfi_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn, 0.6f, 1.1f, &bfi_desc, 0.5f);
	
	CShot_RotateYaw::Desc ry_desc;
	ry_desc.pTargetTransform = mp_desc.pTargetTransform;
	ry_desc.startEulerAngle = 45.f;
	ry_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateYaw, 0.6f, 3.f, &ry_desc, 0.6f);

	CShot_PushIn::Desc pi_desc;
	pi_desc.startDistance = 6.f;
	pi_desc.endDistance = 4.f;
	pTake->ReadyShot(ShotName_PushIn, 0.6f, 3.f, &pi_desc, 0.6f);

	// jump ~ land
	CShot_RotatePitch_Spline::Desc rps_desc;
	rps_desc.angleCurve = m_pGaneshaPitchCurve_1st;
	pTake->ReadyShot(ShotName_RotatePitch_Spline, 2.6f, 2.6f + 0.87f, &rps_desc, 0.5f);

	CShot_MovePivot::Desc mp_sub1_desc;
	mp_sub1_desc.pTargetTransform = mp_desc.pTargetTransform;
	mp_sub1_desc.startOffset = ZERO_VECTOR;
	mp_sub1_desc.endOffset = UP_VECTOR;
	pTake->ReadyShot(ShotName_MovePivot_SubCh1, 3.2f, 3.24f, &mp_sub1_desc, 3.2f);

	CShot_RotatePitch_Spline::Desc rps_sub1_desc;
	rps_sub1_desc.angleCurve = m_pGaneshaPitchCurve_2nd;
	pTake->ReadyShot(ShotName_RotatePitch_Spline_SubCh1, 4.7f, 4.7f + 1.f, &rps_sub1_desc, 4.7f);

	CShot_MovePivot::Desc mp_sub2_desc;
	mp_sub2_desc.pTargetTransform = mp_desc.pTargetTransform;
	mp_sub2_desc.startOffset = UP_VECTOR;
	mp_sub2_desc.endOffset = ZERO_VECTOR * 1.5f;
	pTake->ReadyShot(ShotName_MovePivot_SubCh2, 4.7f, 4.7f + 0.2f, &mp_sub2_desc, 4.7f);
	
	// land ~ end

	CShot_PushIn::Desc pi_sub1_desc;
	pi_sub1_desc.startDistance = 4.f;
	pi_sub1_desc.endDistance = 3.f;
	pi_sub1_desc.isPowLerp = true;
	pTake->ReadyShot(ShotName_PushIn_SubCh1, 6.f, 6.9f, &pi_sub1_desc, 6.f);

	CShot_PushOut::Desc po_sub1_desc;
	po_sub1_desc.startDistance = 3.f;
	po_sub1_desc.endDistance = 4.5f;
	pTake->ReadyShot(ShotName_PushOut_SubCh1, 7.25f, 7.35f, &po_sub1_desc, 7.25f);

	CShot_RotateYaw::Desc ry_sub1_desc;
	ry_sub1_desc.startEulerAngle = 180.f;
	ry_sub1_desc.endEulerAngle = 170.f;
	pTake->ReadyShot(ShotName_RotateYaw_SubCh1, 7.25f, 12.f, &ry_sub1_desc, 7.25f);

	CShot_Shake::Desc shake_desc;
	shake_desc.shakeChannel = m_pGaneshaShakeChannel;
	pTake->ReadyShot(ShotName_Shake, 7.25f, 8.9f, &shake_desc, 7.25f);

	CShot_BlackFadeOut::Desc blo_sub1_desc;
	blo_sub1_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeOut_SubCh1, 9.35f, 9.75f, &blo_sub1_desc, 9.35f);

	CShot_BlackFadeIn::Desc bfi_sub1_desc;
	bfi_sub1_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn_SubCh1, 9.75f, 10.0f, &bfi_sub1_desc, 9.75f);

	CShot_MovePivot::Desc mp_sub3_desc;
	mp_sub3_desc.pTargetTransform = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform().get();
	pTake->ReadyShot(ShotName_MovePivot_SubCh3, 9.75f, 9.75f, &mp_sub3_desc, 9.75f);

	CShot_ReturnCameraToActor::Desc rca_desc;
	pTake->ReadyShot(ShotName_ReturnCameraToActor, 9.75f, 9.75f, &rca_desc, 9.75f);
	
	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;

	// tesssst
	// m_pCurTake->SetEditMode(true);
}

void CMovieDirector::StartTake_BronyaBorn()
{
	auto pTake = m_takeMap[TakeName_BronyaBorn];
	m_spBlackFadeImage->SetIsEnabled(true);

	auto pBronyaTransform = Engine::GET_CUR_SCENE->FindObjectWithKey(L"MB_Bronya")->GetTransform().get();

	CShot_MovePivot::Desc mp_desc;
	mp_desc.pTargetTransform = pBronyaTransform;
	pTake->ReadyShot(ShotName_MovePivot, 0.0f, 0.1f, &mp_desc, 0.0f);

	CShot_BronyaBorn::Desc bronya_desc;
	pTake->ReadyShot(ShotName_BronyaBorn, 0.0f, 12.1f, &bronya_desc, 0.f);

	CShot_RotatePitch::Desc rp_desc;
	rp_desc.startEulerAngle = 5.f;
	rp_desc.endEulerAngle = 5.f;
	pTake->ReadyShot(ShotName_RotatePitch, 0.0f, 0.1f, &rp_desc, 0.0f);

	// 1st right side view
	CShot_BlackFadeIn::Desc bfi_desc;
	bfi_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn, 0.05f, 0.35f, &bfi_desc, 0.05f);

	CShot_MovePivot::Desc mp_sub1_desc;
	mp_sub1_desc.pTargetTransform = pBronyaTransform;
	mp_sub1_desc.startOffset = pBronyaTransform->GetUp() * 0.17f;
	mp_sub1_desc.endOffset = pBronyaTransform->GetUp() * 0.14f;
	pTake->ReadyShot(ShotName_MovePivot_SubCh1, 0.0f, 4.0f, &mp_sub1_desc, 0.0f);

	CShot_RotateYaw::Desc ry_desc;
	ry_desc.pTargetTransform = pBronyaTransform;
	ry_desc.startEulerAngle = 120.f;
	ry_desc.endEulerAngle = 140.f;
	pTake->ReadyShot(ShotName_RotateYaw, 0.0f, 4.0f, &ry_desc, 0.0f);

	CShot_PushOut::Desc po_desc;
	po_desc.startDistance = 0.2f;
	po_desc.endDistance = 0.3f;
	pTake->ReadyShot(ShotName_PushOut, 0.0f, 4.0f, &po_desc, 0.0f);
	
	CShot_BlackFadeOut::Desc blo_desc;
	blo_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeOut, 3.7f, 4.0f, &blo_desc, 3.7f);

	// 2nd left side view
	CShot_BlackFadeIn::Desc bfi_sub1_desc;
	bfi_sub1_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn_SubCh1, 4.0f, 4.3f, &bfi_sub1_desc, 4.0f);

	CShot_MovePivot::Desc mp_sub2_desc;
	mp_sub2_desc.pTargetTransform = pBronyaTransform;
	mp_sub2_desc.startOffset = pBronyaTransform->GetUp() * 0.4f - pBronyaTransform->GetForward() * 0.3f;
	mp_sub2_desc.endOffset = pBronyaTransform->GetUp() * 0.2f + pBronyaTransform->GetForward() * 0.1f;
	pTake->ReadyShot(ShotName_MovePivot_SubCh2, 4.0f, 8.f, &mp_sub2_desc, 4.0f);

	CShot_PushIn::Desc pi_desc;
	pi_desc.startDistance = 0.7f;
	pi_desc.endDistance = 0.7f;
	pTake->ReadyShot(ShotName_PushIn, 4.0f, 4.0f, &pi_desc, 4.0f);

	CShot_RotateYaw::Desc ry_sub1_desc;
	ry_sub1_desc.pTargetTransform = mp_desc.pTargetTransform;
	ry_sub1_desc.startEulerAngle = -90.f;
	ry_sub1_desc.endEulerAngle = -65.f;
	pTake->ReadyShot(ShotName_RotateYaw_SubCh1, 4.0f, 8.f, &ry_sub1_desc, 4.0f);

	CShot_BlackFadeOut::Desc blo_sub1_desc;
	blo_sub1_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeOut_SubCh1, 7.7f, 8.0f, &blo_sub1_desc, 7.7f);

	// 3rd front side view
	CShot_BlackFadeIn::Desc bfi_sub2_desc;
	bfi_sub2_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn_SubCh2, 8.0f, 8.3f, &bfi_sub2_desc, 8.0f);

	CShot_MovePivot::Desc mp_sub3_desc;
	mp_sub3_desc.pTargetTransform = mp_desc.pTargetTransform;
	mp_sub3_desc.startOffset = UP_VECTOR * 0.23f;
	mp_sub3_desc.endOffset = UP_VECTOR * 0.23f;
	pTake->ReadyShot(ShotName_MovePivot_SubCh3, 8.0f, 12.f, &mp_sub3_desc, 8.0f);

	CShot_RotateYaw::Desc ry_sub2_desc;
	ry_sub2_desc.pTargetTransform = mp_desc.pTargetTransform;
	ry_sub2_desc.startEulerAngle = 0.f;
	ry_sub2_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateYaw_SubCh2, 8.0f, 8.0f, &ry_sub2_desc, 8.0f);

	CShot_PushOut::Desc po_sub1_desc;
	po_sub1_desc.startDistance = 0.3f;
	po_sub1_desc.endDistance = 0.5f;
	pTake->ReadyShot(ShotName_PushOut_SubCh1, 8.0f, 12.f, &po_sub1_desc, 8.0f);

	CShot_BlackFadeOut::Desc blo_sub2_desc;
	blo_sub2_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeOut_SubCh2, 11.5f, 12.f, &blo_sub2_desc, 11.5f);

	// enddd
	CShot_MovePivot::Desc mp_sub4_desc;
	mp_sub4_desc.pTargetTransform = CStageControlTower::GetInstance()->GetCurrentActor()->GetTransform().get();
	pTake->ReadyShot(ShotName_MovePivot_SubCh4, 12.f, 12.f, &mp_sub4_desc, 12.f);

	CShot_ReturnCameraToActor::Desc rca_desc;
	pTake->ReadyShot(ShotName_ReturnCameraToActor, 12.f, 12.f, &rca_desc, 12.f);

	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;

	//m_pCurTake->SetEditMode(true);
}

void CMovieDirector::CutCurrentTake()
{
	m_pCurTake->EndTake();
	m_pCurTake = nullptr;
	m_onAir = false;
}

_float3 CMovieDirector::GetBezierPoint(_float3 startPoint, _float3 midPoint, _float3 endPoint, float detail)
{
	_float3 result = ZERO_VECTOR;

	_float startRatio = detail * detail;
	_float midRatio = 2.f * detail * (1.f - detail);
	_float endRatio = (1.f - detail) * (1.f - detail);

	result.x = startPoint.x * startRatio + midPoint.x * midRatio + endPoint.x * endRatio;
	result.y = startPoint.y * startRatio + midPoint.y * midRatio + endPoint.y * endRatio;
	result.z = startPoint.z * startRatio + midPoint.z * midRatio + endPoint.z * endRatio;

	return result;
}
