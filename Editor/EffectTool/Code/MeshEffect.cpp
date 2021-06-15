#include "stdafx.h"
#include "..\Header\MeshEffect.h"


CMeshEffect::CMeshEffect()
{
}

void CMeshEffect::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CMeshEffect::Start()
{
	__super::Start();
}

void CMeshEffect::FixedUpdate()
{
	__super::FixedUpdate();
}

void CMeshEffect::Update()
{
	__super::Update();
}

void CMeshEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CMeshEffect::OnDestroy()
{
	__super::OnDestroy();
}

void CMeshEffect::OnEnable()
{
	__super::OnEnable();
}

void CMeshEffect::OnDisable()
{
	__super::OnDisable();
}