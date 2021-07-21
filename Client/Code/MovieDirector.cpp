#include "stdafx.h"
#include "..\Header\MovieDirector.h"

#include "WndApp.h"
#include "FadeInOutC.h"
#include "Take.h"
#include "Valkyrie.h"

#include "Shot_WhiteFadeIn.h"
#include "Shot_WhiteFadeOut.h"
#include "Shot_BlackFadeIn.h"
#include "Shot_RotateAround.h"
#include "Shot_RotateYaw.h"
#include "Shot_RotateRoll.h"
#include "Shot_PushOut.h"

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
	SAFE_DELETE(m_pShot_RotateRoll)
	SAFE_DELETE(m_pShot_PushOut)

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
		StartTake_Failure();

	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_2))
		Cut();


	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_3))
	{
		StartTake_SakuraVictory();
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

	m_pShot_RotateAround = new CShot_RotateAround;
	m_pShot_RotateYaw = new CShot_RotateYaw;
	//m_pShot_RotateAround = new CShot_RotateAround;
	m_pShot_RotateRoll = new CShot_RotateRoll;

	m_pShot_PushOut = new CShot_PushOut;
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
	pTake->AddShot(ShotName_RotateRoll, m_pShot_RotateRoll);

	pTake->AddShot(ShotName_PushOut, m_pShot_PushOut);

	m_takeMap.emplace(TakeName_SakuraVictory, pTake);
}

void CMovieDirector::StartTake_Failure()
{
	auto pTake = m_takeMap[TakeName_Failure];
	m_spBlackFadeImage->SetIsEnabled(true);
	m_spWhiteFadeImage->SetIsEnabled(true);

	CShot_WhiteFadeIn::Desc wfi_desc;
	wfi_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeIn, 0.6f, 1.1f, &wfi_desc);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, 0.f, 0.5f, &wfo_desc);

	CShot_BlackFadeIn::Desc bfi_desc;
	bfi_desc.pBlackFade = m_pBlackFade;
	pTake->ReadyShot(ShotName_BlackFadeIn, 0.5f, 0.6f, &bfi_desc);

	CShot_RotateAround::Desc ra_desc;
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	ra_desc.offset = pActor->GetTransform()->GetRight() * 0.5f;
	ra_desc.rotateSpeed = 12.f;
	pTake->ReadyShot(ShotName_RotateAround, 0.5f, 100.f, &ra_desc);

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
	pTake->ReadyShot(ShotName_WhiteFadeIn, 0.6f, 1.1f, &wfi_desc);

	CShot_WhiteFadeOut::Desc wfo_desc;
	wfo_desc.pWhiteFade = m_pWhiteFade;
	pTake->ReadyShot(ShotName_WhiteFadeOut, 0.f, 0.5f, &wfo_desc);

	CShot_RotateYaw::Desc ry_desc;
	ry_desc.startEulerAngle = -90.f;
	ry_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateYaw, 0.6f, 3.6f, &ry_desc);

	CShot_RotateRoll::Desc rr_desc;
	rr_desc.startEulerAngle = 45.f;
	rr_desc.endEulerAngle = 0.f;
	pTake->ReadyShot(ShotName_RotateRoll, 0.6f, 3.6f, &rr_desc);

	CShot_PushOut::Desc po_desc;
	auto pActor = CStageControlTower::GetInstance()->GetCurrentActor();
	po_desc.offset = pActor->GetTransform()->GetUp() * -0.1f;
	po_desc.startDistance = 0.5f;
	po_desc.endDistance = 1.f;
	pTake->ReadyShot(ShotName_PushOut, 0.6f, 3.6f, &po_desc);

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
