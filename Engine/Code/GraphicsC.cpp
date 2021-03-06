#include "EngineStdafx.h"
#include "GraphicsC.h"
#include "Scene.h"
#include "WndApp.h"
#include "DataStore.h"
#include "Object.h"
#include "MeshData.h"

USING(Engine)
CGraphicsC::CGraphicsC(void)
{
}

CGraphicsC::~CGraphicsC(void)
{
	OnDestroy();
}

SP(CComponent) CGraphicsC::MakeClone(CObject* pObject)
{
	SP(CGraphicsC) spClone(new CGraphicsC);
	CComponent::InitClone(spClone, pObject);
	spClone->m_renderID = m_renderID;

	return spClone;
}
void CGraphicsC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic = m_pOwner->GetIsStatic();
		_int dataID = m_pOwner->GetDataID();
		std::wstring objectKey = m_pOwner->GetObjectKey();
		CScene*	pOwnerScene = m_pOwner->GetScene();

		pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"renderID", m_renderID);
	}
}

void CGraphicsC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_spMesh = m_pOwner->GetComponent<CMeshC>();
	m_spTexture = m_pOwner->GetComponent<CTextureC>();
	m_spTransform = m_pOwner->GetComponent<CTransformC>();
	m_spRectTex = m_pOwner->GetComponent<CRectTexC>();
	m_spShader = m_pOwner->GetComponent<CShaderC>();

	if (m_spMesh != nullptr)
		GenerateBV();

	m_mtrl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_mtrl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f);
	m_mtrl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	m_mtrl.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	m_mtrl.Power = 0.f;
}

void CGraphicsC::FixedUpdate(SP(CComponent) spThis)
{
}

void CGraphicsC::Update(SP(CComponent) spThis)
{
}

void CGraphicsC::LateUpdate(SP(CComponent) spThis)
{
	SP(CGraphicsC) spGraphicC = std::dynamic_pointer_cast<CGraphicsC>(spThis);

	ADD_TO_RENDER_LIST(m_renderID, m_pOwner);
}

void CGraphicsC::OnDestroy(void)
{
}

void CGraphicsC::OnEnable(void)
{
	__super::OnEnable();
}

void CGraphicsC::AddMaterial(D3DMATERIAL9 mtrl, _int index)
{
	if (index == UNDEFINED)
		m_vMaterials.emplace_back(mtrl);
	else
		m_vMaterials[index] = mtrl;
}

void CGraphicsC::ResizeMaterial(_int size)
{
	m_vMaterials.resize(size);
}

D3DMATERIAL9 & CGraphicsC::GetMtrl(void)
{
	return m_mtrl;
}

void CGraphicsC::OnDisable(void)
{
	__super::OnDisable();

}

void CGraphicsC::GenerateBV(void)
{
	_float3 meshSize = m_spMesh->GetMeshSize();
	_float3 mySize = m_spTransform->GetSize();

	m_sizeBV.x = meshSize.x * mySize.x;
	m_sizeBV.y = meshSize.y * mySize.y;
	m_sizeBV.z = meshSize.z * mySize.z;


	m_offsetBV = (m_spMesh->GetMaxVertex() + m_spMesh->GetMinVertex()) / 2.f;
}


