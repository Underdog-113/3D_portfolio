#include "EngineStdafx.h"
#include "ShaderC.h"


USING(Engine)
CShaderC::CShaderC()
{
}


CShaderC::~CShaderC()
{
}

SP(CComponent) CShaderC::MakeClone(CObject * pObject)
{
	SP(CShaderC) spClone(new CShaderC);
	__super::InitClone(spClone, pObject);

	spClone->m_pEffects = m_pEffects;

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

		std::wstring shaderName;
		pOwnerScene->GET_VALUE(isStatic, dataID, objectKey, L"ShaderName", shaderName);

		m_pEffects = CShaderStore::GetInstance()->GetShader(GetShaderID(shaderName));
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
}

void CShaderC::OnEnable(void)
{
	__super::OnEnable();
	
}

void CShaderC::OnDisable(void)
{
	__super::OnDisable();
	
}

_int CShaderC::GetShaderID(std::wstring shaderName)
{
	if (shaderName == L"Basic")
		return (_int)EShaderID::Basic;
	else
	{
		MSG_BOX(__FILE__, L"Wrong shdaer name in GetShaderID");
		ABORT;
	}
}
