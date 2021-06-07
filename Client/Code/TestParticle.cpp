#include "stdafx.h"
#include "..\Header\TestParticle.h"


CTestParticle::CTestParticle(Engine::BoundingBox* _boundingBox, _int _numParticles)
{
	m_boundingBox = *_boundingBox;
	m_fsize = 0.8f;
	m_dwvbSize = 2048;
	m_dwvbOffset = 0;
	m_dwvbBatchSize = 512;

	for (_int i = 0; i < _numParticles; ++i)
	{
		addParticle();
	}
}

void CTestParticle::resetParticle(Engine::ATTRIBUTE * _attribute)
{
	_attribute->_isAlive = true;

	// 파티클의 위치 지정을 위해 임의의 x, z 좌표를 얻는다.
	GetRandomVector(
		&_attribute->_position,
		&m_boundingBox._min,
		&m_boundingBox._max);

	// 높이 (y-좌표)는 항상 경계 상자의 최상단이 됨.
	_attribute->_position.y = m_boundingBox._max.y;
	_attribute->_velocity.x = GetRandomFloat(0.f, 1.f) * -3.f;
	_attribute->_velocity.y = GetRandomFloat(0.f, 1.f) * -10.f;
	_attribute->_velocity.z = 0.f;

	_attribute->_color = D3DCOLOR_XRGB(255, 255, 255);
}

void CTestParticle::Update()
{
	for (auto& iter : m_particles)
	{
		iter._position += iter._velocity * GET_DT * 50.f;

		if (!isPointInside(iter._position))
		{
			resetParticle(&iter);
		}
	}
}

SP(Engine::CObject) CTestParticle::MakeClone(void)
{
	return SP(CObject)();
}

void CTestParticle::Awake(void)
{
	__super::Awake();
}

void CTestParticle::Start(void)
{
	__super::Start();
}

void CTestParticle::FixedUpdate(void)
{
	__super::FixedUpdate();
}

void CTestParticle::LateUpdate(void)
{
	__super::LateUpdate();
}

void CTestParticle::OnDestroy(void)
{
	__super::OnDestroy();
}

void CTestParticle::OnEnable(void)
{
	__super::OnEnable();
}

void CTestParticle::OnDisable(void)
{
	__super::OnDisable();
}

void CTestParticle::SetBasicName(void)
{
}
