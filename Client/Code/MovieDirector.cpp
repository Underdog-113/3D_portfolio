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

#include "SplineCurve.h"

CMovieDirector::CMovieDirector()
{
}


CMovieDirector::~CMovieDirector()
{
	SAFE_DELETE(m_pShot_WhiteFadeIn)
	SAFE_DELETE(m_pShot_WhiteFadeOut)
	SAFE_DELETE(m_pShot_BlackFadeIn)
	SAFE_DELETE(m_pShot_RotateAround)
	SAFE_DELETE(m_pShot_RotateYaw)
	SAFE_DELETE(m_pShot_RotateYaw_SubCh1)
	SAFE_DELETE(m_pShot_RotatePitch)
	SAFE_DELETE(m_pShot_RotatePitch_Spline)
	SAFE_DELETE(m_pShot_RotateRoll)
	SAFE_DELETE(m_pShot_PushIn)
	SAFE_DELETE(m_pShot_PushOut)
	SAFE_DELETE(m_pShot_FixPivot)
	SAFE_DELETE(m_pShot_Victory)

	SAFE_DELETE(m_pGaneshaPitchCurve)

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

	CreateTake_Failure();
	CreateTake_SakuraVictory();
	CreateTake_GaneshaBorn();

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
		Cut();

	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_2))
	{
		//StartTake_SakuraVictory();
		StartTake_GaneshBorn();
	}


	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_3))
	{
		//StartTake_SakuraVictory();
		StartTake_GaneshBorn();
		m_pCurTake->SetEditMode(true);
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
	m_pShot_BlackFadeOut = new CShot_BlackFadeOut;

	m_pShot_RotateAround = new CShot_RotateAround;
	m_pShot_RotateYaw = new CShot_RotateYaw;
	m_pShot_RotateYaw_SubCh1 = new CShot_RotateYaw;
	m_pShot_RotatePitch = new CShot_RotatePitch;
	m_pShot_RotatePitch_Spline = new CShot_RotatePitch_Spline;
	m_pShot_RotateRoll = new CShot_RotateRoll;

	m_pShot_PushIn = new CShot_PushIn;
	m_pShot_PushOut = new CShot_PushOut;
	m_pShot_FixPivot = new CShot_MovePivot;

	m_pShot_Victory = new CShot_ActorVictory;
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

void CMovieDirector::CreateTake_SakuraVictory()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);
	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);

	pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);
	pTake->AddShot(ShotName_RotateYaw_SubCh1, m_pShot_RotateYaw_SubCh1);
	pTake->AddShot(ShotName_RotatePitch, m_pShot_RotatePitch);
	pTake->AddShot(ShotName_RotatePitch_Spline, m_pShot_RotatePitch_Spline);
	pTake->AddShot(ShotName_RotateRoll, m_pShot_RotateRoll);

	pTake->AddShot(ShotName_PushOut, m_pShot_PushOut);
	pTake->AddShot(ShotName_FixPivot, m_pShot_FixPivot);

	pTake->AddShot(ShotName_Victory, m_pShot_Victory);

	m_takeMap.emplace(TakeName_SakuraVictory, pTake);
}

void CMovieDirector::CreateTake_GaneshaBorn()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_FixPivot, m_pShot_FixPivot);

	pTake->AddShot(ShotName_BlackFadeIn, m_pShot_BlackFadeIn);
	pTake->AddShot(ShotName_BlackFadeOut, m_pShot_BlackFadeOut);

	pTake->AddShot(ShotName_PushIn, m_pShot_PushIn);
	pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);

	//pTake->AddShot(ShotName_FixPivot, m_pShot_FixPivot);

	// start ~ before jump
	//pTake->AddShot(ShotName_PushIn, m_pShot_PushIn);
	//pTake->AddShot(ShotName_RotateYaw, m_pShot_RotateYaw);

	// jump ~ land
	//pTake->AddShot(ShotName_RotatePitch, m_pShot_RotatePitch);
	pTake->AddShot(ShotName_RotatePitch_Spline, m_pShot_RotatePitch_Spline);
	m_pGaneshaPitchCurve = new CSplineCurve;
	m_pGaneshaPitchCurve->AddPoint(_float3(2.f, 30.f, 0.f));
	m_pGaneshaPitchCurve->AddPoint(_float3(2.6f, 10.f, 0.f));
	m_pGaneshaPitchCurve->AddPoint(_float3(2.9f, -45.f, 0.f));
	m_pGaneshaPitchCurve->AddPoint(_float3(4.f, -45.f, 0.f));
	CSplineCurve::Desc desc;
	m_pGaneshaPitchCurve->CreateCurve(&desc);

	// land ~ end

	//pTake->AddShot(ShotName_RotateYaw_SubCh1, m_pShot_RotateYaw_SubCh1);
	
	
	m_takeMap.emplace(TakeName_GaneshaBorn, pTake);
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
	ry2_desc.endEulerAngle = 20.f;
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
	
	CShot_MovePivot::Desc fp_desc;
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	fp_desc.startOffset = pActor->GetTransform()->GetUp() * 0.15f + pActor->GetTransform()->GetRight() * 0.1f;
	fp_desc.endOffset = pActor->GetTransform()->GetUp() * 0.11f + pActor->GetTransform()->GetRight() * -0.15f;
	pTake->ReadyShot(ShotName_FixPivot, 0.6f, 3.6f, &fp_desc, 0.6f);


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


	CShot_MovePivot::Desc fp_desc;
	fp_desc.pTargetTransform = Engine::GET_CUR_SCENE->FindObjectWithKey(L"MB_Ganesha")->GetTransform().get();
// 	fp_desc.startOffset = pActor->GetTransform()->GetUp() * 0.15f + pActor->GetTransform()->GetRight() * 0.1f;
// 	fp_desc.endOffset = pActor->GetTransform()->GetUp() * 0.11f + pActor->GetTransform()->GetRight() * -0.15f;
	pTake->ReadyShot(ShotName_FixPivot, 0.f, 12.f, &fp_desc, 0.f);


	// start ~ before jump
	CShot_BlackFadeOut::Desc blo_desc;
	blo_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeOut, 0.f, 0.5f, &blo_desc, 0.f);

	CShot_BlackFadeIn::Desc bfi_desc;
	bfi_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn, 0.6f, 1.1f, &bfi_desc, 0.5f);
	
	CShot_RotateYaw::Desc ry_desc;
	ry_desc.pTargetTransform = fp_desc.pTargetTransform;
	ry_desc.startEulerAngle = 45.f;
	ry_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateYaw, 0.6f, 2.6f, &ry_desc, 0.6f);

	CShot_PushIn::Desc pi_desc;
	pi_desc.startDistance = 5.f;
	pi_desc.endDistance = 4.f;
	pTake->ReadyShot(ShotName_PushIn, 0.6f, 2.6f, &pi_desc, 0.6f);

	// jump ~ land

	CShot_RotatePitch_Spline::Desc rps_desc;
	rps_desc.angleCurve = m_pGaneshaPitchCurve;
	pTake->ReadyShot(ShotName_RotatePitch_Spline, 2.6f, 4.6f, &rps_desc, 0.5f);

	// land ~ end


	m_pCurTake = pTake;

	m_pCurTake->StartTake();
	m_onAir = true;
}

void CMovieDirector::Cut()
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
