#include "stdafx.h"
#include "..\Header\MeshEffect_Client.h"


CMeshEffect_Client::CMeshEffect_Client()
{
}



void CMeshEffect_Client::Awake()
{
	__super::Awake();

	m_addExtra = true;
	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spGraphics = AddComponent<Engine::CGraphicsC>();
}

void CMeshEffect_Client::Start()
{
	__super::Start();
}

void CMeshEffect_Client::FixedUpdate()
{
	__super::FixedUpdate();
}

void CMeshEffect_Client::Update()
{
	__super::Update();
}

void CMeshEffect_Client::LateUpdate()
{
	__super::LateUpdate();
}


void CMeshEffect_Client::OnDestroy()
{
	__super::OnDestroy();
}

void CMeshEffect_Client::OnEnable()
{
	__super::OnEnable();
}

void CMeshEffect_Client::OnDisable()
{
	__super::OnDisable();
}
