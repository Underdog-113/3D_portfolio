#pragma once

#define ShotName_WhiteFadeIn		L"WhiteFadeIn"
#define ShotName_WhiteFadeOut		L"WhiteFadeOut"
#define ShotName_BlackFadeIn		L"BlackFadeIn"
#define ShotName_RotateAround		L"RotateAround"

#define TakeName_Failure			L"Failure"

class CShot;	 
class CTake;
class CMovieDirector
{
public:
	CMovieDirector();
	~CMovieDirector();

public:
	void Start();
	void UpdateDirector();

public:
	void Create_FadeImages();

	void Create_AllShots();

	void Create_FailureTake();

public:
	void Start_FailureTake();

	void Cut();

public:
	_float3 GetBezierPoint(_float3 startPoint, _float3 midPoint, _float3 endPoint, float detail);

private:
	GETTOR			(SP(Engine::CImageObject),	m_spWhiteFadeImage,		nullptr,	WhiteFadeImage)
	GETTOR			(SP(Engine::CImageObject),	m_spBlackFadeImage,		nullptr,	BlackFadeImage)
	GETTOR			(Engine::CFadeInOutC*,				m_pWhiteFade,			nullptr,	WhiteFade)
	GETTOR			(Engine::CFadeInOutC*,				m_pBlackFade,			nullptr,	BlackFade)
	
	std::unordered_map<std::wstring, CTake*> m_takeMap;

	CTake* m_pCurTake = nullptr;
	_bool m_onAir = false;


	bool m_isStart = false;

private:
	CShot* m_pShot_WhiteFadeIn = nullptr;
	CShot* m_pShot_WhiteFadeOut = nullptr;

	CShot* m_pShot_BlackFadeIn = nullptr;

	CShot* m_pShot_RotateAround = nullptr;

};

