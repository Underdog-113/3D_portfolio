#include "EngineStdafx.h"
#include "MeshC.h"
#include "Object.h"
#include "StaticMeshData.h"
#include "DynamicMeshData.h"
#include "RootMotion.h"
#include "AniCtrl.h"

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

void CMeshC::PreRenderWire(SP(CGraphicsC) spGC)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetTransform(D3DTS_WORLD, &spGC->GetTransform()->GetLastWorldMatrix());
	pDevice->SetTransform(D3DTS_VIEW, &GET_MAIN_CAM->GetViewMatrix());
	pDevice->SetTransform(D3DTS_PROJECTION, &GET_MAIN_CAM->GetProjMatrix());
	
	pDevice->SetMaterial(&spGC->m_mtrl);
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

void CMeshC::PreRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
}

void CMeshC::RenderWire(SP(CGraphicsC) spGC)
{
	for (_size i = 0; i < m_vMeshDatas.size(); ++i)
	{
		CStaticMeshData* pSM = dynamic_cast<CStaticMeshData*>(m_vMeshDatas[i]);
		for (_ulong j = 0; j < pSM->GetSubsetCount(); ++j)
		{
			pSM->GetMesh()->DrawSubset(j);
		}
	}
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

void CMeshC::Render(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	for (_size i = 0; i < m_vMeshDatas.size(); ++i)
	{
		if (m_vMeshDatas[i]->GetMeshType() == (_int)EMeshType::Static)
			RenderStatic(spGC, m_vMeshDatas[i], (_int)i, pEffect);
		else
			RenderDynamic(spGC, m_vMeshDatas[i], (_int)i, pEffect);
	}
}

void CMeshC::PostRenderWire(SP(CGraphicsC) spGC)
{
}

void CMeshC::PostRender(SP(CGraphicsC) spGC)
{
}

void CMeshC::PostRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
}

void CMeshC::OnDestroy(void)
{
	SAFE_DELETE(m_pRootMotion);

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
	
	if (!m_vMeshDatas.empty() && m_vMeshDatas[0]->GetMeshType() == (_int)EMeshType::Dynamic)
	{
		m_pRootMotion = new CRootMotion;

		CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(m_vMeshDatas[0]);
		m_pRootMotion->CreateFixOffsetArray(pDM->GetAniCtrl()->GetAniCtrl()->GetNumAnimationSets());
	}
}

void CMeshC::AddMeshData(std::wstring meshKey)
{
	m_vMeshDatas.emplace_back(m_pOwner->GetScene()->GetMeshStore()->GetMeshData(meshKey));

	if (!m_vMeshDatas.empty() && m_vMeshDatas[0]->GetMeshType() == (_int)EMeshType::Dynamic)
	{
		m_pRootMotion = new CRootMotion;

		CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(m_vMeshDatas[0]);
		m_pRootMotion->CreateFixOffsetArray(pDM->GetAniCtrl()->GetAniCtrl()->GetNumAnimationSets());
	}
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

void CMeshC::OnRootMotion(void)
{
	m_pRootMotion->SetIsRootMotion(true);
}

void CMeshC::OffRootMotion(void)
{
	m_pRootMotion->SetIsRootMotion(false);
}

void CMeshC::ApplyRootMotion(CDynamicMeshData* pDM, _float3 * rootMotionMoveAmount)
{
	if (m_pRootMotion->GetIsRootMotion())
	{
		CAniCtrl* aniCtrl = pDM->GetAniCtrl();

		aniCtrl->GetFakeAniCtrl()->AdvanceTime(0, NULL);
		pDM->UpdateFrame();

		// Get First Bone("Bip001"?) TransformCombinedMatrix
		_mat makeMeshLookAtMe;
		D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f));
		_mat rootCombMat = pDM->GetRootFrame()->TransformationMatrix * makeMeshLookAtMe;
		_mat rootChildCombMat = pDM->GetRootFrame()->pFrameFirstChild->TransformationMatrix * rootCombMat;

		*rootMotionMoveAmount = _float3(rootChildCombMat._41, rootChildCombMat._42, rootChildCombMat._43);

		// Set RootMotion Move Amount
		m_pRootMotion->SetRootMotionPos(*rootMotionMoveAmount);

		// Set Start Offset for Loop Animation
		if (aniCtrl->GetIsFakeAniStart())
			m_pRootMotion->SetRootMotionOffset(*rootMotionMoveAmount);

		// Apply Root Motion 
		m_pRootMotion->RootMotionMove(m_pOwner, aniCtrl);
	}
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

