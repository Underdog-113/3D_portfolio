#include "EngineStdafx.h"
#include "..\Header\SmokeParticle.h"
#include "PSC_Manager.h"

USING(Engine)

SmokeParticle::SmokeParticle(BoundingBox * boundingBox, _uint numParticles)
{
	m_boundingBox = *boundingBox;
	m_size = 0.1f;
	m_dwvbSize = 2048;
	m_dwvbOffset = 0;
	m_dwvbBatchSize = 512;

	for (_uint i = 0; i < numParticles; ++i)
	{
		Add_ParticleAttribute();
	}
}

SmokeParticle::~SmokeParticle()
{
}

void SmokeParticle::resetParticle(ATTRIBUTE * _attribute)
{
	_attribute->_isAlive = true;

	CPSC_Manager::GetInstance()->GetRandomVector(
		&_attribute->_position,
		&m_boundingBox._min,
		&m_boundingBox._max);

	_attribute->_position.y = m_boundingBox._max.y;

	_attribute->_velocity.x = CPSC_Manager::GetInstance()->GetRandomFloat(0.f, 1.f) * -3.f;
	_attribute->_velocity.y = CPSC_Manager::GetInstance()->GetRandomFloat(0.f, 1.f) * -10.f;
	_attribute->_velocity.z = 0.f;
	
}

void SmokeParticle::Awake()
{
	__super::Awake();
}

void SmokeParticle::Start()
{
	__super::Start();

}

void SmokeParticle::Update()
{
	__super::Update();

	for (auto& iter : m_AttributeList)
	{
		iter._position += iter._velocity * GET_DT * 0.5f;

		if (isPointInside(iter._position) == false)
		{
			resetParticle(&(iter));
		}
	}
}
