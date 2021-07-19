#pragma once

class CMovieDirector
{
public:
	CMovieDirector();
	~CMovieDirector();

public:
	void Start();
	void UpdateDirector();




public:
	_float3 GetBezierPoint(_float3 startPoint, _float3 midPoint, _float3 endPoint, float detail);

private:
	GETTOR			(SP(Engine::CImageObject),	m_spWhiteFadeImage,		nullptr,	WhiteFadeImage)
	GETTOR			(Engine::CFadeInOutC*,				m_pWhiteFade,			nullptr,	WhiteFade)
	
	bool m_isStart = false;

};

