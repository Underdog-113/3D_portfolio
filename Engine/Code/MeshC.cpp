#include "EngineStdafx.h"
 
#include "MeshStore.h"
#include "DataStore.h"
#include "Object.h"

#include "StaticMeshData.h"
#include "DynamicMeshData.h"

USING(Engine)
CMeshC::CMeshC(void)
{
}


CMeshC::~CMeshC(void)
{
	OnDestroy();
}

SP(CComponent) CMeshC::MakeClone(CObject* pObject)
{
	SP(CMeshC) spClone(new CMeshC);
	__super::InitClone(spClone, pObject);

	for (auto& meshData : m_vMeshDatas)
		spClone->AddMeshData(meshData->MakeClone());

	spClone->m_minVertex	= m_minVertex;
	spClone->m_maxVertex	= m_maxVertex;
	spClone->m_meshSize		= m_meshSize;
	spClone->m_initTex		= m_initTex;

	return spClone;
}

void CMeshC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();
		CScene*	pOwnerScene		= m_pOwner->GetScene();

		_int numOfMeshData;
		pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"numOfMeshData", numOfMeshData);

		std::wstring meshKey;
		for (_int i = 0; i < numOfMeshData; ++i)
		{
			pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"meshKey" + std::to_wstring(i), meshKey);
			m_vMeshDatas.emplace_back(pOwnerScene->GetMeshStore()->GetMeshData(meshKey));
		}

		GenMinMaxVtx();
	}
}

void CMeshC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	for (_int i = 0; i < m_vMeshDatas.size(); ++i)
	{
		m_vMeshDatas[i]->Start();
		if (m_initTex)
		{
			SP(CTextureC) spOwnerTexC = m_pOwner->GetComponent<CTextureC>();
			for (_int j = 0; j < m_vMeshDatas[i]->GetTexList().size(); ++j)
				spOwnerTexC->AddTexture(RemoveExtension(m_vMeshDatas[i]->GetTexList()[j]), i);
		}
	}
}

void CMeshC::FixedUpdate(SP(CComponent) spThis)
{
}

void CMeshC::Update(SP(CComponent) spThis)
{
	for (auto& meshData : m_vMeshDatas)
		meshData->Update();
}

void CMeshC::LateUpdate(SP(CComponent) spThis)
{
}

void CMeshC::PreRender(SP(CGraphicsC) spGC)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetTransform(D3DTS_WORLD, &spGC->GetTransform()->GetLastWorldMatrix());
	pDevice->SetTransform(D3DTS_VIEW, &GET_MAIN_CAM->GetViewMatrix());
	pDevice->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetProjMatrix());
	pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, spGC->GetTexture()->GetColor());
	pDevice->SetMaterial(&spGC->m_mtrl);
}

void CMeshC::Render(SP(CGraphicsC) spGC)
{
	for (_size i = 0; i < m_vMeshDatas.size(); ++i)
	{
		if (m_vMeshDatas[i]->GetMeshType() == (_int)EMeshType::Static)
			RenderStatic(spGC, m_vMeshDatas[i], (_int)i);
		else
			RenderDynamic(spGC, m_vMeshDatas[i], (_int)i);
	}
}

void CMeshC::PostRender(SP(CGraphicsC) spGC)
{
}
   
void CMeshC::OnDestroy(void)
{
	for (auto& meshData : m_vMeshDatas)
		meshData->FreeClone();
}

void CMeshC::OnEnable(void)
{
	__super::OnEnable();
	
}

void CMeshC::OnDisable(void)
{
	__super::OnDisable();
	
}

void CMeshC::AddMeshData(CMeshData * pMeshData)
{
	m_vMeshDatas.emplace_back(pMeshData);
}

void CMeshC::AddMeshData(std::wstring meshKey)
{
	m_vMeshDatas.emplace_back(m_pOwner->GetScene()->GetMeshStore()->GetMeshData(meshKey));
}


void CMeshC::GenMinMaxVtx(void)
{
	m_minVertex = MAX_VECTOR;
	m_maxVertex = -MAX_VECTOR;

	for (auto& mesh : m_vMeshDatas)
	{
		_float3 minVtx = mesh->GetMinVertex();
		_float3 maxVtx = mesh->GetMaxVertex();

		if (minVtx.x < m_minVertex.x)
			m_minVertex.x = minVtx.x;
		if (minVtx.y < m_minVertex.y)
			m_minVertex.y = minVtx.y;
		if (minVtx.z < m_minVertex.z)
			m_minVertex.z = minVtx.z;

		if (maxVtx.x > m_maxVertex.x)
			m_maxVertex.x = maxVtx.x;
		if (maxVtx.y > m_maxVertex.y)
			m_maxVertex.y = maxVtx.y;
		if (maxVtx.z > m_maxVertex.z)
			m_maxVertex.z = maxVtx.z;
	}

	if(m_vMeshDatas.size() != 0)
		m_meshSize = m_maxVertex - m_minVertex;
}

