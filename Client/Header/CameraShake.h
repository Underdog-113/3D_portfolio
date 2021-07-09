#pragma once

struct Wave
{
	float amplitude = 0.f;			// 진폭, -amplitued ~ amplitude
	float frequency = 0.f;			// 초당 주파수
	float offset = 0.f;				// 그래프에서의 타임라인 시작 위치

	float ampAxisOffset = 0.f;
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

public:	/* Player Action */
	void Preset_LowAttack(_float3 eventPos);	// kiana base attack, theresa base attack
	void Preset_HighAttack_Vert(_float3 eventPos); // cat paw attack_5, theresa axe down
	void Preset_HighAttack_Horz(_float3 eventPos); // theresa axe horz

	void Preset_Theresa_Charge1Impact(_float3 eventPos);
	void Preset_Theresa_Charge2Impact(_float3 eventPos);
	void Preset_Theresa_UltImpact(_float3 eventPos);
	void Preset_Theresa_CrossImpact(_float3 eventPos);

public: /* Enemy Action */
	void Preset_Boom(_float3 eventPos);
	
	void Preset_Run();

	void SetDistanceRate(_float3 eventPos);

private:
	void ResetAllMember();
	void ResetRotMember();
	void ResetLocMember();
	void ResetWave(Wave& wave);

private:
	GETTOR_SETTOR(SP(Engine::CCamera), m_spCamera, nullptr, Camera)

	float m_timer = 0.f;
	float m_duration = 0.f;			
	float m_blendInTime = 0.1f;			// 원래는 blend in 섞이는 시간, 지금은 진폭 감쇠에만 사용
	float m_blendOutTime = 0.2f;		// 원래는 blend out
	// shake while blend in -> shake -> shake while blend out
	
	float m_innerRadius = 5.f;			// 현재 카메라 위치에서 amplitude를 1.f배로 들을 수 있는 거리
	float m_outerRadius = 10.f;			// 이거 밖으로는 0.f배
	float m_distanceRate = 1.f;

	float m_amplitudeRate = 0.f;
	
private: // Rot Oscilation, radian 값으로 해주세요
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