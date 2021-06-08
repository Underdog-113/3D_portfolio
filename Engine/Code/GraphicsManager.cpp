#include "EngineStdafx.h"
#include "Scene.h"
#include "Object.h"
#include "Frustum.h"


USING(Engine)
IMPLEMENT_SINGLETON(CGraphicsManager)

void CGraphicsManager::Awake(void)
{
	__super::Awake();

	InitDeferredBuffer();
}

void CGraphicsManager::Start(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	//D3DLIGHT9 light;
	//ZeroMemory(&light, sizeof(D3DLIGHT9));

	//light.Type = D3DLIGHT_DIRECTIONAL;
	//light.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	//light.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	//light.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	//light.Direction = _float3(1.f, -1.f, 1.f);
	//
	//pDevice->SetLight(0, &light);
	//pDevice->LightEnable(0, TRUE);



	////Get the alpha from the texture
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CONSTANT);



}

void CGraphicsManager::FixedUpdate(void)
{
}

void CGraphicsManager::Update(void)
{
	if (IMKEY_DOWN(KEY_Z))
	{
		m_rtDebugOn = (m_rtDebugOn ? false : true);
	}
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

	RenderDeferred();
	RenderLights();
	RenderDeferBlend();

	RenderWire();
	RenderAlphaTest();
	RenderAlphaBlend();
	RenderUI();

	if (m_rtDebugOn == true)
	{
		CRenderTargetManager::GetInstance()->RenderDebugBufferMRT(L"MRT_Deferred");
		CRenderTargetManager::GetInstance()->RenderDebugBufferMRT(L"MRT_LightAcc");
	}

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

void CGraphicsManager::InitDeferredBuffer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(_VertexScreen) * 4, 
										  0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										  FVF_SCR, 
										  D3DPOOL_MANAGED, 
										  &m_pVertexBuffer, 
										  NULL)))
	{
		MSG_BOX(__FILE__, L"Failed Creating VertexBuffer in CGraphicsManager::Awake()");
		ABORT;
	}

	if(FAILED(pDevice->CreateIndexBuffer(sizeof(INDEX16) * 2, 
										 0,// 정적 버퍼를 사용(d3dusage_dynamic 사용 시 동적 버퍼)
										 D3DFMT_INDEX16, 
										 D3DPOOL_MANAGED, 
										 &m_pIndexBuffer, 
										 NULL)))
	{
		MSG_BOX(__FILE__, L"Failed Creating IndexBuffer in CGraphicsManager::Awake()");
		ABORT;
	}

	D3DVIEWPORT9 viewport;
	pDevice->GetViewport(&viewport);

	_VertexScreen*		pVertex = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].position = _float4(0.f, 0.f, 0.f, 1.f);
	pVertex[0].texUV = _float2(0.f, 0.f);

	pVertex[1].position = _float4((_float)viewport.Width, 0.f, 0.f, 1.f);
	pVertex[1].texUV = _float2(1.f, 0.f);

	pVertex[2].position = _float4((_float)viewport.Width, (_float)viewport.Height, 0.f, 1.f);
	pVertex[2].texUV = _float2(1.f, 1.f);

	pVertex[3].position = _float4(0.f, (_float)viewport.Height, 0.f, 1.f);
	pVertex[3].texUV = _float2(0.f, 1.f);

	m_pVertexBuffer->Unlock();

	INDEX16*		pIndex = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIndexBuffer->Unlock();
}

void CGraphicsManager::RenderBase(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

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
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void CGraphicsManager::RenderDeferred(void)
{
	BEGIN_MRT(L"MRT_Deferred");
	RenderNonAlpha();
	END_MRT(L"MRT_Deferred");
}

void CGraphicsManager::RenderNonAlpha(void)
{
	for (auto& pObject : m_vRenderList[(_int)ERenderID::NonAlpha])
	{
		if (pObject->GetIsEnabled())
		{
			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
						  pObject->GetTransform()->GetSize() / 2.f))
			{
				SP(CComponent) spShader;
				if (spShader = pObject->GetComponent<CShaderC>())
				{
					const std::vector<CShader*>& vShader = std::dynamic_pointer_cast<CShaderC>(spShader)->GetShaders();

					for (_size i = 0; i < vShader.size(); ++i)
					{
						LPD3DXEFFECT pEffect = vShader[i]->GetEffect();
						vShader[i]->SetUpConstantTable(pObject->GetComponent<CGraphicsC>());

						_uint maxPass = 0;
						pEffect->Begin(&maxPass, 0);
						pObject->PreRender(pEffect);
						pObject->Render(pEffect);
						pObject->PostRender(pEffect);
						pEffect->End();
					}
				}
				else
				{
					pObject->PreRender();
					pObject->Render();
					pObject->PostRender();
				}
			}
		}
	}
}

