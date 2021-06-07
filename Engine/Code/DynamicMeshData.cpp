#include "EngineStdafx.h"
#include "DynamicMeshData.h"
#include "StaticMeshData.h"
#include "DeviceManager.h"

USING(Engine)
CDynamicMeshData::CDynamicMeshData()
{
}


CDynamicMeshData::~CDynamicMeshData()
{
}

CMeshData * CDynamicMeshData::MakeClone(void)
{
	CDynamicMeshData* pClone = new CDynamicMeshData;

	pClone->m_pRootFrame		= m_pRootFrame;
	pClone->m_pHierarchyLoader	= m_pHierarchyLoader;
	pClone->m_pAniCtrl			= m_pAniCtrl->MakeClone();
	
	pClone->m_vMeshContainers	= m_vMeshContainers;
	pClone->m_meshType			= m_meshType;
	
	pClone->m_vTexList			= m_vTexList;
	pClone->m_vAniList			= m_vAniList;

	pClone->m_minVertex			= m_minVertex;
	pClone->m_maxVertex			= m_maxVertex;

	pClone->m_meshKey			= m_meshKey;

	return pClone;
}

void CDynamicMeshData::FreeClone(void)
{
	OnDestory();
}

void CDynamicMeshData::Awake(std::wstring const& filePath, std::wstring const& fileName)
{
	__super::Awake(filePath, fileName);
	
	m_meshType = (_int)EMeshType::Dynamic;

	m_pHierarchyLoader = CHierarchyLoader::Create(filePath, this);

	LPD3DXANIMATIONCONTROLLER pAniCtrl = nullptr;

	if (FAILED(D3DXLoadMeshHierarchyFromX((filePath + fileName).c_str(),
			   D3DXMESH_MANAGED,
			   GET_DEVICE,
			   m_pHierarchyLoader,
			   NULL,
			   &m_pRootFrame,
			   &pAniCtrl)))
	{
		MSG_BOX(__FILE__, L"Load Mesh Hierarchy failed in ParsingMesh");
		ABORT;
	}

	//할일 : 나중에 GET_VALUE로 읽어와야함.
	m_minVertex =  _float3(-100, -100, -100);
	m_maxVertex = _float3(100, 100, 100);

	m_meshSize = m_maxVertex - m_minVertex;



	m_pAniCtrl = CAniCtrl::Create(pAniCtrl); 
	m_pAniCtrl->ChangeAniSet(FindFirstAniIndex(fileName));

	LPD3DXANIMATIONCONTROLLER aniCtrl = m_pAniCtrl->GetAniCtrl();
	_uint numOfAni = aniCtrl->GetNumAnimationSets();
	LPD3DXANIMATIONSET pAS = NULL;
	for (_uint i = 0; i < numOfAni; ++i)
	{
		aniCtrl->GetAnimationSet(i, &pAS);
		m_vAniList.push_front(StrToWStr(pAS->GetName()));
	}

	((_DerivedD3DXFRAME*)m_pRootFrame)->pParentFrame = nullptr;
	UpdateFrame();
	SetFrameMatPointer((_DerivedD3DXFRAME*)m_pRootFrame);

}

void CDynamicMeshData::Update(void)
{
	if(m_playAnimation)
		m_pAniCtrl->Play();
}

void CDynamicMeshData::OnDestory(void)
{
	m_pAniCtrl->Free();
	delete this;
}

CDynamicMeshData * CDynamicMeshData::Create(std::wstring const & filePath, std::wstring const & fileName)
{
	CDynamicMeshData* pDynamicMesh = new CDynamicMeshData;
	pDynamicMesh->Awake(filePath, fileName);

	return pDynamicMesh;
}

void CDynamicMeshData::Free(void)
{
	m_pHierarchyLoader->DestroyFrame(m_pRootFrame);
	m_pHierarchyLoader->Free();
	OnDestory();
}

void CDynamicMeshData::UpdateFrame(void)
{
	_mat makeMeshLookAtMe;
	UpdateFrameMatrices((_DerivedD3DXFRAME*)m_pRootFrame,
						D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f)));

}

void CDynamicMeshData::ChangeAniSet(_uint index, _bool fixTillEnd, _double smoothTime, _float changeWeight)
{
	m_pAniCtrl->ChangeAniSet(index, fixTillEnd, smoothTime, changeWeight);
}

void CDynamicMeshData::ChangeAniSet(std::string name, _bool fixTillEnd, _double smoothTime, _float changeWeight)
{
	m_pAniCtrl->ChangeAniSet(name, fixTillEnd, smoothTime, changeWeight);
}

void CDynamicMeshData::PlayAnimation(void)
{
	m_pAniCtrl->Play();

	UpdateFrame();
}

_DerivedD3DXFRAME * CDynamicMeshData::GetFrameByName(std::string name)
{
	return (_DerivedD3DXFRAME*)D3DXFrameFind(m_pRootFrame, name.c_str());
}

_bool CDynamicMeshData::IsAnimationEnd(void)
{
	return m_pAniCtrl->IsItEnd();
}

void CDynamicMeshData::SetAniFixTillEnd(_bool isItFixed)
{
	m_pAniCtrl->SetFixTillEnd(isItFixed);
}

void CDynamicMeshData::UpdateFrameMatrices(_DerivedD3DXFRAME* pFrame, _mat* pParentMat)
{
	if (pFrame == nullptr)
		return;

	pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix * (*pParentMat);
	
	if (pFrame->pFrameSibling != nullptr)
	{
		UpdateFrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameSibling, pParentMat);
		((D3DXFRAME_DERIVED*)pFrame->pFrameSibling)->pParentFrame = pFrame->pParentFrame;
	}


	if (pFrame->pFrameFirstChild != nullptr)
	{
		UpdateFrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild, &pFrame->CombinedTransformMatrix);
		((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild)->pParentFrame = pFrame;
	}
		

}

void CDynamicMeshData::SetFrameMatPointer(_DerivedD3DXFRAME * pFrame)
{
	if (pFrame->pMeshContainer != nullptr)
	{
		_DerivedD3DXMESHCONTAINER*	pDerivedMeshContainer = (_DerivedD3DXMESHCONTAINER*)pFrame->pMeshContainer;

		for (_ulong i = 0; i < pDerivedMeshContainer->numBones; ++i)
		{
			std::string			pBoneName = pDerivedMeshContainer->pSkinInfo->GetBoneName(i);
			_DerivedD3DXFRAME* pFindFrame = (_DerivedD3DXFRAME*)D3DXFrameFind(m_pRootFrame, pBoneName.c_str());
			pDerivedMeshContainer->ppCombinedTransformMatrix[i] = &pFindFrame->CombinedTransformMatrix;


			pDerivedMeshContainer->pOriMesh;
		}

		m_vMeshContainers.push_back(pDerivedMeshContainer);
	}


	if (nullptr != pFrame->pFrameSibling)
		SetFrameMatPointer((D3DXFRAME_DERIVED*)pFrame->pFrameSibling);

	if (nullptr != pFrame->pFrameFirstChild)
		SetFrameMatPointer((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild);
}

_uint CDynamicMeshData::FindFirstAniIndex(std::wstring const & fileName)
{
	_size startPoint = fileName.find_first_of('.');
	_size endPoint = fileName.find_last_of('.');

	if (startPoint == endPoint)
		return 0;
	else
		return std::stoi(fileName.substr(++startPoint, endPoint - startPoint));
}
