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

	if(m_pMeshData)
		spClone->SetMeshData(m_pMeshData->MakeClone());

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
		if (numOfMeshData == 0)
			return;

		std::wstring meshKey;
		pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"meshKey0", meshKey);
		m_pMeshData = pOwnerScene->GetMeshStore()->GetMeshData(meshKey);

		GenMinMaxVtx();

		if (m_pMeshData && m_pMeshData->GetMeshType() == (_int)EMeshType::Dynamic)
		{
			m_pRootMotion = new CRootMotion;

			CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(m_pMeshData);
			m_pRootMotion->CreateFixOffsetArray(pDM->GetAniCtrl()->GetAniCtrl()->GetNumAnimationSets());
		}
	}

}

void CMeshC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	if (m_initTex)
	{
		SP(CTextureC) spOwnerTexC = m_pOwner->GetComponent<CTextureC>();
		for (_uint i = 0; i < m_pMeshData->GetSubsetCount(); ++i)
		{
			spOwnerTexC->AddTexture(RemoveExtension(m_pMeshData->GetTexList()[i]), i);
		}
	}
}

void CMeshC::FixedUpdate(SP(CComponent) spThis)
{
}

void CMeshC::Update(SP(CComponent) spThis)
{
	m_pMeshData->Update();
}

void CMeshC::LateUpdate(SP(CComponent) spThis)
{
}

void CMeshC::PreRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
}

void CMeshC::Render(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
	if (m_pMeshData->GetMeshType() == (_int)EMeshType::Static)
		RenderStatic(spGC, m_pMeshData, pEffect);
	else
		RenderDynamic(spGC, m_pMeshData, pEffect);
}

void CMeshC::PostRender(SP(CGraphicsC) spGC, LPD3DXEFFECT pEffect)
{
}

void CMeshC::OnDestroy(void)
{
	SAFE_DELETE(m_pRootMotion);

	if (m_pMeshData)
		m_pMeshData->FreeClone();
}

void CMeshC::OnEnable(void)
{
	__super::OnEnable();

}

void CMeshC::OnDisable(void)
{
	__super::OnDisable();

}

void CMeshC::SetMeshData(CMeshData * pMeshData)
{
	if (m_pMeshData)
	{
		m_pMeshData->FreeClone();
		if (m_pRootMotion)
		{
			delete m_pRootMotion;
			m_pRootMotion = nullptr;
		}
	}
	m_pMeshData = pMeshData;

	if (m_pMeshData && m_pMeshData->GetMeshType() == (_int)EMeshType::Dynamic)
	{
		m_pRootMotion = new CRootMotion;

		CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(m_pMeshData);
		m_pRootMotion->CreateFixOffsetArray(pDM->GetAniCtrl()->GetAniCtrl()->GetNumAnimationSets());
	}
}

void CMeshC::SetMeshData(std::wstring meshKey)
{
	if (m_pMeshData)
	{
		m_pMeshData->FreeClone();

		if (m_pRootMotion)
		{
			delete m_pRootMotion;
			m_pRootMotion = nullptr;
		}
	}
	m_pMeshData = m_pOwner->GetScene()->GetMeshStore()->GetMeshData(meshKey);

	if (m_pMeshData && m_pMeshData->GetMeshType() == (_int)EMeshType::Dynamic)
	{
		m_pRootMotion = new CRootMotion;

		CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(m_pMeshData);
		m_pRootMotion->CreateFixOffsetArray(pDM->GetAniCtrl()->GetAniCtrl()->GetNumAnimationSets());
	}
}

