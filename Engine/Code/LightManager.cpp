#include "EngineStdafx.h"
#include "LightManager.h"



USING(Engine)

CLightManager::CLightManager(void)
{
}

CLightManager::~CLightManager(void)
{
}

CLightManager * CLightManager::Create(void)
{
	CLightManager* pInstance = new CLightManager;
	pInstance->Awake();

	return pInstance;
}

void CLightManager::Free(void)
{
	OnDestroy();
	delete this;
}

void CLightManager::Awake(void)
{
	__super::Awake();
}
void CLightManager::Start(void)
{
}

void CLightManager::OnDestroy(void)
{
	ClearLights();
}

void CLightManager::AddLight(D3DLIGHT9 * pLightInfo)
{
	CLight* pLight = CLight::Create(pLightInfo, (_int)m_vLights.size());

	m_vLights.push_back(pLight);
}

void CLightManager::RenderLights(LPD3DXEFFECT pEffect)
{
	for (auto& light : m_vLights)
		light->RenderLight(pEffect);
}

void CLightManager::ClearLights(void)
{
	for (auto& light : m_vLights)
		light->Free();

	m_vLights.clear();
}
