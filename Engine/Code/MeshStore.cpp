#include "EngineStdafx.h"
#include "MeshStore.h"
#include "DeviceManager.h"
#include "StaticMeshData.h"
#include "DynamicMeshData.h"


#include <fstream>
#include <algorithm>
#include <filesystem>

USING(Engine)

CMeshStore::_MeshMap CMeshStore::m_s_mStaticMeshData = {};
_uint CMeshStore::m_s_usage = 0;

CMeshStore::CMeshStore(void)
{
}

CMeshStore::~CMeshStore(void)
{
}

CMeshStore * CMeshStore::Create(void)
{
	CMeshStore* pInstance = new CMeshStore;
	pInstance->Awake();

	++m_s_usage;

	return pInstance;
}

void CMeshStore::Free(void)
{
	--m_s_usage;
	OnDestroy();
	delete this;
}

void CMeshStore::Awake(void)
{
	__super::Awake();
	m_fpResourceHandler = std::bind(&CMeshStore::ParsingMesh, this, std::placeholders::_1, std::placeholders::_2);
	m_resourcePath = L"..\\..\\Resource\\Mesh";
}


void CMeshStore::OnDestroy(void)
{
	for (auto& mesh : m_mCurSceneMeshData)
		mesh.second->Free();
	m_mCurSceneMeshData.clear();
	
	if (m_s_usage == 0)
	{
		for (auto& mesh : m_s_mStaticMeshData)
			mesh.second->Free();
		m_s_mStaticMeshData.clear();
	}
}

void CMeshStore::ClearCurResource(void)
{
	for (auto& mesh : m_mCurSceneMeshData)
		mesh.second->Free();
	m_mCurSceneMeshData.clear();
}

CMeshData* CMeshStore::GetMeshData(std::wstring meshKey)
{
	auto iter_find_static = m_s_mStaticMeshData.find(meshKey);
	if (iter_find_static != m_s_mStaticMeshData.end())
		return iter_find_static->second->MakeClone();

	auto iter_find_cur = m_mCurSceneMeshData.find(meshKey);
	if (iter_find_cur != m_mCurSceneMeshData.end())
		return iter_find_cur->second->MakeClone();

	MSG_BOX(__FILE__, L"meshKey is broken in GetMeshData");
	ABORT;

	return nullptr;
}

void CMeshStore::InitMeshForScene(std::wstring curScene, _bool isStatic)
{
	m_isStatic = isStatic;
	__super::InitResource(m_resourcePath + L"\\" + curScene);
}


void CMeshStore::ParsingMesh(std::wstring filePath, std::wstring fileName)
{
	std::wstring fullFilePath = filePath + fileName;
	
	if (filePath.find(L"\\Static\\") != std::wstring::npos)
	{	
		CStaticMeshData* pNewStaticMesh = CStaticMeshData::Create(filePath, fileName);
		if (m_isStatic)
			m_s_mStaticMeshData[pNewStaticMesh->GetMeshKey()] = pNewStaticMesh;
		else
			m_mCurSceneMeshData[pNewStaticMesh->GetMeshKey()] = pNewStaticMesh;
	}
	else// if (GetLastDirName(fullFilePath) == L"Dynamic")//Dynamic Mesh
	{
		CDynamicMeshData* pNewDynamicMesh = CDynamicMeshData::Create(filePath, fileName);
		if (m_isStatic)
			m_s_mStaticMeshData[pNewDynamicMesh->GetMeshKey()] = pNewDynamicMesh;
		else
			m_mCurSceneMeshData[pNewDynamicMesh->GetMeshKey()] = pNewDynamicMesh;
	}

}


