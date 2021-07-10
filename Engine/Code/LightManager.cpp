#include "EngineStdafx.h"
#include "LightManager.h"
#include "CameraLight.h"


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

void CLightManager::Update(void)
{
	for (auto& light : m_vLights)
		light->UpdateLight();
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

void CLightManager::AddCameraLight(D3DLIGHT9 * pLightInfo)
{
	CLight* pLight = CCameraLight::Create(pLightInfo, (_int)m_vLights.size());

	m_vLights.push_back(pLight);
}

void CLightManager::RenderLights(LPD3DXEFFECT pEffect)
{
	m_globalAmbient = _float4(.5f, .5f, .5f, .5f);
	pEffect->SetVector("g_vGlobalAmbient", &m_globalAmbient);
	for (auto& light : m_vLights)
		light->RenderLight(pEffect);
}

void CLightManager::ClearLights(void)
{
	for (auto& light : m_vLights)
		light->Free();

	m_vLights.clear();
}
