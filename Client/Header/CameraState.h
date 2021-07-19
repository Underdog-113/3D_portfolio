#pragma once

class CTake;
class CMovieDirector;
class CStageCameraMan;
class CShot
{
public:
	CShot();
	~CShot();

	virtual void Ready() PURE;
	virtual void Action() PURE;
	virtual void Cut() PURE;
	

protected:		
	GETTOR_SETTOR(CMovieDirector*, m_pMovieDirector, nullptr, MovieDirector)
	GETTOR_SETTOR(CStageCameraMan*, m_pCameraMan, nullptr, CameraMan)
	GETTOR_SETTOR(SP(Engine::CCamera), m_pCamera, nullptr, Camera)


	GETTOR_SETTOR(CTake*, m_pOnAirTake, nullptr, OnAirTake)
};

