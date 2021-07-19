#include "EngineStdafx.h"
#include "FadeInOutC.h"
#include "Object.h"

USING(Engine)
CFadeInOutC::CFadeInOutC()
{
}


CFadeInOutC::~CFadeInOutC()
{
	OnDestroy();
}

SP(CComponent) CFadeInOutC::MakeClone(CObject * pObject)
{
	SP(CFadeInOutC) spClone(new CFadeInOutC);
	__super::InitClone(spClone, pObject);
	spClone->m_isFadeIn = m_isFadeIn;
	spClone->m_speed	= m_speed;
	

	return spClone;
}

void CFadeInOutC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;;
}

void CFadeInOutC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CFadeInOutC::FixedUpdate(SP(CComponent) spThis)
{
}

void CFadeInOutC::Update(SP(CComponent) spThis)
{
	if (!m_autoMode)
		return;

	SP(CTextureC) spOwnerGraphics = m_pOwner->GetComponent<CTextureC>();
	if (m_finish == false)
	{
		if (m_isFadeIn)
		{
			spOwnerGraphics->AddAlpha(0.016f / m_speed);

			if (spOwnerGraphics->GetColor().w >= 1.f)
			{
				spOwnerGraphics->SetAlpha(1.f);
				m_finish = true;
			}
		}
		else
		{
			spOwnerGraphics->AddAlpha(-0.016f / m_speed);

			if (spOwnerGraphics->GetColor().w <= 0.f)
			{
				spOwnerGraphics->SetAlpha(0.f);
				m_finish = true;
			}
		}
	}
	else if(m_autoDelete)
	{
		m_pOwner->SetDeleteThis(true);
	}
}

void CFadeInOutC::LateUpdate(SP(CComponent) spThis)
{
}

void CFadeInOutC::OnDestroy(void)
{
}

void CFadeInOutC::OnEnable(void)
{
	__super::OnEnable();
}

void CFadeInOutC::OnDisable(void)
{
	__super::OnDisable();
	
}

void CFadeInOutC::Setup(_bool isFadeIn, _float speed)
{
	m_isFadeIn = isFadeIn;
	m_speed = speed;
}

_float CFadeInOutC::GetCurrentAlpha()
{
	SP(CTextureC) spOwnerGraphics = m_pOwner->GetComponent<CTextureC>();
	return spOwnerGraphics->GetColor().w;
}

void CFadeInOutC::SetAlpha(_float alphaValue)
{
	if (alphaValue > 1.f)
		alphaValue = 1.f;
	else if (alphaValue < 0.f)
		alphaValue = 0.f;

	SP(CTextureC) spOwnerGraphics = m_pOwner->GetComponent<CTextureC>();
	spOwnerGraphics->SetAlpha(alphaValue);
}

void CFadeInOutC::AddAlpha(_float alphaValue)
{
	_float curAlpha = GetCurrentAlpha();
	alphaValue += curAlpha;

	if (alphaValue > 1.f)
		alphaValue = 1.f;
	else if (alphaValue < 0.f)
		alphaValue = 0.f;

	SP(CTextureC) spOwnerGraphics = m_pOwner->GetComponent<CTextureC>();
	spOwnerGraphics->SetAlpha(alphaValue);
}
