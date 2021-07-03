#pragma once

#define NearTake 1.5f
#define MidTake 3.f
#define FarTake 4.5f


class CStageCameraMan
{
public:
	enum TakeType { Near, Mid, Far, Change };

public:
	CStageCameraMan();
	~CStageCameraMan();

	void Start();

	void UpdateCameraMan();
	void PivotChasing();

public:
	void SetNearTake();
	void SetMidTake();
	void SetFarTake();
	void ChangeTake();

	void AppendTargetCorrecting();
	void AppendHorizontalCorrecting();
	
	void ShakeCamera();

	bool MouseControlMode();
	void ManualControlMode();
	void AutoControlMode();

private:

	float FloatLerp(float _start, float _end, float _time)
	{
		return _start * (1.f - _time) + _time * _end;
	}

	bool CheckNoAction();


	void ShowMouseCursor();
	void HideMouseCursor();



private:
	GETTOR_SETTOR	(SP(Engine::CCamera),	m_spCamera,		nullptr,	Camera)		
	GETTOR			(SP(Engine::CObject),	m_spPivot,		nullptr,	Pivot)

private:
	_float m_followTimer = 0.f;

	_float3 m_dstPivotPos = ZERO_VECTOR;
	_float m_movePivotTimer = 0.f;
	_float m_chaseSpeed = 5.f;
	_float m_chaseSpeedIncreaseTimer = 0.f;

private:
	TakeType m_curTakeType = Mid;
	TakeType m_nextTakeType = Mid;
	_float m_curMaxDist = 3.f;
	_float m_dstMaxDist = 3.f;
	_float m_gotoNearTakeTimer = 0.f;
	_float m_changeTakeTimer = 0.f;
	_float m_changeTakeSpeed = 2.f;

private:
	_float m_rotateYDst = 0.f;
	_float m_rotateSpeed = D3DXToRadian(3.f);
	_float m_rotateLerpTimer = 0.f;
	_float m_rotateLerpStart = 0.f;
	
	_float m_horzCorrectingSpeed = 5.f;
	_float m_speedIncreaseTimer = 0.f;
private:
	float m_enterAutoTimer = 0.f;

	bool m_whyCursorOffOneMore = true;
	bool m_cursorOn = true;
	float m_hideCursorTimer = 0.f;

	bool m_manualControl = false;
	bool m_noAction = true;
};