void CMeshC::RenderStatic(SP(CGraphicsC) spGC, CMeshData * pMeshData, _int meshIndex)
{
	CStaticMeshData* pSM = dynamic_cast<CStaticMeshData*>(pMeshData);

	for (_ulong i = 0; i < pSM->GetSubsetCount(); ++i)
	{
		_TexData* pTexData = spGC->GetTexture()->GetTexData()[meshIndex][i];

		if (pTexData != nullptr)
			GET_DEVICE->SetTexture(0, pTexData->pTexture);
		else
			GET_DEVICE->SetTexture(0, nullptr);

		pSM->GetMesh()->DrawSubset(i);
	}
}

void CMeshC::RenderDynamic(SP(CGraphicsC) spGC, CMeshData * pMeshData, _int meshIndex)
{
	CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(pMeshData);

	pDM->GetAniCtrl()->GetAniCtrl()->AdvanceTime(0, NULL);
	pDM->UpdateFrame();
	
	// root motion
	_mat makeMeshLookAtMe;
	D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f));
	_mat rootComb = pDM->GetRootFrame()->TransformationMatrix * makeMeshLookAtMe;
	_mat rootChildComb = pDM->GetRootFrame()->pFrameFirstChild->TransformationMatrix * rootComb;

	_float3 rootMotionPos = _float3(rootChildComb._41, rootChildComb._42, rootChildComb._43);
	// root motion

	for (auto& meshContainer : pDM->GetMeshContainers())
	{
		for (_ulong i = 0; i < meshContainer->numBones; ++i)
		{
			meshContainer->pRenderingMatrix[i] =
				meshContainer->pFrameOffsetMatrix[i] * (*meshContainer->ppCombinedTransformMatrix[i]);
		}

		void* pSrcVertex = nullptr;
		void* pDestVertex = nullptr;

		meshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVertex);
		meshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVertex);
		
		// root motion
		for (_ulong i = 0; i < meshContainer->numBones; ++i)
		{
			meshContainer->pRenderingMatrix[i]._41 -= rootMotionPos.x;
			meshContainer->pRenderingMatrix[i]._42 -= rootMotionPos.y;
			meshContainer->pRenderingMatrix[i]._43 -= rootMotionPos.z;
		}
		// root motion

		meshContainer->pSkinInfo->UpdateSkinnedMesh(meshContainer->pRenderingMatrix, NULL, pSrcVertex, pDestVertex);
		
		meshContainer->MeshData.pMesh->UnlockVertexBuffer();
		meshContainer->pOriMesh->UnlockVertexBuffer();


		const std::vector<std::vector<_TexData*>>& pTexData = spGC->GetTexture()->GetTexData();
		for (_ulong i = 0; i < meshContainer->NumMaterials; ++i)
		{
			if (pTexData[meshIndex][i] != nullptr)
				GET_DEVICE->SetTexture(0, pTexData[meshIndex][meshContainer->texIndexStart + i]->pTexture);
			else
				GET_DEVICE->SetTexture(0, nullptr);

			meshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}

	// root motion
	D3DXTRACK_DESC trackDesc;
	ZeroMemory(&trackDesc, sizeof(D3DXTRACK_DESC));
	pDM->GetAniCtrl()->GetAniCtrl()->GetTrackDesc(pDM->GetAniCtrl()->GetCurTrack(), &trackDesc);
	double timeline = trackDesc.Position / pDM->GetAniCtrl()->GetPeriod();
	int repeatCount = (int)timeline;
	timeline -= repeatCount;

	if (timeline < m_prevTimeLine)
	{
		m_prevRootMotionPos = _float3(0.f, 0.f, 0.f);
		m_prevTimeLine = 0.f;
	}

	_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;

	m_pOwner->GetTransform()->AddPosition(moveAmount);
	//m_pOwner->GetTransform()->SetPosition(rootMotionPos);
	m_prevRootMotionPos = rootMotionPos;
	m_prevTimeLine = timeline;
	// root motion
}
