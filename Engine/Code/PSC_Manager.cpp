#include "EngineStdafx.h"
#include "..\Header\PSC_Manager.h"
#include "ParticleSystemC.h"

USING(Engine)
IMPLEMENT_SINGLETON(CPSC_Manager)


void CPSC_Manager::Awake()
{
	__super::Awake();
}

void CPSC_Manager::Start()
{
}

void CPSC_Manager::FixedUpdate()
{
}

void CPSC_Manager::Update()
{
}

void CPSC_Manager::LateUpdate()
{
}

void CPSC_Manager::PreRender(SP(CGraphicsC) spGC)
{
	if (m_vParticleCom.empty())
		return;

	for (auto& iter : m_vParticleCom)
	{
		iter->PreRender(spGC);
	}
	
}

void CPSC_Manager::Render(SP(CGraphicsC) spGC)
{
	if (m_vParticleCom.empty())
		return;

	for (auto& iter : m_vParticleCom)
	{
		iter->Render(spGC);
	}
}

void CPSC_Manager::PostRender(SP(CGraphicsC) spGC)
{
	if (m_vParticleCom.empty())
		return;

	for (auto& iter : m_vParticleCom)
	{
		iter->PostRender(spGC);
	}
}

void CPSC_Manager::OnDestroy()
{
	

	
}

void CPSC_Manager::OnEnable()
{
}

void CPSC_Manager::OnDisable()
{
}

_float CPSC_Manager::GetRandomFloat(_float _lowBound, _float _highBound)
{
	if (_lowBound >= _highBound) // bad input
		return _lowBound;

	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f;

	// return float in [lowBound, highBound] interval. 
	return (f * (_highBound - _lowBound)) + _lowBound;
}

void CPSC_Manager::GetRandomVector(_float3 * _Out, _float3 * _min, _float3 * _max)
{
	_Out->x = GetRandomFloat(_min->x, _max->x);
	_Out->y = GetRandomFloat(_min->y, _max->y);
	_Out->z = GetRandomFloat(_min->z, _max->z);
}
