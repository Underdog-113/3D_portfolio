#include "Stdafx.h"
#include "AlphaLifeTimeC.h"
#include "Object.h"

CAlphaLifeTimeC::CAlphaLifeTimeC()
{
}

CAlphaLifeTimeC::~CAlphaLifeTimeC()
{
	OnDestroy();
}

SP(Engine::CComponent) CAlphaLifeTimeC::MakeClone(Engine::CObject *pObject)
{
	SP(CAlphaLifeTimeC) spClone(new CAlphaLifeTimeC);
	__super::InitClone(spClone, pObject);

	return spClone;
}

void CAlphaLifeTimeC::Awake()
{
	__super::Awake();

	m_componentID = (_int)m_s_componentID;
}

void CAlphaLifeTimeC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
	m_canvas = static_cast<Engine::CCanvas*>(GetOwner());
	m_lifeTime = 0;
}

void CAlphaLifeTimeC::FixedUpdate(SP(CComponent) spThis)
{

}

void CAlphaLifeTimeC::Update(SP(CComponent) spThis)
{
	m_lifeTime -= GET_DT;

	if (m_lifeTime <= 0)
	{
		GetOwner()->SetIsEnabled(false);
	}
	else if (m_lifeTime <= 2)
	{
		// ±ôºýÀÌ°Ô ÇÏ±â
		for (auto& object : m_canvas->GetObjectList())
		{
			object->GetComponent<Engine::CTextureC>()->SetAlpha(0);
			/*if (object->GetComponent<Engine::CTextureC>()->GetColor().a == 1)
				object->GetComponent<Engine::CTextureC>()->SetColor(D3DXCOLOR(1, 1, 1, 0));
			else if (object->GetComponent<Engine::CTextureC>()->GetColor().a == 0)
				object->GetComponent<Engine::CTextureC>()->SetColor(D3DXCOLOR(1, 1, 1, 1));*/
		}
	}
}

void CAlphaLifeTimeC::LateUpdate(SP(CComponent) spThis)
{

}

void CAlphaLifeTimeC::OnDestroy()
{
}

void CAlphaLifeTimeC::OnEnable()
{
	__super::OnEnable();
}

void CAlphaLifeTimeC::OnDisable()
{
	__super::OnDisable();
}
