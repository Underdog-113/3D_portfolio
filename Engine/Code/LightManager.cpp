#include "EngineStdafx.h"
#include "LightManager.h"



USING(Engine)
IMPLEMENT_SINGLETON(CLightManager)

void CLightManager::Awake(void)
{
	__super::Awake();
}
void CLightManager::Start(void)
{
}

void CLightManager::OnDestroy(void)
{
	for (auto& light : m_vLights)
		light->Free();

	m_vLights.clear();
}

void CLightManager::AddLight(const D3DLIGHT9 * pLightInfo)
{
	CLight* pLight = CLight::Create(pLightInfo, (_int)m_vLights.size());

	m_vLights.push_back(pLight);
}

void CLightManager::RenderLights(LPD3DXEFFECT & pEffect)
{
	for (auto& light : m_vLights)
		light->RenderLight(pEffect);
}
