#include "stdafx.h"
#include "..\Header\CameraShake.h"


CCameraShake::CCameraShake()
{

	// blend in�� 0�̸�, wave�� 1 ���¿��� ����.
	// 
}


CCameraShake::~CCameraShake()
{
}

void CCameraShake::PlayShake()
{
	m_timer += GET_DT;

	if (m_timer < m_blendInTime)
	{
		m_amplitudeRate = m_timer / m_blendInTime;
	}
	else if(m_timer >  m_duration - m_blendOutTime)
	{
		m_amplitudeRate = (m_duration - m_timer) / m_blendOutTime;
	}
	else
	{
		m_amplitudeRate = 1.f;
	}

	m_amplitudeRate *= m_distanceRate;

	m_rotOscilation.x = AdvanceSinWave(m_pitchWave);
	m_rotOscilation.y = AdvanceSinWave(m_yawWave);
	m_rotOscilation.z = AdvanceSinWave(m_rollWave);

	m_locOscilation.x = AdvanceSinWave(m_xWave);
	m_locOscilation.y = AdvanceSinWave(m_yWave);
	m_locOscilation.z = AdvanceSinWave(m_zWave);
}

bool CCameraShake::IsShaking()
{
	if (m_timer < m_duration)
		return true;

	return false;
}

_float CCameraShake::AdvanceSinWave(Wave wave)
{
	_float sinFrequency = 2 * PI * wave.frequency;
	_float curTimeline = sinFrequency * (m_timer + wave.offset);
	_float curAmplitude = wave.amplitude * m_amplitudeRate;

	return sinf(curTimeline) * curAmplitude;
}

void CCameraShake::Preset_Low(_float3 eventPos)
{
	SetDistanceRate(eventPos);
	m_timer = 0.f;

	m_duration = 0.2f;
	m_blendInTime = 0.f;
	m_blendOutTime = 0.1f;

	float randomOffset = 0.f;
	randomOffset = (rand() % 100) / 100.f;
	m_pitchWave.amplitude = 0.01f;
	m_pitchWave.frequency = 10.f;
	m_pitchWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	m_yawWave.amplitude = 0.01f;
	m_yawWave.frequency = 10.f;
	m_yawWave.offset = randomOffset;

	randomOffset = 0.f;
	m_rollWave.amplitude = 0.f;
	m_rollWave.frequency = 0.f;
	m_rollWave.offset = 0.f;

	randomOffset = 0.f;
	m_xWave.amplitude = 0.f;
	m_xWave.frequency = 0.f;
	m_xWave.offset = 0.f;

	randomOffset = 0.f;
	m_yWave.amplitude = 0.f;
	m_yWave.frequency = 0.f;
	m_yWave.offset = 0.f;

	randomOffset = 0.f;
	m_zWave.amplitude = 0.f;
	m_zWave.frequency = 0.f;
	m_zWave.offset = 0.f;
}

void CCameraShake::Preset_High(_float3 eventPos)
{
	SetDistanceRate(eventPos);
	m_timer = 0.f;
}

void CCameraShake::Preset_Boom(_float3 eventPos)
{
	SetDistanceRate(eventPos);
	m_timer = 0.f;

	m_duration = 0.25f;
	m_blendInTime = 0.1f;
	m_blendOutTime = 0.2f;

	float randomOffset = 0.f;
	randomOffset = (rand() % 100) / 100.f;
	m_pitchWave.amplitude = 10.f;
	m_pitchWave.frequency = 25.f;
	m_pitchWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	m_yawWave.amplitude = 5.f;
	m_yawWave.frequency = 25.f;
	m_yawWave.offset = randomOffset;

	randomOffset = 0.f;
	m_rollWave.amplitude = 0.f;
	m_rollWave.frequency = 0.f;
	m_rollWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	m_xWave.amplitude = 70.f;
	m_xWave.frequency = 1.f;
	m_xWave.offset = randomOffset;

	randomOffset = 0.f;
	m_yWave.amplitude = 0.f;
	m_yWave.frequency = 0.f;
	m_yWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	m_zWave.amplitude = 70.f;
	m_zWave.frequency = 25.f;
	m_zWave.offset = randomOffset;

}

void CCameraShake::Preset_Run()
{
	SetDistanceRate(m_spCamera->GetTransform()->GetPosition());
	m_timer = 0.f;
}

void CCameraShake::SetDistanceRate(_float3 eventPos)
{
	_float3 camPos = m_spCamera->GetTransform()->GetPosition();
	_float3 dir = eventPos - camPos;
	_float len = D3DXVec3Length(&dir);

	if (len > m_outerRadius)
		m_distanceRate = 0.f;
	else if (len > m_innerRadius)
		m_distanceRate = (len - m_innerRadius) / (m_outerRadius - m_innerRadius);
	else
		m_distanceRate = 1.f;
}