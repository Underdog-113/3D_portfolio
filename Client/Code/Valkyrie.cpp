#include "stdafx.h"
#include "..\Header\Valkyrie.h"


CValkyrie::CValkyrie()
{
}

void CValkyrie::Awake(void)
{
	__super::Awake();

	m_dataID = (_int)EDataID::Player;
	m_layerID = (_int)ELayerID::Player;

	m_spMesh = AddComponent<Engine::CMeshC>();
	m_spMesh->SetInitTex(true);

	m_spGraphics = AddComponent<Engine::CGraphicsC>();
	m_spShader = AddComponent<Engine::CShaderC>();
	m_spTexture = AddComponent<Engine::CTextureC>();
}


