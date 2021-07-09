#pragma once

#define NearTake 1.5f
#define MidTake 3.f
#define FarTake 5.f

#define NearAngle 0.f
#define MidAngle D3DXToRadian(10.f)
#define FarAngle D3DXToRadian(15.f)


#define MaxChaseDistance 0.5f

class CCameraShake;
class CStageCameraMan
{
public:
	enum TakeType { Near, Mid, Far, Custom, Change };

public:
	CStageCameraMan();
	~CStageCameraMan();

	void Start();

	void UpdateCameraMan();
	void PivotChasing();

	void SetIsTargeting(bool value);

public:
	void SetNearTake();
	void SetMidTake();
	void SetFarTake();
	void SetCustomTake(_float dstMaxDistance, _float changeSpeed, _float dstXAngle);
	void ChangeTake();

	void AppendTargetCorrecting();
	void AppendHorizontalCorrecting();
	
	bool MouseControlMode();
	void ManualControlMode();
	void AutoControlMode();

public:
	void ShakeCamera_Low(_float3 eventPos);

	void ShakeCamera_Theresa_Charge1Impact(_float3 eventPos);
	void ShakeCamera_Theresa_Charge2Impact(_float3 eventPos);
	void ShakeCamera_Theresa_CrossImpact(_float3 eventPos);

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
	GETTOR			(_bool,					m_isTargeting,	false,		IsTargeting)		
	GETTOR			(CCameraShake*,			m_pCameraShake,	nullptr,	CameraShake)	
	GETTOR_SETTOR	(_bool,					m_isSwitching,	false,		IsSwitching)
	_float3 m_noShakePos = ZERO_VECTOR;
	_float3 m_noShakeRot = ZERO_VECTOR;

	bool m_returnToActor = false;
	_float m_targetingTimer = 0.f;
	bool m_isStart = false;
private:
	_float m_followTimer = 0.f;

	_float3 m_dstPivotPos = ZERO_VECTOR;
	_float m_movePivotTimer = 0.f;
	_float m_chaseSpeed = 7.f;
	_float m_chaseSpeedIncreaseTimer = 0.f;

private:
	TakeType m_curTakeType = Mid;
	TakeType m_nextTakeType = Mid;
	_float m_curMaxDist = 3.f;
	_float m_dstMaxDist = 3.f;
	_float m_gotoNextTakeTimer = 0.f;
	_float m_changeTakeTimer = 0.f;
	_float m_changeTakeSpeed = 2.f;

private:
	_float m_rotateXStart = 0.f;
	_float m_rotateXDst = 0.f;
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

	_uint m_prevMoveKey = 0;
};