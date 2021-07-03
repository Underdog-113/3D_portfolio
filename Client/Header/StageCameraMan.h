#pragma once
class CStageCameraMan
{
public:
	CStageCameraMan();
	~CStageCameraMan();

	void Awake();
	void UpdateCameraMan();

public:
	void SetNearTake();
	void SetMiddleTake();
	void SetFarTake();

	void ApplyTargetingMove();
	void ApplyHorizontalMove();
	
	void ShakeCamera();

	void ManualControlMode();
	void AutoControlMode();

private:
	GETTOR_SETTOR(SP(Engine::CCamera), m_spCamera, nullptr, Camera)

	float m_enterAutoTimer = 0.f;
};