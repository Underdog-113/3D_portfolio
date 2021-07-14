#pragma once

BEGIN(Engine)
class ENGINE_DLL CParticleSystem
{
private:
	struct ParticleDesc
	{
		_float posX, posY, posZ;
		_float red, green, blue;
		_float velocity;
		_bool  active;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR4 color;
	};
public:
	CParticleSystem();
	CParticleSystem(const CParticleSystem& rhs);
	~CParticleSystem();

	_bool Init(IDirect3DVertexBuffer9, std::wstring);

private:
	_float m_particleDeviationX, m_particleDeviationY, m_particleDeviationZ;
	_float m_particleVelocity, m_particleVelocityVariation;
	_float m_particleSize, m_particlesPerSecond;
	_int m_maxParticles;

	_int m_currentParticleCount;
	_float m_accumulatedTime;

	TextureClass* m_Texture;
	ParticleDesc* m_particleList;
	_int m_vertexCount, m_indexCount;
	VertexType* m_vertices;
	IDirect3DVertexBuffer9 *m_vertexBuffer, *m_indexBuffer;
};
END

