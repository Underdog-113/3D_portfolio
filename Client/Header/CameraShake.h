#pragma once

struct Wave
{
	float amplitude = 0.f;
	float frequency = 0.f;
	float offset = 0.f;
};

class CCameraShake
{
	enum ShakeType { Low, High, Boom, Run };

public:
	CCameraShake();
	~CCameraShake();

public:
	void PlayShake();
	bool IsShaking();
	
	_float AdvanceSinWave(Wave wave);

public:
	void Preset_Low(_float3 eventPos);
	void Preset_High(_float3 eventPos);
	void Preset_Boom(_float3 eventPos);
	
	void Preset_Run();

	void SetDistanceRate(_float3 eventPos);

private:
	GETTOR_SETTOR(SP(Engine::CCamera), m_spCamera, nullptr, Camera)

	float m_timer = 0.f;
	float m_duration = 0.f;			
	float m_blendInTime = 0.1f;
	float m_blendOutTime = 0.2f;
	
	float m_innerRadius = 1.f;
	float m_outerRadius = 3.f;
	float m_distanceRate = 1.f;

	float m_amplitudeRate = 0.f;
	
private: // Rot Oscilation
	GETTOR (_float3, m_rotOscilation, ZERO_VECTOR, RotateOscilation)
	Wave m_pitchWave;
	Wave m_yawWave;
	Wave m_rollWave;

private: // Loc Oscilation
	GETTOR(_float3, m_locOscilation, ZERO_VECTOR, LocationOscilation)
	Wave m_xWave;
	Wave m_yWave;
	Wave m_zWave;
};