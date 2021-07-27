#include "stdafx.h"
#include "..\Header\CameraShake.h"


CCameraShake::CCameraShake()
{
}


CCameraShake::~CCameraShake()
{
}

void CCameraShake::PlayShake()
{
	if (m_shakeChannel[Player].enable)
		PlayChannel(&m_shakeChannel[Player]);
	if (m_shakeChannel[Monster].enable)
		PlayChannel(&m_shakeChannel[Monster]);
}

void CCameraShake::PlayShake_Pure()
{
	if (m_shakeChannel[Player].enable)
		PlayChannel_Pure(&m_shakeChannel[Player]);
	if (m_shakeChannel[Monster].enable)
		PlayChannel_Pure(&m_shakeChannel[Monster]);
}

void CCameraShake::PlayChannel(ShakeChannel* channel)
{
	if (m_isMovieOn)
		return;

	channel->m_timer += GET_PLAYER_DT;

	if (channel->m_timer < channel->m_blendInTime)
	{
		channel->m_amplitudeRate = channel->m_timer / channel->m_blendInTime;
	}
	else if (channel->m_timer > channel->m_duration - channel->m_blendOutTime)
	{
		if (channel->m_blendOutTime == 0.f)
			channel->m_amplitudeRate = 0.f;
		else
			channel->m_amplitudeRate = (channel->m_duration - channel->m_timer) / channel->m_blendOutTime;
	}
	else
	{
		channel->m_amplitudeRate = 1.f;
	}

	channel->m_amplitudeRate *= channel->m_distanceRate;

	AdvanceSinWave(&channel->m_pitchWave, channel);
	AdvanceSinWave(&channel->m_yawWave, channel);
	AdvanceSinWave(&channel->m_rollWave, channel);

	AdvanceSinWave(&channel->m_xWave, channel);
	AdvanceSinWave(&channel->m_yWave, channel);
	AdvanceSinWave(&channel->m_zWave, channel);
}

void CCameraShake::PlayChannel_Pure(ShakeChannel * channel)
{
	if (m_isMovieOn)
		return;

	channel->m_timer += GET_PURE_DT;

	if (channel->m_timer < channel->m_blendInTime)
	{
		channel->m_amplitudeRate = channel->m_timer / channel->m_blendInTime;
	}
	else if (channel->m_timer > channel->m_duration - channel->m_blendOutTime)
	{
		if (channel->m_blendOutTime == 0.f)
			channel->m_amplitudeRate = 0.f;
		else
			channel->m_amplitudeRate = (channel->m_duration - channel->m_timer) / channel->m_blendOutTime;
	}
	else
	{
		channel->m_amplitudeRate = 1.f;
	}

	channel->m_amplitudeRate *= channel->m_distanceRate;

	AdvanceSinWave(&channel->m_pitchWave, channel);
	AdvanceSinWave(&channel->m_yawWave, channel);
	AdvanceSinWave(&channel->m_rollWave, channel);

	AdvanceSinWave(&channel->m_xWave, channel);
	AdvanceSinWave(&channel->m_yWave, channel);
	AdvanceSinWave(&channel->m_zWave, channel);
}

void CCameraShake::PlayChannelOnMovie(_float timeline)
{
	m_pMovieChannel->m_timer = m_pMovieChannel->m_duration * timeline;

	if (m_pMovieChannel->m_timer < m_pMovieChannel->m_blendInTime)
	{
		m_pMovieChannel->m_amplitudeRate = m_pMovieChannel->m_timer / m_pMovieChannel->m_blendInTime;
	}
	else if (m_pMovieChannel->m_timer > m_pMovieChannel->m_duration - m_pMovieChannel->m_blendOutTime)
	{
		if (m_pMovieChannel->m_blendOutTime == 0.f)
			m_pMovieChannel->m_amplitudeRate = 0.f;
		else
			m_pMovieChannel->m_amplitudeRate = (m_pMovieChannel->m_duration - m_pMovieChannel->m_timer) / m_pMovieChannel->m_blendOutTime;
	}
	else
	{
		m_pMovieChannel->m_amplitudeRate = 1.f;
	}

	m_pMovieChannel->m_amplitudeRate *= m_pMovieChannel->m_distanceRate;

	AdvanceSinWave(&m_pMovieChannel->m_pitchWave, m_pMovieChannel);
	AdvanceSinWave(&m_pMovieChannel->m_yawWave, m_pMovieChannel);
	AdvanceSinWave(&m_pMovieChannel->m_rollWave, m_pMovieChannel);

	AdvanceSinWave(&m_pMovieChannel->m_xWave, m_pMovieChannel);
	AdvanceSinWave(&m_pMovieChannel->m_yWave, m_pMovieChannel);
	AdvanceSinWave(&m_pMovieChannel->m_zWave, m_pMovieChannel);
}

