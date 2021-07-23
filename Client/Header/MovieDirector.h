#pragma once

#define ShotName_WhiteFadeIn		L"WhiteFadeIn"
#define ShotName_WhiteFadeOut		L"WhiteFadeOut"
#define ShotName_BlackFadeIn		L"BlackFadeIn"
#define ShotName_BlackFadeOut		L"BlackFadeOut"

#define ShotName_RotateAround		L"RotateAround"
#define ShotName_RotateYaw			L"RotateYaw"
#define ShotName_RotateYaw_SubCh1	L"RotateYaw_SubCh1"
#define ShotName_RotatePitch		L"RotatePitch"
#define ShotName_RotatePitch_Spline	L"RotatePitch_Spline"
#define ShotName_RotateRoll			L"RotateRoll"

#define ShotName_PushIn				L"PushIn"
#define ShotName_PushOut			L"PushOut"
#define ShotName_FixPivot			L"FixPivot"

#define ShotName_Victory			L"Victory"


#define TakeName_Failure			L"Failure"

#define TakeName_SakuraVictory		L"SakuraVictory"


#define TakeName_GaneshaBorn		L"GaneshaBorn"

class CShot;	 
class CTake;
class CSplineCurve;
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

	void CreateTake_Failure();
	void CreateTake_SakuraVictory();

	void CreateTake_GaneshaBorn();

public:
	void StartTake_Failure();
	void StartTake_SakuraVictory();
	void StartTake_GaneshBorn();

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

	
	CSplineCurve* m_pGaneshaPitchCurve = nullptr;

	bool m_isStart = false;

private:
	CShot* m_pShot_WhiteFadeIn = nullptr;
	CShot* m_pShot_WhiteFadeOut = nullptr;

	CShot* m_pShot_BlackFadeIn = nullptr;
	CShot* m_pShot_BlackFadeOut = nullptr;

	CShot* m_pShot_RotateAround = nullptr;
	CShot* m_pShot_RotateYaw = nullptr;
	CShot* m_pShot_RotateYaw_SubCh1 = nullptr;
	CShot* m_pShot_RotatePitch = nullptr;
	CShot* m_pShot_RotatePitch_Spline = nullptr;
	CShot* m_pShot_RotateRoll = nullptr;

	CShot* m_pShot_PushIn = nullptr;
	CShot* m_pShot_PushOut = nullptr;
	CShot* m_pShot_FixPivot = nullptr;

	CShot* m_pShot_Victory = nullptr;
};