void CMeshC::GenMinMaxVtx(void)
{
	m_minVertex = MAX_VECTOR;
	m_maxVertex = -MAX_VECTOR;


	_float3 minVtx = m_pMeshData->GetMinVertex();
	_float3 maxVtx = m_pMeshData->GetMaxVertex();

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

void CMeshC::ApplyRootMotion(CDynamicMeshData* pDM)
{
	if (m_pRootMotion->GetIsRootMotion())
	{
		CAniCtrl* aniCtrl = pDM->GetAniCtrl();

		if (aniCtrl->GetIsFakeAniChange())
		{
			m_pRootMotion->RootMotionMove_WhileChange(m_pOwner, aniCtrl, pDM);
		}
		else
		{
			// Apply Root Motion
			m_pRootMotion->RootMotionMove(m_pOwner, aniCtrl, pDM);
		}
	}
}

//¿Ã∏ß
CStaticMeshData* CMeshC::GetFirstMeshData_Static(void)
{
	return static_cast<Engine::CStaticMeshData*>(m_pMeshData);
}

CDynamicMeshData* CMeshC::GetFirstMeshData_Dynamic(void)
{
	return static_cast<Engine::CDynamicMeshData*>(m_pMeshData);
}

void CMeshC::RenderStatic(SP(CGraphicsC) spGC, CMeshData * pMeshData, LPD3DXEFFECT pEffect)
{
	CStaticMeshData* pSM = dynamic_cast<CStaticMeshData*>(pMeshData);
	_uint pass = 0;

	for (_ulong i = 0; i < pSM->GetSubsetCount(); ++i)
	{
		if (spGC->GetTexture())
		{
			_TexData* pTexData = spGC->GetTexture()->GetTexData()[i][0];

			if (pTexData->includeAlpha)
				pass = 1;
			else
				pass = 0;

			pEffect->SetTexture("g_BaseTexture", pTexData->pTexture);
			pEffect->CommitChanges();
		}

		pEffect->BeginPass(pass);
		pSM->GetMesh()->DrawSubset(i);
		pEffect->EndPass();
	}
}


void CMeshC::RenderDynamic(SP(CGraphicsC) spGC, CMeshData * pMeshData, LPD3DXEFFECT pEffect)
{
	CDynamicMeshData* pDM = dynamic_cast<CDynamicMeshData*>(pMeshData);

	// root motion
	ApplyRootMotion(pDM);

	pDM->PlayAnimation();

	_mat makeMeshLookAtMe;
	D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f));
	_mat rootCombMat = pDM->GetRootFrame()->TransformationMatrix * makeMeshLookAtMe;
	_mat rootChildCombMat = pDM->GetRootFrame()->pFrameFirstChild->TransformationMatrix * rootCombMat;

	_float3 rootMotionMoveAmount = _float3(rootChildCombMat._41, 
										   rootChildCombMat._42,
										   rootChildCombMat._43);

	m_halfYOffset = rootChildCombMat._42 * m_pOwner->GetTransform()->GetSize().y;

	const std::vector<_DerivedD3DXMESHCONTAINER*>* pMeshContainers = &pDM->GetMeshContainers();
	for (_int i = 0; i < pMeshContainers->size(); ++i)
	{
		for (_ulong j = 0; j < (*pMeshContainers)[i]->numBones; ++j)
		{
			(*pMeshContainers)[i]->pRenderingMatrix[j] =
				(*pMeshContainers)[i]->pFrameOffsetMatrix[j] * (*(*pMeshContainers)[i]->ppCombinedTransformMatrix[j]);

			if (m_pRootMotion->GetIsRootMotion())
			{
				(*pMeshContainers)[i]->pRenderingMatrix[j]._41 -= rootMotionMoveAmount.x;
				(*pMeshContainers)[i]->pRenderingMatrix[j]._42 -= rootMotionMoveAmount.y;
				(*pMeshContainers)[i]->pRenderingMatrix[j]._42 += m_halfYOffset;
				(*pMeshContainers)[i]->pRenderingMatrix[j]._43 -= rootMotionMoveAmount.z;
			}
		}

		void* pSrcVertex = nullptr;
		void* pDestVertex = nullptr;

		(*pMeshContainers)[i]->pOriMesh->LockVertexBuffer(0, &pSrcVertex);
		(*pMeshContainers)[i]->MeshData.pMesh->LockVertexBuffer(0, &pDestVertex);

		(*pMeshContainers)[i]->pSkinInfo->UpdateSkinnedMesh((*pMeshContainers)[i]->pRenderingMatrix, NULL, pSrcVertex, pDestVertex);

		const std::vector<std::vector<_TexData*>>& pTexData = spGC->GetTexture()->GetTexData();
		_uint pass = 0;
		for (_ulong j = 0; j < (*pMeshContainers)[i]->NumMaterials; ++j)
		{
			if (pTexData[(*pMeshContainers)[i]->texIndexStart + j][0] != nullptr)
			{
				if (pTexData[(*pMeshContainers)[i]->texIndexStart + j][0]->includeAlpha)
					pass = 1;
				else
					pass = 0;

				if (!m_isEffectMesh)
				{
					if(FAILED(pEffect->SetTexture("g_BaseTexture", pTexData[(*pMeshContainers)[i]->texIndexStart + j][0]->pTexture)))
						int a = 5;
				}
			}
			else
			{
				pEffect->SetTexture("g_BaseTexture", nullptr);
			}
			pEffect->CommitChanges();

			pEffect->BeginPass(pass);
			GET_DEVICE->SetMaterial(&(*pMeshContainers)[i]->pMaterials[j].MatD3D);
			if(FAILED((*pMeshContainers)[i]->MeshData.pMesh->DrawSubset(j)))
				int a = 5;
			pEffect->EndPass();
		}

		(*pMeshContainers)[i]->MeshData.pMesh->UnlockVertexBuffer();
		(*pMeshContainers)[i]->pOriMesh->UnlockVertexBuffer();
	}

}