bool CCameraShake::IsShaking()
{
	if (m_shakeChannel[Player].m_timer < m_shakeChannel[Player].m_duration)
		return true;

	if (m_isMovieOn)
	{
		if (m_pMovieChannel->m_timer < m_pMovieChannel->m_duration)
			return true;
	}

	return false;
}

void CCameraShake::AdvanceSinWave(Wave* wave, ShakeChannel* channel)
{
	if (wave->amplitude == 0.f)
	{
		wave->point = 0.f;
		return;
	}

	_float sinFrequency = 2 * PI * wave->frequency;
	_float curTimeline = sinFrequency * (channel->m_timer + wave->offset);
	_float curAmplitude = wave->amplitude * channel->m_amplitudeRate;

	wave->point = sinf(curTimeline) * curAmplitude + (wave->ampAxisOffset * channel->m_amplitudeRate);
	if (sinf(curTimeline) < 0.f)
	{
		int a = 10;
	}
}
_float3 CCameraShake::GetRotateOscilation()
{
	_float3 rotOscilation = ZERO_VECTOR;
	for (auto channel : m_shakeChannel)
	{
		if (!channel.enable)
			continue;
		
		if (abs(rotOscilation.x) < abs(channel.m_pitchWave.point))
		{
			rotOscilation.x = channel.m_pitchWave.point;
		}

		if (abs(rotOscilation.y) < abs(channel.m_yawWave.point))
		{
			rotOscilation.y = channel.m_yawWave.point;
		}

		if (abs(rotOscilation.z) < abs(channel.m_rollWave.point))
		{
			rotOscilation.z = channel.m_rollWave.point;
		}
	}

	if (m_isMovieOn)
	{
		if (abs(rotOscilation.x) < abs(m_pMovieChannel->m_pitchWave.point))
		{
			rotOscilation.x = m_pMovieChannel->m_pitchWave.point;
		}

		if (abs(rotOscilation.y) < abs(m_pMovieChannel->m_yawWave.point))
		{
			rotOscilation.y = m_pMovieChannel->m_yawWave.point;
		}

		if (abs(rotOscilation.z) < abs(m_pMovieChannel->m_rollWave.point))
		{
			rotOscilation.z = m_pMovieChannel->m_rollWave.point;
		}
	}

	return rotOscilation;
}
_float3 CCameraShake::GetLocationOscilation()
{
	_float3 locOscilation = ZERO_VECTOR;
	for (auto channel : m_shakeChannel)
	{
		if (!channel.enable)
			continue;

		if (abs(locOscilation.x) < abs(channel.m_xWave.point))
		{
			locOscilation.x = channel.m_xWave.point;
		}

		if (abs(locOscilation.y) < abs(channel.m_yWave.point))
		{
			locOscilation.y = channel.m_yWave.point;
		}

		if (abs(locOscilation.z) < abs(channel.m_zWave.point))
		{
			locOscilation.z = channel.m_zWave.point;
		}
	}

	if (m_isMovieOn)
	{
		if (abs(locOscilation.x) < abs(m_pMovieChannel->m_xWave.point))
		{
			locOscilation.x = m_pMovieChannel->m_xWave.point;
		}

		if (abs(locOscilation.y) < abs(m_pMovieChannel->m_yWave.point))
		{
			locOscilation.y = m_pMovieChannel->m_yWave.point;
		}

		if (abs(locOscilation.z) < abs(m_pMovieChannel->m_zWave.point))
		{
			locOscilation.z = m_pMovieChannel->m_zWave.point;
		}
	}

	return locOscilation;
}
void CCameraShake::Preset_LowAttack(_float3 eventPos)
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(eventPos, channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.2f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.1f;

	ResetAllMember(channel);

	float randomOffset = 0.f;
	
	randomOffset = (rand() % 100) / 100.f;
	channel->m_xWave.amplitude = 0.03f;
	channel->m_xWave.frequency = 20.f;
	channel->m_xWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_yWave.amplitude = 0.03f;
	channel->m_yWave.frequency = 20.f;
	channel->m_yWave.offset = randomOffset;

	randomOffset = 0.f;
	channel->m_zWave.amplitude = 0.f;
	channel->m_zWave.frequency = 0.f;
	channel->m_zWave.offset = randomOffset;
}

void CCameraShake::Preset_HighAttack_Vert(_float3 eventPos)
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(eventPos, channel);
	
	channel->m_timer = 0.f;

	channel->m_duration = 0.2f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.1f;

	ResetAllMember(channel);

	float randomOffset = 0.f;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_xWave.amplitude = 0.04f;
	channel->m_xWave.frequency = 20.f;
	channel->m_xWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_yWave.amplitude = 0.04f;
	channel->m_yWave.frequency = 20.f;
	channel->m_yWave.offset = randomOffset;

	randomOffset = 0.f;
	channel->m_zWave.amplitude = 0.f;
	channel->m_zWave.frequency = 0.f;
	channel->m_zWave.offset = randomOffset;
}

