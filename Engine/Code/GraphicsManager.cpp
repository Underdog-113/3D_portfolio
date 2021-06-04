#include "EngineStdafx.h"
 
 
#include "Scene.h"
#include "DeviceManager.h"
#include "Object.h"
 
#include "Frustum.h"
 
#include "Shader.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGraphicsManager)

void CGraphicsManager::Awake(void)
{
	__super::Awake();
}

void CGraphicsManager::Start(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	light.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	light.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	light.Direction = _float3(1.f, -1.f, 1.f);

	pDevice->SetLight(0, &light);
	pDevice->LightEnable(0, TRUE);



	//Get the alpha from the texture
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);
}

void CGraphicsManager::FixedUpdate(void)
{
}

void CGraphicsManager::Update(void)
{
}

void CGraphicsManager::LateUpdate(void)
{
	for (int i = 0; i < (_int)ERenderID::NumOfRenderID; ++i)
	{
		for (auto& it = m_vRenderList[i].begin(); it != m_vRenderList[i].end();)
		{
			if ((*it)->GetDeleteThis() == true)
				it = m_vRenderList[i].erase(it);
			else
				++it;
		}
	}
}

void CGraphicsManager::PreRender(void)
{
	GET_DEVICE->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 125, 125, 125),
		1.f, 0);

	GET_DEVICE->BeginScene();
}

void CGraphicsManager::Render(void)
{
	RenderBase();
	RenderNonAlpha();
	RenderWire();
	RenderAlphaTest();
	RenderAlphaBlend();
	RenderUI();

	ClearRenderList();
}

void CGraphicsManager::PostRender(void)
{
	GET_DEVICE->EndScene();
	GET_DEVICE->Present(NULL, NULL, NULL, NULL);
}

void CGraphicsManager::OnDestroy(void)
{
	for (_uint i = 0; i < (_uint)ERenderID::NumOfRenderID; ++i)
	{
		m_vRenderList[i].clear();
	}
}

void CGraphicsManager::OnEnable(void)
{
}

void CGraphicsManager::OnDisable(void)
{
}

void CGraphicsManager::AddToRenderList(_int renderID, CObject* pObject)
{
	if (pObject == nullptr)
	{
		MSG_BOX(__FILE__, L"Object is null in AddToRenderList");
		ABORT;
	}

	if (renderID >= (_int)ERenderID::NumOfRenderID || renderID < 0)
	{
		MSG_BOX(__FILE__, L"renderID is out of range in AddToRenderList");
		ABORT;
	}

	m_vRenderList[(_uint)renderID].push_back(pObject);
}

void CGraphicsManager::ClearRenderList(void)
{
	for (_int i = 0; i < (_int)ERenderID::NumOfRenderID; ++i)
		m_vRenderList[i].clear();
}

void CGraphicsManager::RenderBase(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& pObject : m_vRenderList[(_int)ERenderID::Base])
	{
		if (pObject->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
						  pObject->GetTransform()->GetSize() / 2.f))
			{
				pObject->PreRender();
				pObject->Render();
				pObject->PostRender();
			}
		}
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CGraphicsManager::RenderNonAlpha(void)
{
	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& pObject : m_vRenderList[(_int)ERenderID::NonAlpha])
	{
		if (pObject->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
						  pObject->GetTransform()->GetSize() / 2.f))
			{
				pObject->PreRender();
				pObject->Render();
				pObject->PostRender();
			}
		}
	}
}

void CGraphicsManager::RenderWire(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CShader* pShader = GET_SHADER((_int)EShaderType::Debug);
	for (auto& pObject : m_vRenderList[(_int)ERenderID::WireFrame])
	{
		if (pObject->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
					      pObject->GetTransform()->GetSize() / 2.f))
			{
				pObject->PreRender();
				pObject->Render();
				pObject->PostRender();
			}
		}
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CGraphicsManager::RenderAlphaTest(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 햇키드 얼굴 랜더링 할때 알파테스팅 해줘야됨
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1); // 알파 기준 설정
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 알파 테스팅 수행

	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& pObject : m_vRenderList[(_int)ERenderID::AlphaTest])
	{
		if (pObject->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
						  pObject->GetTransform()->GetSize() / 2.f))
			{
				pObject->PreRender();
				pObject->Render();
				pObject->PostRender();
			}
		}

	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void CGraphicsManager::RenderAlphaBlend(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	CShader* pShader = GET_SHADER((_int)EShaderType::Texture);
	for (auto& pObject : m_vRenderList[(_int)ERenderID::AlphaBlend])
	{
		if (pObject->GetIsEnabled())
		{
			//그래픽 컴포넌트를 주면
			//메쉬 컴포넌트가 가진 민맥스 버텍스 * 트랜스폼의 사이즈 + 포지션으로 컬링
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
						  pObject->GetTransform()->GetSize() / 2.f))
			{
				//
				pObject->PreRender();
				pObject->Render();
				pObject->PostRender();
			}
		}
	}
}

void CGraphicsManager::RenderUI(void)
{
	CShader* pShader = GET_SHADER((_int)EShaderType::UI);
	for (auto& pObject : m_vRenderList[(_int)ERenderID::UI])
	{
		if (pObject->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
						  pObject->GetTransform()->GetSize() / 2.f))
			{
				pObject->PreRender();
				pObject->Render();
				pObject->PostRender();
			}
		}
	}
	GET_DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