void CGraphicsManager::RenderLights(void)
{
	BEGIN_MRT(L"MRT_LightAcc");

	LPD3DXEFFECT pEffect = GET_SHADER((_int)EShaderID::DeferredLightShader)->GetEffect();
	CRenderTargetManager::GetInstance()->SetRenderTargetTexture(pEffect, L"Target_Normal", "g_NormalTexture");
	CRenderTargetManager::GetInstance()->SetRenderTargetTexture(pEffect, L"Target_Depth", "g_DepthTexture");

	pEffect->Begin(NULL, 0);
	GET_CUR_SCENE->GetLightManager()->RenderLights(pEffect);
	pEffect->End();
	
	END_MRT(L"MRT_LightAcc");
}

void CGraphicsManager::RenderDeferBlend(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	LPD3DXEFFECT pEffect = GET_SHADER((_int)EShaderID::DeferredBlendShader)->GetEffect();
	CRenderTargetManager::GetInstance()->SetRenderTargetTexture(pEffect, L"Target_Albedo", "g_AlbedoTexture");
	CRenderTargetManager::GetInstance()->SetRenderTargetTexture(pEffect, L"Target_Shade", "g_ShadeTexture");
	CRenderTargetManager::GetInstance()->SetRenderTargetTexture(pEffect, L"Target_Specular", "g_SpeecularTexture");

	pEffect->Begin(NULL, 0);
	pEffect->BeginPass(0);

	pDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(_VertexScreen));
	pDevice->SetFVF(FVF_SCR);
	pDevice->SetIndices(m_pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	pEffect->EndPass();
	pEffect->End();
}

void CGraphicsManager::RenderWire(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 햇키드 얼굴 랜더링 할때 알파테스팅 해줘야됨
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 1); // 알파 기준 설정
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // 알파 테스팅 수행

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
}

void CGraphicsManager::RenderAlphaBlend(void)
{
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
	GET_DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
	std::sort(m_vRenderList[(_int)ERenderID::UI].begin(), m_vRenderList[(_int)ERenderID::UI].end(), 
			[](CObject* pObj1, CObject* pObj2)
			{
				return pObj1->GetTransform()->GetPosition().z > pObj2->GetTransform()->GetPosition().z;								
			});

	
	for (auto& pObject : m_vRenderList[(_int)ERenderID::UI])
	{
		if (pObject->GetIsEnabled())
		{
		
			GET_DEVICE->SetRenderState(D3DRS_STENCILENABLE, TRUE);
			GET_DEVICE->SetRenderState(D3DRS_STENCILREF, 0x1);
			GET_DEVICE->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

			if (GET_MAIN_CAM->GetFrustum()->
				CheckAabb(pObject->GetTransform()->GetPosition(),
						  pObject->GetTransform()->GetSize() / 2.f))
			{
				SP(CComponent) pShader;
				if (pShader = pObject->GetComponent<CShaderC>())
				{
					const std::vector<CShader*>& vShader = std::dynamic_pointer_cast<CShaderC>(pShader)->GetShaders();

					for (_size i = 0; i < vShader.size(); ++i)
					{
						LPD3DXEFFECT pEffect = vShader[i]->GetEffect();
						vShader[i]->SetUpConstantTable(pObject->GetComponent<CGraphicsC>());

						_uint maxPass = 0;
						pEffect->Begin(&maxPass, 0);
						pEffect->BeginPass(0);

						pObject->PreRender(pEffect);
						pObject->Render(pEffect);
						pObject->PostRender(pEffect);

						pEffect->EndPass();
						pEffect->End();
					}
				}
				else
				{
					pObject->PreRender();
					pObject->Render();
					pObject->PostRender();
				}
			}
		}
	}

	GET_DEVICE->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	GET_DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
	GET_DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
