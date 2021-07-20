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

CMovieDirector::CMovieDirector()
{
}


CMovieDirector::~CMovieDirector()
{
	SAFE_DELETE(m_pShot_WhiteFadeIn)
	SAFE_DELETE(m_pShot_WhiteFadeOut)
	SAFE_DELETE(m_pShot_BlackFadeIn)
	SAFE_DELETE(m_pShot_RotateAround)

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

	Create_FailureTake();

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
		Start_FailureTake();

	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_2))
		Cut();


	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_3))
	{
		Start_FailureTake();
		m_pCurTake->SeteditMode(true);
	}

// 	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_1))
// 		CStageControlTower::GetInstance()->SetDirectorMode(true);
// 	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_2))
// 		CStageControlTower::GetInstance()->SetDirectorMode(false);

	if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_PRESS(KEY_LEFT))
	{
		m_pWhiteFade->AddAlpha(-GET_DT);
	}
	if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_PRESS(KEY_RIGHT))
	{
		m_pWhiteFade->AddAlpha(GET_DT);
	}
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


}

void CMovieDirector::Create_AllShots()
{
	m_pShot_WhiteFadeIn = new CShot_WhiteFadeIn;
	m_pShot_WhiteFadeOut = new CShot_WhiteFadeOut;

	m_pShot_BlackFadeIn = new CShot_BlackFadeIn;

	m_pShot_RotateAround = new CShot_RotateAround;
}

void CMovieDirector::Create_FailureTake()
{
	CTake* pTake = new CTake;

	pTake->AddShot(ShotName_WhiteFadeIn, m_pShot_WhiteFadeIn);
	pTake->AddShot(ShotName_WhiteFadeOut, m_pShot_WhiteFadeOut);
	pTake->AddShot(ShotName_BlackFadeIn, m_pShot_BlackFadeIn);
	pTake->AddShot(ShotName_RotateAround, m_pShot_RotateAround);

	m_takeMap.emplace(TakeName_Failure, pTake);
}

void CMovieDirector::Start_FailureTake()
{
	auto pTake = m_takeMap[TakeName_Failure];
	
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
	ra_desc.pPivotObject = pActor;
	ra_desc.offset = pActor->GetTransform()->GetRight() * 0.5f;
	ra_desc.rotateSpeed = 12.f;
	pTake->ReadyShot(ShotName_RotateAround, 0.5f, 100.f, &ra_desc);

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
