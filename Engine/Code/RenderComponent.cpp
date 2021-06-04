#include "EngineStdafx.h"
#include "RenderComponent.h"



USING(Engine)
CRenderComponent::CRenderComponent()
{
}


CRenderComponent::~CRenderComponent()
{
}

void CRenderComponent::Awake(void)
{
	__super::Awake();	
}

void CRenderComponent::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CRenderComponent::OnEnable(void)
{
	__super::OnEnable();
	
}

void CRenderComponent::OnDisable(void)
{
	__super::OnDisable();
	
}
