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

	spClone->m_vEffects = m_vEffects;

	return spClone;
}

void CShaderC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;

	if (m_pOwner->GetAddExtra() == false)
	{

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

void CShaderC::AddEffect(LPD3DXEFFECT pEffect)
{
	m_vEffects.emplace_back(pEffect);
}
