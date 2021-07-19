#include "stdafx.h"
#include "..\Header\MovieDirector.h"

#include "WndApp.h"
#include "FadeInOutC.h"
#include "Take.h"

CMovieDirector::CMovieDirector()
{
}


CMovieDirector::~CMovieDirector()
{
}

void CMovieDirector::Start()
{
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

	m_isStart = true;

}

void CMovieDirector::UpdateDirector()
{
	if (!m_isStart)
		Start();

	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_1))
		CStageControlTower::GetInstance()->SetDirectorMode(true);
	if (Engine::IMKEY_PRESS(KEY_TAB) && Engine::IMKEY_DOWN(KEY_2))
		CStageControlTower::GetInstance()->SetDirectorMode(false);

	if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_PRESS(KEY_LEFT))
	{
		m_pWhiteFade->AddAlpha(-GET_DT);
	}
	if (Engine::IMKEY_PRESS(KEY_CONTROL) && Engine::IMKEY_PRESS(KEY_RIGHT))
	{
		m_pWhiteFade->AddAlpha(GET_DT);
	}
}

void CMovieDirector::StartTake(std::wstring takeName)
{
	auto pTake = m_takeMap[takeName];

	pTake->StartTake();
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
