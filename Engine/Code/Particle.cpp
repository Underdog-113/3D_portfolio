#include "EngineStdafx.h"
#include "..\Header\Particle.h"


USING(Engine)
CParticle::CParticle() :
	m_pD3DDevice(0)
	, m_pVIBuffer(0)
	, m_pTexture(0)
{
}

HRESULT CParticle::Init(LPDIRECT3DDEVICE9 _Device, std::wstring _texFIleName)
{
	m_pD3DDevice = _Device;

	HRESULT hr = 0;

	hr = _Device->CreateVertexBuffer(
		m_dwvbSize * sizeof(PARTICLE_DESC),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		FVF_Particle,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED �� D3DUSAGE_DYNAMIC�� �Բ� ���Ұ�.
		&m_pVIBuffer,
		0);

	if (FAILED(hr))
	{
		MSG_BOX(__FILE__, L"CreateVertexBuffer() - FAILED");
		ABORT;
		return E_FAIL;
	}

	hr = D3DXCreateTextureFromFile(
		_Device,
		_texFIleName.c_str(),
		&m_pTexture);

	if (FAILED(hr))
	{
		MSG_BOX(__FILE__, L"D3DXCreateTextureFromFile() - FAILED");
		ABORT;
		return E_FAIL;
	}

	return S_OK;
}

void CParticle::reset()
{
	for (auto iter : m_particles)
	{
		resetParticle(&iter);
	}
}

void CParticle::resetParticle(ATTRIBUTE * _attribute)
{
	_attribute->_isAlive = true;

	// get random x, z coordinate for the position of the snow flake.
	GetRandomVector(
		&_attribute->_position,
		&m_boundingBox._min,
		&m_boundingBox._max);

	// no randomness for height (y-coordinate).  Snow flake
	// always starts at the top of bounding box.
	_attribute->_position.y = m_boundingBox._max.y;

	// snow flakes fall downwards and slightly to the left
	_attribute->_velocity.x = GetRandomFloat(0.0f, 1.0f) * -3.0f;
	_attribute->_velocity.y = GetRandomFloat(0.0f, 1.0f) * -10.0f;
	_attribute->_velocity.z = 0.0f;

	// white snow flake
	_attribute->_color = D3DCOLOR_XRGB(255, 255, 255);
}

void CParticle::addParticle()
{
	ATTRIBUTE attribute;

	resetParticle(&attribute);

	m_particles.emplace_back(attribute);
}

void CParticle::Awake()
{
	__super::Awake();
	Init(GET_DEVICE, L"snowflake.dds");
}

void CParticle::Update()
{
	std::list<ATTRIBUTE>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->_position += i->_velocity * GET_DT * 50.f;

		if (isPointInside(i->_position) == false)
		{
			resetParticle(&(*i));
		}
	}
}

void CParticle::PreRender()
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(m_fsize));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.f));

	// �Ÿ��� ���� ��ƼŬ�� ũ�⸦ ����
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.f));

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

    // �ؽ�ó�� ���ĸ� �̿�.
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

void CParticle::Render()
{
	if (!m_particles.empty())
	{
		PreRender();
				
		m_pD3DDevice->SetTexture(0, m_pTexture);
		m_pD3DDevice->SetFVF(FVF_Particle);
		m_pD3DDevice->SetStreamSource(0, m_pVIBuffer, 0, sizeof(PARTICLE_DESC));

		// ���ؽ� ���۸� ��� ��� ó������ �����Ѵ�.
		if (m_dwvbOffset >= m_dwvbSize)
			m_dwvbOffset = 0;

		PARTICLE_DESC* v = 0;

		m_pVIBuffer->Lock(m_dwvbOffset * sizeof(PARTICLE_DESC),
			m_dwvbBatchSize * sizeof(PARTICLE_DESC),
			(void**)&v,
			m_dwvbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		for (auto iter : m_particles)
		{
			if (iter._isAlive)
			{
				// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���� ���׸�Ʈ�� ����.
				v->_pos = iter._position;
				v->_color = (D3DCOLOR)iter._color;
				v++;
				numParticlesInBatch++; // �ܰ� ī���� ����

				if (numParticlesInBatch == m_dwvbBatchSize)
				{
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ�� �׸�
					m_pVIBuffer->Unlock();

					m_pD3DDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						m_dwvbOffset,
						m_dwvbBatchSize);

					// �ܰ谡 �׷����� ���� ���� �ܰ踦 ��ƼŬ�� ä���.

					// ���� �ܰ��� ó�� ���������� �̵�.
					m_dwvbOffset += m_dwvbBatchSize;

					// ���ؽ� ������ ��踦 �Ѵ� �޸𸮷� �������� �������� ����.
					// ��踦 ���� ��� ó������ ����.
					if (m_dwvbOffset >= m_dwvbSize)
						m_dwvbOffset = 0;

					m_pVIBuffer->Lock(
						m_dwvbOffset * sizeof(PARTICLE_DESC),
						m_dwvbBatchSize * sizeof(PARTICLE_DESC),
						(void**)&v,
						m_dwvbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // ���� �ܰ踦 ���� ����
				}
			}
		}

		m_pVIBuffer->Unlock();

		// (numParticlesInBatch == m_vbBatchSize) ������
		// �������� ���Ͽ� ������ �ܰ谡 ���������� �ʴ� ��찡
		// �߻��� �� �ִ�. �Ϻθ� ä���� �ܰ��
		// �̰����� �������� �ȴ�.

		if (numParticlesInBatch)
		{
			m_pD3DDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				m_dwvbOffset,
				numParticlesInBatch);
		}

		// ���� ���
		m_dwvbOffset += m_dwvbBatchSize;

		PostRender();
	}
}

void CParticle::PostRender()
{
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

_bool CParticle::isEmpty()
{
	return m_particles.empty();
}

_bool CParticle::isDead()
{
	for (auto& iter : m_particles)
	{
		if (iter._isAlive)
			return false;
	}

	return true;
}

void CParticle::RemoveDeadParticles()
{
	std::list<ATTRIBUTE>::iterator iter;

	for (iter = m_particles.begin(); iter != m_particles.end();)
	{
		if (iter->_isAlive == false)
		{
			iter = m_particles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void CParticle::Release()
{
	std::list<ATTRIBUTE>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end();)
	{
		iter = m_particles.erase(iter);
	}
	m_particles.clear();

	SafeRelease(m_pVIBuffer);
	SafeRelease(m_pTexture);
	SafeRelease(m_pD3DDevice);
}

_float CParticle::GetRandomFloat(_float _lowBound, _float _highBound)
{
	if (_lowBound >= _highBound) // bad input
		return _lowBound;

	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f;

	// return float in [lowBound, highBound] interval. 
	return (f * (_highBound - _lowBound)) + _lowBound;
}

void CParticle::GetRandomVector(_float3 * _Out, _float3 * _min, _float3 * _max)
{
	_Out->x = GetRandomFloat(_min->x, _max->x);
	_Out->y = GetRandomFloat(_min->y, _max->y);
	_Out->z = GetRandomFloat(_min->z, _max->z);
}

_bool CParticle::isPointInside(_float3 & p)
{
	if (p.x >= m_boundingBox._min.x && p.y >= m_boundingBox._min.y && p.z >= m_boundingBox._min.z &&
		p.x <= m_boundingBox._max.x && p.y <= m_boundingBox._max.y && p.z <= m_boundingBox._max.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
