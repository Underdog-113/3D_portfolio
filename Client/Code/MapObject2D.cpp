#include "stdafx.h"
#include "MapObject2D.h"


_uint CMapObject2D::m_s_uniqueID = 0;

CMapObject2D::CMapObject2D()
{
}


CMapObject2D::~CMapObject2D()
{
	OnDestroy();
}

SP(CMapObject2D) CMapObject2D::Create(_bool isStatic, Engine::CScene * pScene)
{
	SP(CMapObject2D) spInstance(new CMapObject2D, Engine::SmartDeleter<CMapObject2D>);
	spInstance->SetIsStatic(isStatic);
	spInstance->SetScene(pScene);
	spInstance->Awake();

	return spInstance;
}

SP(Engine::CObject) CMapObject2D::MakeClone(void)
{
	SP(CMapObject2D) spClone(new CMapObject2D, Engine::SmartDeleter<CMapObject2D>);
	__super::InitClone(spClone);

	spClone->m_spTransform	= spClone->GetComponent<Engine::CTransformC>();
	spClone->m_spRectTex	= spClone->GetComponent<Engine::CRectTexC>();
	spClone->m_spTexture	= spClone->GetComponent<Engine::CTextureC>();
	spClone->m_spGraphics	= spClone->GetComponent<Engine::CGraphicsC>();
	spClone->m_spCollision	= spClone->GetComponent<Engine::CCollisionC>();
	spClone->m_spShader		= spClone->GetComponent<Engine::CShaderC>();
	return spClone;
}

void CMapObject2D::Awake(void)
{
	__super::Awake();

	m_layerID = (_int)ELayerID::Map;
	m_dataID = UNDEFINED;

	m_addExtra = true;

	m_spRectTex		= AddComponent<Engine::CRectTexC>();
	m_spTexture		= AddComponent<Engine::CTextureC>();
	m_spGraphics	= AddComponent<Engine::CGraphicsC>();
	m_spCollision	= AddComponent<Engine::CCollisionC>();
	m_spShader		= AddComponent<Engine::CShaderC>();
}

void CMapObject2D::Start(void)
{
	__super::Start();

}

void CMapObject2D::FixedUpdate(void)
{
	__super::FixedUpdate();

}

void CMapObject2D::Update(void)
{
	__super::Update();

}

void CMapObject2D::LateUpdate(void)
{
	__super::LateUpdate();

}

void CMapObject2D::PreRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PreRender(m_spGraphics, pEffect);
}

void CMapObject2D::Render(LPD3DXEFFECT pEffect)
{
	m_spRectTex->Render(m_spGraphics, pEffect);
}

void CMapObject2D::PostRender(LPD3DXEFFECT pEffect)
{
	m_spRectTex->PostRender(m_spGraphics, pEffect);
}


void CMapObject2D::OnDestroy(void)
{
	__super::OnDestroy();

}

void CMapObject2D::OnEnable(void)
{
	__super::OnEnable();

}

void CMapObject2D::OnDisable(void)
{
	__super::OnDisable();

}

void CMapObject2D::SetBasicName(void)
{
	m_name = m_objectKey + std::to_wstring(m_s_uniqueID++);
}
