#include "EngineStdafx.h"
#include "ShaderC.h"


USING(Engine)
CShaderC::CShaderC()
{
}


CShaderC::~CShaderC()
{
	OnDestroy();
}

SP(CComponent) CShaderC::MakeClone(CObject * pObject)
{
	SP(CShaderC) spClone(new CShaderC);
	__super::InitClone(spClone, pObject);

	spClone->m_vShaders = m_vShaders;

	return spClone;
}

void CShaderC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{
		_bool isStatic			= m_pOwner->GetIsStatic();
		_int dataID				= m_pOwner->GetDataID();
		std::wstring objectKey	= m_pOwner->GetObjectKey();
		CScene*	pOwnerScene		= m_pOwner->GetScene();

		_int numOfEffects;
		pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"numOfShaders", numOfEffects);

		for (_int i = 0; i < numOfEffects; ++i)
		{
			std::wstring shaderKey;
			pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"shaderKey" + std::to_wstring(i), shaderKey);
			_int shaderID = CShaderManager::GetInstance()->GetShaderID(shaderKey);
			m_vShaders.emplace_back(CShaderManager::GetInstance()->GetShader(shaderID));
		}
	}
}

void CShaderC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CShaderC::FixedUpdate(SP(CComponent) spThis)
{
}

void CShaderC::Update(SP(CComponent) spThis)
{
}

void CShaderC::LateUpdate(SP(CComponent) spThis)
{
}

void CShaderC::OnDestroy(void)
{
	m_vShaders.clear();
}

void CShaderC::OnEnable(void)
{
	__super::OnEnable();
	
}

void CShaderC::OnDisable(void)
{
	__super::OnDisable();
}

void CShaderC::AddShader(_int shaderID)
{
	m_vShaders.emplace_back(CShaderManager::GetInstance()->GetShader(shaderID));
}
