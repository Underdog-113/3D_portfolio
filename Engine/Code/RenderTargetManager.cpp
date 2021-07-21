#include "EngineStdafx.h"
#include "RenderTargetManager.h"


USING(Engine)
IMPLEMENT_SINGLETON(CRenderTargetManager)

void CRenderTargetManager::Awake(void)
{
	__super::Awake();

	LPDIRECT3DDEVICE9	pDevice	= GET_DEVICE;
	D3DVIEWPORT9		viewport;
	_bool				succeed = true;

	pDevice->GetViewport(&viewport);

	//Add render targets
#pragma region BasicRT
	AddRenderTarget(L"Target_Albedo", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(0, 0);
	AddRenderTarget(L"Target_Normal", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(0, 1);
	AddRenderTarget(L"Target_Depth", viewport.Width, viewport.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(1, 1, 1, 1))->InitDebugRT(0, 2);
	//AddRenderTarget(L"Target_MtrlSpecular", viewport.Width, viewport.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(0, 0, 0, 0));
#pragma endregion

#pragma region LightRT
	AddRenderTarget(L"Target_Shade", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 1))->InitDebugRT(1, 0);
	AddRenderTarget(L"Target_Specular", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(1, 1);
	AddRenderTarget(L"Target_LightDepth", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(1, 2);
#pragma endregion


#pragma region BlurRT
	AddRenderTarget(L"Target_Emissive", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(2, 0);
	AddRenderTarget(L"Target_BlurDiv2_Ver", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	AddRenderTarget(L"Target_BlurDiv2_Fin", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	AddRenderTarget(L"Target_BlurDiv4_Ver", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	AddRenderTarget(L"Target_BlurDiv4_Fin", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(2, 1);
	AddRenderTarget(L"Target_BlurDiv8_Ver", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	AddRenderTarget(L"Target_BlurDiv8_Fin", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(2, 2);
	AddRenderTarget(L"Target_BlurDiv16_Ver", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	AddRenderTarget(L"Target_BlurDiv16_Fin", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))->InitDebugRT(2, 3);
#pragma endregion


#pragma region MaterialRT
	//AddRenderTarget(L"Material_Diffuse", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	//AddRenderTarget(L"Material_Ambient", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	//AddRenderTarget(L"Material_Specular", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	//AddRenderTarget(L"Material_Emissive", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
#pragma endregion

	m_vCurRenderTargets.resize(MAX_RENDER_TARGET_NUM, nullptr);
}

void CRenderTargetManager::Start(void)
{
	
}

void CRenderTargetManager::OnDestroy(void)
{
	for (auto& renderTarget : m_mRenderTarget)
		renderTarget.second->Free();

	m_mRenderTarget.clear();
}

void CRenderTargetManager::RenderDebugBuffer(void)
{
	for (auto& renderTarget : m_mRenderTarget)
	{
		if (renderTarget.second->GetIsDebugOn())
			renderTarget.second->RenderDebugBuffer();
	}
}

void CRenderTargetManager::SetRenderTargetTexture(LPD3DXEFFECT & pEffect, const _tchar* targetKey, const _char* contantTableKey)
{
	CRenderTarget* pRenderTarget = FindRenderTarget(targetKey);
	pRenderTarget->SetRenderTargetTexture(pEffect, contantTableKey);
}

//ReadyRenderTarget이었던 것
CRenderTarget* CRenderTargetManager::AddRenderTarget(const _tchar* targetKey, const _uint & width, const _uint & height, D3DFORMAT format, D3DXCOLOR color)
{
	CRenderTarget* pRenderTarget = FindRenderTarget(targetKey);
	if (pRenderTarget != nullptr)
	{
		MSG_BOX(__FILE__, L"RenderTarget is already in MRT Map");
		ABORT;
	}

	pRenderTarget = CRenderTarget::Create(width, height, format, color);
	m_mRenderTarget.emplace(targetKey, pRenderTarget);

	return pRenderTarget;
}

void CRenderTargetManager::ClearRenderTargets(void)
{
	for (auto& renderTarget : m_mRenderTarget)
		renderTarget.second->ClearRenderTarget();
}

void CRenderTargetManager::ReleaseCurRenderTargets(void)
{
	for (_int i = 0; i < MAX_RENDER_TARGET_NUM; ++i)
	{
		if (m_vCurRenderTargets[i])
		{
			m_vCurRenderTargets[i]->ReleaseOnDevice(i);
			m_vCurRenderTargets[i] = nullptr;
		}
	}
}

void CRenderTargetManager::SetUpRenderTarget(const _uint & index, CRenderTarget * pRenderTarget)
{
	if (m_vCurRenderTargets[index] != pRenderTarget)
	{
		if (m_vCurRenderTargets[index])
			m_vCurRenderTargets[index]->ReleaseOnDevice(index);

		m_vCurRenderTargets[index] = pRenderTarget;
		if (pRenderTarget == nullptr)
			return;
		else
			pRenderTarget->SetUpOnDevice(index);
	}
}

CRenderTarget * CRenderTargetManager::FindRenderTarget(const _tchar* targetKey)
{
	for (auto& renderTarget : m_mRenderTarget)
	{
		if (renderTarget.first == targetKey)
			return renderTarget.second;
	}

	return nullptr;
}