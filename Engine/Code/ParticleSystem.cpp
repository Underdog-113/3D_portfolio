#include "EngineStdafx.h"
#include "..\Header\ParticleSystem.h"

USING(Engine)

CParticleSystem::CParticleSystem()
{
}

CParticleSystem::~CParticleSystem()
{
	OnDestroy();

}

void CParticleSystem::Awake()
{
	m_pGraphicDevice = GET_DEVICE;

}

void CParticleSystem::Start()
{
}

void CParticleSystem::Update()
{
}

void CParticleSystem::PreRender(SP(CGraphicsC) spGC, IDirect3DVertexBuffer9 * pBuffer, IDirect3DBaseTexture9 * pTexture)
{
	m_pGraphicDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true); // Point sprite can be textured and resized.
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(m_size));
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.f));

	// �Ÿ��� ���� ��ƼŬ�� ũ�⸦ ����
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.f));
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.f));
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.f));

	m_pGraphicDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pGraphicDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	// �ؽ�ó�� ���ĸ� �̿�.
	m_pGraphicDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pGraphicDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pGraphicDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDevice->SetTexture(0, pTexture);
	m_pGraphicDevice->SetFVF(FVF_Particle);
	m_pGraphicDevice->SetStreamSource(0, pBuffer, 0, sizeof(PARTICLE_DESC));
}

void CParticleSystem::Render(SP(CGraphicsC) spGC, IDirect3DVertexBuffer9 * pBuffer)
{
	if (!m_AttributeList.empty())
	{
		// ���ؽ� ���۸� ��� ��� ó������ �����Ѵ�.
		if (m_dwvbOffset >= m_dwvbSize)
			m_dwvbOffset = 0;

		PARTICLE_DESC* v = 0;

		pBuffer->Lock(m_dwvbOffset * sizeof(PARTICLE_DESC),
			m_dwvbBatchSize * sizeof(PARTICLE_DESC),
			(void**)&v,
			m_dwvbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		for (auto iter : m_AttributeList)
		{
			if (iter._isAlive)
			{
				// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���� ���׸�Ʈ�� ����.
				v->_pos = iter._position;
				v->_color = (D3DXCOLOR)iter._color;
				v++;
				numParticlesInBatch++; // �ܰ� ī���� ����

				if (numParticlesInBatch == m_dwvbBatchSize)
				{
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ�� �׸�
					pBuffer->Unlock();

					m_pGraphicDevice->DrawPrimitive(
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

					pBuffer->Lock(
						m_dwvbOffset * sizeof(PARTICLE_DESC),
						m_dwvbBatchSize * sizeof(PARTICLE_DESC),
						(void**)&v,
						m_dwvbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // ���� �ܰ踦 ���� ����
				}
			}
		}

		pBuffer->Unlock();

		// (numParticlesInBatch == m_vbBatchSize) ������
		// �������� ���Ͽ� ������ �ܰ谡 ���������� �ʴ� ��찡
		// �߻��� �� �ִ�. �Ϻθ� ä���� �ܰ��
		// �̰����� �������� �ȴ�.

		if (numParticlesInBatch)
		{
			m_pGraphicDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				m_dwvbOffset,
				numParticlesInBatch);
		}

		// ���� ���
		m_dwvbOffset += m_dwvbBatchSize;

	}
}

void CParticleSystem::PostRender(SP(CGraphicsC) spGC)
{
	m_pGraphicDevice->SetRenderState(D3DRS_LIGHTING, true);
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	m_pGraphicDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//m_pGraphicDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void CParticleSystem::OnDestroy()
{
	if (!m_AttributeList.empty())
	{
		std::list<ATTRIBUTE>::iterator iter;
		for (iter = m_AttributeList.begin(); iter != m_AttributeList.end();)
		{
			iter = m_AttributeList.erase(iter);
		}
		m_AttributeList.clear();
	}

	m_pGraphicDevice = nullptr;

}

void CParticleSystem::reset()
{
	for (auto iter : m_AttributeList)
	{
		resetParticle(&iter);
	}
}

void CParticleSystem::resetParticle(ATTRIBUTE * _attribute)
{
	_attribute->_isAlive = true;

	CPSC_Manager::GetInstance()->GetRandomVector(
		&_attribute->_position,
		&m_boundingBox._min,
		&m_boundingBox._max);

	_attribute->_position.y = m_boundingBox._max.y;

	_attribute->_velocity.x = CPSC_Manager::GetInstance()->GetRandomFloat(0.0f, 1.0f) * -3.0f;
	_attribute->_velocity.y = CPSC_Manager::GetInstance()->GetRandomFloat(0.0f, 1.0f) * -10.0f;
	_attribute->_velocity.z = 0.0f;
}

void CParticleSystem::RemoveDeadParticles()
{
	std::list<ATTRIBUTE>::iterator iter;

	for (iter = m_AttributeList.begin(); iter != m_AttributeList.end();)
	{
		if (iter->_isAlive == false)
		{
			iter = m_AttributeList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void CParticleSystem::Add_ParticleAttribute()
{
	ATTRIBUTE attribute;

	resetParticle(&attribute);

	m_AttributeList.emplace_back(attribute);
	
}

_bool CParticleSystem::isPointInside(_float3 & p)
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