void CMeshC::RenderStatic(SP(CGraphicsC) spGC, CMeshData * pMeshData, _int meshIndex, LPD3DXEFFECT pEffect)
{
	CStaticMeshData* pSM = dynamic_cast<CStaticMeshData*>(pMeshData);
	_uint pass = 0;

	for (_ulong i = 0; i < pSM->GetSubsetCount(); ++i)
	{
		_TexData* pTexData = spGC->GetTexture()->GetTexData()[meshIndex][i];

		if (pTexData->includeAlpha)
			pass = 1;
		else
			pass = 0;

		pEffect->SetTexture("g_BaseTexture", pTexData->pTexture);
		pEffect->CommitChanges();

		pEffect->BeginPass(pass);
		pSM->GetMesh()->DrawSubset(i);
		pEffect->EndPass();
	}
}

void CMeshC::RenderDynamic(SP(CGraphicsC) spGC, CMeshData * pMeshData, _int meshIndex)
{
	CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(pMeshData);

	// root motion
	_float3 rootMotionMoveAmount = ZERO_VECTOR;
	ApplyRootMotion(pDM, &rootMotionMoveAmount);

	pDM->GetAniCtrl()->GetAniCtrl()->AdvanceTime(0, NULL);
	pDM->UpdateFrame();

	_mat makeMeshLookAtMe;
	D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f));
	_mat rootCombMat		= pDM->GetRootFrame()->TransformationMatrix * makeMeshLookAtMe;
	_mat rootChildCombMat	= pDM->GetRootFrame()->pFrameFirstChild->TransformationMatrix * rootCombMat;

	rootMotionMoveAmount	= _float3(rootChildCombMat._41, rootChildCombMat._42, rootChildCombMat._43);

	
	m_halfYOffset = rootChildCombMat._42 * m_pOwner->GetTransform()->GetSize().y;

	for (auto& meshContainer : pDM->GetMeshContainers())
	{
		for (_ulong i = 0; i < meshContainer->numBones; ++i)
		{
			meshContainer->pRenderingMatrix[i] =
				meshContainer->pFrameOffsetMatrix[i] * (*meshContainer->ppCombinedTransformMatrix[i]);

			meshContainer->pRenderingMatrix[i]._41 -= rootMotionMoveAmount.x;
			//meshContainer->pRenderingMatrix[i]._42 -= rootMotionMoveAmount.y;
			meshContainer->pRenderingMatrix[i]._43 -= rootMotionMoveAmount.z;
		}

		void* pSrcVertex = nullptr;
		void* pDestVertex = nullptr;

		meshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVertex);
		meshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVertex);

		meshContainer->pSkinInfo->UpdateSkinnedMesh(meshContainer->pRenderingMatrix, NULL, pSrcVertex, pDestVertex);


		const std::vector<std::vector<_TexData*>>& pTexData = spGC->GetTexture()->GetTexData();
		for (_ulong i = 0; i < meshContainer->NumMaterials; ++i)
		{
			if (pTexData[meshIndex][i] != nullptr)
				GET_DEVICE->SetTexture(0, pTexData[meshIndex][meshContainer->texIndexStart + i]->pTexture);
			else
				GET_DEVICE->SetTexture(0, nullptr);

			meshContainer->MeshData.pMesh->DrawSubset(i);
		}

		meshContainer->MeshData.pMesh->UnlockVertexBuffer();
		meshContainer->pOriMesh->UnlockVertexBuffer();
	}
}

void CMeshC::RenderDynamic(SP(CGraphicsC) spGC, CMeshData * pMeshData, _int meshIndex, LPD3DXEFFECT pEffect)
{
	CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(pMeshData);

	pDM->GetAniCtrl()->GetAniCtrl()->AdvanceTime(0, NULL);
	pDM->UpdateFrame();

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

		meshContainer->pSkinInfo->UpdateSkinnedMesh(meshContainer->pRenderingMatrix, NULL, pSrcVertex, pDestVertex);

		const std::vector<std::vector<_TexData*>>& pTexData = spGC->GetTexture()->GetTexData();
		_uint pass = 0;
		for (_ulong i = 0; i < meshContainer->NumMaterials; ++i)
		{
			if (pTexData[meshIndex][i] != nullptr)
			{
				if (pTexData[meshIndex][i]->includeAlpha)
					pass = 1;
				else
					pass = 0;

				pEffect->SetTexture("g_BaseTexture", pTexData[meshIndex][meshContainer->texIndexStart + i]->pTexture);

			}
			else
			{
				pEffect->SetTexture("g_BaseTexture", nullptr);
			}
			pEffect->CommitChanges();

			pEffect->BeginPass(pass);
			meshContainer->MeshData.pMesh->DrawSubset(i);
			pEffect->EndPass();
		}

		meshContainer->MeshData.pMesh->UnlockVertexBuffer();
		meshContainer->pOriMesh->UnlockVertexBuffer();
	}

}