void CCameraShake::Preset_HighAttack_Horz(_float3 eventPos)
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(eventPos, channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.2f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.1f;

	ResetAllMember(channel);

	float randomOffset = 0.f;
	
	randomOffset = (rand() % 100) / 100.f;
	channel->m_xWave.amplitude = 0.04f;
	channel->m_xWave.frequency = 20.f;
	channel->m_xWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_yWave.amplitude = 0.04f;
	channel->m_yWave.frequency = 20.f;
	channel->m_yWave.offset = randomOffset;

	randomOffset = 0.f;
	channel->m_zWave.amplitude = 0.f;
	channel->m_zWave.frequency = 0.f;
	channel->m_zWave.offset = randomOffset;
}

void CCameraShake::Preset_Land()
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(m_spCamera->GetTransform()->GetPosition(), channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.4f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.25f;

	ResetAllMember(channel);

	channel->m_zWave.amplitude = 0.05f;
	channel->m_zWave.frequency = 2.f;
	channel->m_zWave.offset = 0.3f / channel->m_zWave.frequency;
	channel->m_zWave.ampAxisOffset = channel->m_zWave.amplitude * sinf(0.3f * 2.f * PI);
}


void CCameraShake::Preset_Kiana_ForwardAttack()
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(m_spCamera->GetTransform()->GetPosition(), channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.2f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.1f;

	ResetAllMember(channel);

	float randomOffset = 0.f;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_xWave.amplitude = 0.03f;
	channel->m_xWave.frequency = 20.f;
	channel->m_xWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_yWave.amplitude = 0.03f;
	channel->m_yWave.frequency = 20.f;
	channel->m_yWave.offset = randomOffset;

	channel->m_zWave.amplitude = 0.03f;
	channel->m_zWave.frequency = 0.5f;
	channel->m_zWave.offset = 0.25f / channel->m_zWave.frequency;
	channel->m_zWave.ampAxisOffset = channel->m_zWave.amplitude;
}

