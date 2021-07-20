#pragma once

#include "Take.h"
#include "MovieDirector.h"
#include "StageCameraMan.h"

class CShot
{
public:
	CShot();
	~CShot();

public:
	virtual void Ready(CTake * pTake, _float startTimeline, _float endTimeline, void* pDesc) PURE;
	virtual void Enter() PURE;
	virtual void Action() PURE;
	virtual void Cut() PURE;
	virtual void Rollback() PURE;
	
	virtual _bool CheckOnTake(_float takeTimer);
	void CheckShotRollback(_float takeTimer);
	_bool CheckShotEnd(_float takeTimer);
	_float GetTimeline();

protected:		
	GETTOR_SETTOR(CMovieDirector*, m_pMovieDirector, nullptr, MovieDirector)
	GETTOR_SETTOR(CStageCameraMan*, m_pCameraMan, nullptr, CameraMan)
	GETTOR_SETTOR(SP(Engine::CCamera), m_spCamera, nullptr, Camera)


	GETTOR_SETTOR(CTake*, m_pOnAirTake, nullptr, OnAirTake)

protected:
	GETTOR_SETTOR(_float, m_startTimeline, 0.f, StartTimeline)
	GETTOR_SETTOR(_float, m_endTimeline, 0.f, endTimeline)
	GETTOR_SETTOR(_bool, m_isEndless, false, IsEndless)

	_bool m_isEnterAction = false;
	_bool m_isExitAction = false;
};

