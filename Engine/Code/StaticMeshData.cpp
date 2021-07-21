#include "EngineStdafx.h"
#include "StaticMeshData.h"
#include "DeviceManager.h"

USING(Engine)
CStaticMeshData::CStaticMeshData()
{
}


CStaticMeshData::~CStaticMeshData()
{
}

CMeshData* CStaticMeshData::MakeClone(void)
{
	CStaticMeshData* pClone = new CStaticMeshData;
	pClone->m_pMesh			= m_pMesh;
	pClone->m_pAdjacency	= m_pAdjacency;
	pClone->m_pSubset		= m_pSubset;
	pClone->m_pMtrl			= m_pMtrl;
	pClone->m_subsetCount	= m_subsetCount;
	pClone->m_meshType		= m_meshType;
	pClone->m_vTexList		= m_vTexList;

	pClone->m_meshSize		= m_meshSize;
	pClone->m_minVertex		= m_minVertex;
	pClone->m_maxVertex		= m_maxVertex;

	pClone->m_meshKey		= m_meshKey;
	pClone->m_subsetCount	= m_subsetCount;
	return pClone;
}

void CStaticMeshData::FreeClone(void)
{
	OnDestory();
}

void CStaticMeshData::Awake(std::wstring const& filePath, std::wstring const& fileName)
{
	__super::Awake(filePath, fileName);
	
	m_meshType = (_int)EMeshType::Static;

	if (FAILED(D3DXLoadMeshFromX((filePath + fileName).c_str(),
								 D3DXMESH_32BIT | D3DXMESH_MANAGED,
								 GET_DEVICE,
								 &m_pAdjacency,
								 &m_pSubset,
								 NULL,
								 &m_subsetCount,
								 &m_pMesh)))
	{
		MSG_BOX(__FILE__, L"Load X-Mesh Failed in CStaticMash::Awake");
		ABORT;
	}
	
	
	
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE] =
	{
		{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0 },
		{ 0,24,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL,  0 },
		{ 0,36,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
		{ 0,48,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
		D3DDECL_END()
	};

	m_pMesh->CloneMesh(m_pMesh->GetOptions() | D3DXMESH_32BIT, decl, GET_DEVICE, &m_pMesh);
	
	LPDWORD pAdjacency = new DWORD[m_pMesh->GetNumFaces() * 3];
	m_pMesh->GenerateAdjacency(0.0001f, pAdjacency);

	_ubyte byOffset = 255;
	_ubyte tanOffset = 255;
	_ubyte biNormalOffset = 255;
	for (_ulong i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (decl[i].Usage == D3DDECLUSAGE_POSITION)
		{
			byOffset = (_ubyte)decl[i].Offset;
		}
		else if (decl[i].Usage == D3DDECLUSAGE_TANGENT)
		{
			tanOffset = (_ubyte)decl[i].Offset;
			D3DXComputeTangent(m_pMesh, 0, 0, 0, 0, pAdjacency);
		}
		else if (decl[i].Usage == D3DDECLUSAGE_BINORMAL)
		{
			biNormalOffset = (_ubyte)decl[i].Offset;
			D3DXComputeNormals(m_pMesh, pAdjacency);
		}

		if (byOffset != 255 && tanOffset != 255 && biNormalOffset != 255)
			break;
	}

	_uint stride	= D3DXGetDeclVertexSize(decl, 0);
	_uint numOfVtx	= m_pMesh->GetNumVertices();
	void* pVertices = nullptr;
	m_pMesh->LockVertexBuffer(0, &pVertices);
	for (_ulong i = 0; i < numOfVtx; ++i)
	{
		_float3 curPoint = *((_float3*)(((_ubyte*)pVertices) + (stride * i + byOffset)));
		if (curPoint.x > m_maxVertex.x)
			m_maxVertex.x = curPoint.x;
		if (curPoint.y > m_maxVertex.y)
			m_maxVertex.y = curPoint.y;
		if (curPoint.z > m_maxVertex.z)
			m_maxVertex.z = curPoint.z;

		if (curPoint.x < m_minVertex.x)
			m_minVertex.x = curPoint.x;
		if (curPoint.y < m_minVertex.y)
			m_minVertex.y = curPoint.y;
		if (curPoint.z < m_minVertex.z)
			m_minVertex.z = curPoint.z;	
	}
	m_pMesh->UnlockVertexBuffer();
	m_meshSize = m_maxVertex - m_minVertex;

	m_pMtrl = (D3DXMATERIAL*)m_pSubset->GetBufferPointer();
	
	for (_size i = 0; i < m_subsetCount; ++i)
	{
		if (m_pMtrl[i].pTextureFilename != nullptr)
			AddTexNameToList(StrToWStr(m_pMtrl[i].pTextureFilename));
		else
			AddTexNameToList(L"NoTex");
	}
}

void CStaticMeshData::Update(void)
{
}


void CStaticMeshData::OnDestory(void)
{
	delete this;
}

CStaticMeshData * CStaticMeshData::Create(std::wstring const & filePath, std::wstring const & fileName)
{
	CStaticMeshData* pStaticMesh = new CStaticMeshData;
	pStaticMesh->Awake(filePath, fileName);

	return pStaticMesh;
}

void CStaticMeshData::Free(void)
{
	m_pAdjacency->Release();
	m_pSubset->Release();
	m_pMesh->Release();
	OnDestory();
}