void CCameraShake::Preset_Kiana_Claw5()
{
	 ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(m_spCamera->GetTransform()->GetPosition(), channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.3f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.2f;

	ResetAllMember(channel);

	float randomOffset = 0.f;

// 	randomOffset = (rand() % 100) / 100.f;
// 	channel->m_xWave.amplitude = 0.04f;
// 	channel->m_xWave.frequency = 20.f;
// 	channel->m_xWave.offset = randomOffset;
// 
// 	channel->m_yWave.amplitude = 0.15f;
// 	channel->m_yWave.frequency = 8.f;
// 	channel->m_yWave.offset = 0.25f / channel->m_yWave.frequency;
// 	channel->m_yWave.ampAxisOffset = channel->m_yWave.amplitude;
// 
// 	randomOffset = (rand() % 100) / 100.f;
// 	channel->m_zWave.amplitude = 0.04f;
// 	channel->m_zWave.frequency = 20.f;
// 	channel->m_zWave.offset = randomOffset;
}

void CCameraShake::Preset_Kiana_UltraActive()
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(m_spCamera->GetTransform()->GetPosition(), channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.25f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.15f;

	ResetAllMember(channel);

	
	channel->m_xWave.amplitude = 0.06f;
	channel->m_xWave.frequency = 30.f;
	channel->m_xWave.offset = 0.f;

	channel->m_yWave.amplitude = 0.15f;
	channel->m_yWave.frequency = 15.f;
	channel->m_yWave.offset = 0.f;
}

void CCameraShake::Preset_Theresa_Charge1Impact(_float3 eventPos)
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(eventPos, channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.3f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.2f;

	ResetAllMember(channel);

	float randomOffset = 0.f;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_xWave.amplitude = 0.04f;
	channel->m_xWave.frequency = 20.f;
	channel->m_xWave.offset = randomOffset;

	channel->m_yWave.amplitude = 0.2f;
	channel->m_yWave.frequency = 8.f;
	channel->m_yWave.offset = 0.25f / channel->m_yWave.frequency;
	channel->m_yWave.ampAxisOffset = channel->m_yWave.amplitude;
}

void CCameraShake::Preset_Theresa_Charge2Impact(_float3 eventPos)
{
	 ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(eventPos, channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.3f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.15f;

	ResetAllMember(channel);

	float randomOffset = 0.f;

	channel->m_xWave.amplitude = 0.2f;
	channel->m_xWave.frequency = 8.f;
	channel->m_xWave.offset = 0.25f / channel->m_xWave.frequency;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_yWave.amplitude = 0.04f;
	channel->m_yWave.frequency = 20.f;
	channel->m_yWave.offset = randomOffset;
}

void CCameraShake::Preset_Theresa_CrossImpact(_float3 eventPos)
{
	 ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(eventPos, channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.4f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.3f;

	ResetAllMember(channel);

	float randomOffset = 0.f;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_xWave.amplitude = 0.02f;
	channel->m_xWave.frequency = 20.f;
	channel->m_xWave.offset = randomOffset;	

	channel->m_yWave.amplitude = 0.2f;
	channel->m_yWave.frequency = 10.f;
	channel->m_yWave.offset = 0.f;
	channel->m_yWave.ampAxisOffset = channel->m_yWave.amplitude;

}

void CCameraShake::Preset_Elevator()
{
	ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(m_spCamera->GetTransform()->GetPosition(), channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.3f;
	channel->m_blendInTime = 0.f;
	channel->m_blendOutTime = 0.2f;

	ResetAllMember(channel);

	channel->m_xWave.amplitude = 0.02f;
	channel->m_xWave.frequency = 20.f;

	channel->m_yWave.amplitude = 0.15f;
	channel->m_yWave.frequency = 10.f;
	channel->m_yWave.offset = 0.25f / channel->m_yWave.frequency;
	channel->m_yWave.ampAxisOffset = channel->m_yWave.amplitude;
}

void CCameraShake::Preset_Kiana_Run()
{
	ShakeChannel* channel = &m_shakeChannel[Monster];

	SetDistanceRate(m_spCamera->GetTransform()->GetPosition(), channel);
	channel->m_timer = 0.f;

	channel->m_duration = 10.f;
	channel->m_blendInTime = 0.5f;
	channel->m_blendOutTime = 0.5f;

	ResetAllMember(channel);

	channel->m_zWave.amplitude = 0.01f;
	channel->m_zWave.frequency = 10.f;
	channel->m_zWave.ampAxisOffset = channel->m_zWave.amplitude;
}

void CCameraShake::Preset_Boom(_float3 eventPos)
{
	 ShakeChannel* channel = &m_shakeChannel[Player];

	SetDistanceRate(eventPos, channel);
	channel->m_timer = 0.f;

	channel->m_duration = 0.25f;
	channel->m_blendInTime = 0.1f;
	channel->m_blendOutTime = 0.2f;

	float randomOffset = 0.f;
	randomOffset = (rand() % 100) / 100.f;
	channel->m_pitchWave.amplitude = D3DXToRadian(10.f);
	channel->m_pitchWave.frequency = 25.f;
	channel->m_pitchWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_yawWave.amplitude = D3DXToRadian(5.f);
	channel->m_yawWave.frequency = 25.f;
	channel->m_yawWave.offset = randomOffset;

	randomOffset = 0.f;
	channel->m_rollWave.amplitude = 0.f;
	channel->m_rollWave.frequency = 0.f;
	channel->m_rollWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_xWave.amplitude = 70.f;
	channel->m_xWave.frequency = 1.f;
	channel->m_xWave.offset = randomOffset;

	randomOffset = 0.f;
	channel->m_yWave.amplitude = 0.f;
	channel->m_yWave.frequency = 0.f;
	channel->m_yWave.offset = randomOffset;

	randomOffset = (rand() % 100) / 100.f;
	channel->m_zWave.amplitude = 70.f;
	channel->m_zWave.frequency = 25.f;
	channel->m_zWave.offset = randomOffset;

}


void CCameraShake::SetDistanceRate(_float3 eventPos, ShakeChannel* channel)
{
	_float3 camPos = m_spCamera->GetTransform()->GetPosition();
	_float3 dir = eventPos - camPos;
	_float len = D3DXVec3Length(&dir);

	if (len > m_outerRadius)
		channel->m_distanceRate = 0.f;
	else if (len > m_innerRadius)
		channel->m_distanceRate = 1.f - (len - m_innerRadius) / (m_outerRadius - m_innerRadius);
	else
		channel->m_distanceRate = 1.f;
}

void CCameraShake::ResetAllMember(ShakeChannel* channel)
{
	ResetRotMember(channel);
	ResetLocMember(channel);
}

void CCameraShake::ResetRotMember(ShakeChannel* channel)
{
	ResetWave(&channel->m_pitchWave);
	ResetWave(&channel->m_yawWave);
	ResetWave(&channel->m_rollWave);
}

void CCameraShake::ResetLocMember(ShakeChannel* channel)
{
	ResetWave(&channel->m_xWave);
	ResetWave(&channel->m_yWave);
	ResetWave(&channel->m_zWave);
}

void CCameraShake::ResetWave(Wave* wave)
{
	wave->point = 0.f;
	wave->amplitude = 0.f;
	wave->frequency = 0.f;
	wave->offset = 0.f;
	wave->ampAxisOffset = 0.f;
}
