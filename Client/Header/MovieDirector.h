#pragma once

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
	void StartTake(std::wstring takeName);

	_bool EndDirecting();



public:
	_float3 GetBezierPoint(_float3 startPoint, _float3 midPoint, _float3 endPoint, float detail);

private:
	GETTOR			(SP(Engine::CImageObject),	m_spWhiteFadeImage,		nullptr,	WhiteFadeImage)
	GETTOR			(Engine::CFadeInOutC*,				m_pWhiteFade,			nullptr,	WhiteFade)
	
	std::map<std::wstring, CTake*> m_takeMap;

	CTake* m_pCurTake = nullptr;

	bool m_isStart = false;

};

