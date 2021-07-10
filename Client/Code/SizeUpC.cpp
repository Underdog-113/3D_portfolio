#include "Stdafx.h"
#include "SizeUpC.h"

CSizeUpC::CSizeUpC()
{
}

CSizeUpC::~CSizeUpC()
{
	OnDestroy();
}

SP(Engine::CComponent) CSizeUpC::MakeClone(Engine::CObject *pObject)
{
	SP(CSizeUpC) spClone(new CSizeUpC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CSizeUpC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CSizeUpC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CSizeUpC::FixedUpdate(SP(CComponent) spThis)
{

}

void CSizeUpC::Update(SP(CComponent) spThis)
{
	if (m_stopTime >= 0)
	{
		m_stopTime -= GET_DT;
		GetOwner()->GetComponent<Engine::CTransformC>()->SetSize(_float3(0, 0, 0));

		return;
	}

	if (GetOwner()->GetComponent<Engine::CTransformC>()->GetSize().x >= m_size)
	{
		GetOwner()->GetComponent<Engine::CTransformC>()->SetSize(_float3(0, 0, 0));
		GetOwner()->GetComponent<Engine::CTextureC>()->SetColor(_float4(1, 1, 1, 1));
	}
	GetOwner()->GetComponent<Engine::CTransformC>()->AddSizeX(+(GET_DT * m_speed));
	GetOwner()->GetComponent<Engine::CTransformC>()->AddSizeY(+(GET_DT * m_speed));
	
	//현재 사이즈와 사이즈의 비율을 구해서 알파로
	_float val = (GetOwner()->GetComponent<Engine::CTransformC>()->GetSize().x / m_size);
	_float a = 1 - (val *val);
	GetOwner()->GetComponent<Engine::CTextureC>()->SetColor(_float4(1, 1, 1, a));

}

void CSizeUpC::LateUpdate(SP(CComponent) spThis)
{

}

void CSizeUpC::OnDestroy()
{
}

void CSizeUpC::OnEnable()
{
	__super::OnEnable();
}

void CSizeUpC::OnDisable()
{
	__super::OnDisable();
}
