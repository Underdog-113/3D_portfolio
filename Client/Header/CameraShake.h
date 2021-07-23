#pragma once


struct Wave
{
	float point = 0.f;

	float amplitude = 0.f;			// ����, -amplitued ~ amplitude
	float frequency = 0.f;			// �ʴ� ���ļ�
	float offset = 0.f;				// �׷��������� Ÿ�Ӷ��� ���� ��ġ

	float ampAxisOffset = 0.f;
};

struct ShakeChannel
{
	bool enable = true;

	float m_timer = 0.f;
	float m_duration = 0.f;
	float m_blendInTime = 0.1f;			// ������ blend in ���̴� �ð�, ������ ���� ���迡�� ���
	float m_blendOutTime = 0.2f;		// ������ blend out

	float m_distanceRate = 1.f;
	float m_amplitudeRate = 0.f;

	Wave m_pitchWave;
	Wave m_yawWave;
	Wave m_rollWave;

	Wave m_xWave;
	Wave m_yWave;
	Wave m_zWave;

	Wave m_Wave;
};

class CCameraShake
{
	enum ShakeChannelType { Player, Run, Max };

public:
	CCameraShake();
	~CCameraShake();

public:
	void PlayShake();
	void PlayChannel(ShakeChannel* channel);
	void PlayChannelOnMovie(_float timeline);
	bool IsShaking();
	
	void AdvanceSinWave(Wave* wave, ShakeChannel* channel);

	_float3 GetRotateOscilation();
	_float3 GetLocationOscilation();

	void Preset_LowAttack(_float3 eventPos);	// kiana base attack, theresa base attack
	void Preset_HighAttack_Vert(_float3 eventPos); // cat paw attack_5, theresa axe down
	void Preset_HighAttack_Horz(_float3 eventPos); // theresa axe horz
	void Preset_Land();

	void Preset_Kiana_ForwardAttack();
	void Preset_Kiana_Claw5();
	void Preset_Kiana_UltraActive();

	void Preset_Theresa_Charge1Impact(_float3 eventPos);
	void Preset_Theresa_Charge2Impact(_float3 eventPos);
	void Preset_Theresa_CrossImpact(_float3 eventPos);

public:
	void Preset_Kiana_Run();

public: /* Enemy Action */
	void Preset_Boom(_float3 eventPos);
	
	void SetDistanceRate(_float3 eventPos, ShakeChannel* channel);

	void ResetAllMember(ShakeChannel* channel);
private:
	void ResetRotMember(ShakeChannel* channel);
	void ResetLocMember(ShakeChannel* channel);
	void ResetWave(Wave* wave);



private:
	GETTOR_SETTOR(SP(Engine::CCamera), m_spCamera, nullptr, Camera)
	GETTOR_SETTOR	(_bool,			m_isMovieOn,	false,	IsMovieOn)
	GETTOR_SETTOR	(ShakeChannel*,	m_pMovieChannel,	nullptr,	MovieChannel)
			
	float m_innerRadius = 5.f;			// ���� ī�޶� ��ġ���� amplitude�� 1.f��� ���� �� �ִ� �Ÿ�
	float m_outerRadius = 10.f;			// �̰� �����δ� 0.f��
;
	

private:
	ShakeChannel m_shakeChannel[Max];

};