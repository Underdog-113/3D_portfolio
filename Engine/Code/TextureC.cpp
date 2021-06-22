#include "EngineStdafx.h"
#include "TextureC.h"
#include "Object.h"
#include "MeshData.h"

USING(Engine)
CTextureC::CTextureC()
{
}


CTextureC::~CTextureC(void)
{
	OnDestroy();
}

SP(CComponent) CTextureC::MakeClone(CObject* pObject)
{
	SP(CTextureC) spClone(new CTextureC);
	__super::InitClone(spClone, pObject);

	spClone->m_vTexData = m_vTexData;
	spClone->m_color	= m_color;
//	spClone->m_changeTex = m_changeTex;

	return spClone;
}

void CTextureC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();
		CScene*	pOwnerScene		= m_pOwner->GetScene();

		_int numOfTexSet;
		pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"numOfTexSet", numOfTexSet);

		m_vTexData.resize(numOfTexSet);
		for (_int i = 0; i < numOfTexSet; ++i)
		{
			_int numOfTex;
			pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"numOfTex_" + std::to_wstring(i), numOfTex);
			m_numOfTex += numOfTex;
			for (_int j = 0; j < numOfTex; ++j)
			{
				std::wstring texKey = L"textureKey" + std::to_wstring(i) + L'_' + std::to_wstring(j);
				pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, texKey, texKey);
				m_vTexData[i].emplace_back(pOwnerScene->GetTextureStore()->GetTextureData(texKey));
			}
		}
	}
}


void CTextureC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CTextureC::FixedUpdate(SP(CComponent) spThis)
{
}

void CTextureC::Update(SP(CComponent) spThis)
{
}

void CTextureC::LateUpdate(SP(CComponent) spThis)
{
}



void CTextureC::OnDestroy(void)
{
}

void CTextureC::OnEnable(void)
{
	__super::OnEnable();

}

void CTextureC::OnDisable(void)
{
	__super::OnDisable();

}

void CTextureC::SetAlpha(_float alpha)
{
	m_color.w = alpha;
}

void CTextureC::AddAlpha(_float alpha)
{
	m_color.w += alpha;
}


void CTextureC::ResizeTexSet(_int numOfTexSet)
{
	m_vTexData.resize(numOfTexSet);
}

void CTextureC::AddTexture(std::wstring const & textureKey, _int setIndex)
{
	SP(CMeshC) spOwnerMeshC;
	if ((spOwnerMeshC = m_pOwner->GetComponent<CMeshC>()) != nullptr)
	{
		_size numOfSubset = spOwnerMeshC->GetMeshData()->GetSubsetCount();
		if (m_vTexData.size() != numOfSubset)
			m_vTexData.resize(numOfSubset);


		if (setIndex < 0 || setIndex >= numOfSubset)
		{
			MSG_BOX(__FILE__, L"index is broken in AddTexture");
			ABORT;
		}
	}
	else
	{
		if (m_vTexData.size() == 0)
			m_vTexData.resize(1);
	}

	++m_numOfTex;
	m_vTexData[setIndex].emplace_back(m_pOwner->GetScene()->GetTextureStore()->GetTextureData(textureKey));
}

void CTextureC::ChangeTexture(std::wstring const & textureKey, _int setIndex, _int texIndex)
{
	m_vTexData[setIndex][texIndex] = m_pOwner->GetScene()->GetTextureStore()->GetTextureData(textureKey);
}

void CTextureC::DeleteTexture(_int setIndex, _int texIndex)
{
	auto& iter_find = m_vTexData[setIndex].begin();
	m_vTexData[setIndex].erase(iter_find + texIndex);
	--m_numOfTex;
}
