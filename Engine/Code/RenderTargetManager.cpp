#include "EngineStdafx.h"
#include "RenderTargetManager.h"


USING(Engine)
IMPLEMENT_SINGLETON(CRenderTargetManager)

void CRenderTargetManager::Awake(void)
{
	__super::Awake();
	
}

void CRenderTargetManager::Start(void)
{
	LPDIRECT3DDEVICE9	pDevice	= GET_DEVICE;
	D3DVIEWPORT9		viewport;
	_bool				succeed = true;

	pDevice->GetViewport(&viewport);

	//Add render targets
#pragma region BasicRT
	AddRenderTarget(L"Target_Albedo", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	InitDebugBufferMRT(L"Target_Albedo", 0, 0, 256, 144);

	AddRenderTarget(L"Target_Normal", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	InitDebugBufferMRT(L"Target_Normal", 0, 144, 256, 144);
	
	AddRenderTarget(L"Target_Depth", viewport.Width, viewport.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(1, 1, 1, 1));
	InitDebugBufferMRT(L"Target_Depth", 0, 288, 256, 144);

	AddRenderTarget(L"Target_MtrlSpecular", viewport.Width, viewport.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(0, 0, 0, 0));
	InitDebugBufferMRT(L"Target_MtrlSpecular", 0, 432, 256, 144);

	InitMRT(L"MRT_Deferred", L"Target_Albedo");
	InitMRT(L"MRT_Deferred", L"Target_Normal");
	InitMRT(L"MRT_Deferred", L"Target_Depth");
	InitMRT(L"MRT_Deferred", L"Target_MtrlSpecular");
#pragma endregion

#pragma region LightRT
	AddRenderTarget(L"Target_Shade", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 1));
	InitDebugBufferMRT(L"Target_Shade", 256, 0, 256, 144);

	AddRenderTarget(L"Target_Specular", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	InitDebugBufferMRT(L"Target_Specular", 256, 144, 256, 144);

	InitMRT(L"MRT_LightAcc", L"Target_Shade");
	InitMRT(L"MRT_LightAcc", L"Target_Specular");	
#pragma endregion

#pragma region MaterialRT
	//AddRenderTarget(L"Material_Diffuse", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	//InitDebugBufferMRT(L"Material_Diffuse", 512, 0, 256, 144);
	//
	//AddRenderTarget(L"Material_Ambient", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	//InitDebugBufferMRT(L"Material_Diffuse", 512, 144, 256, 144);
	//
	//AddRenderTarget(L"Material_Specular", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	//InitDebugBufferMRT(L"Material_Specular", 512, 288, 256, 144);
	//
	//AddRenderTarget(L"Material_Emissive", viewport.Width, viewport.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0));
	//InitDebugBufferMRT(L"Material_Emissive", 512, 432, 256, 144);
	//
	//InitMRT(L"MRT_Mtrl", L"Material_Diffuse");
	//InitMRT(L"MRT_Material", L"Material_Ambient");
	//InitMRT(L"MRT_Mtrl", L"Material_Specular");
	//InitMRT(L"MRT_Mtrl", L"Material_Emissive");
#pragma endregion
}

void CRenderTargetManager::OnDestroy(void)
{
	for (auto& renderTarget : m_mRenderTarget)
		renderTarget.second->Free();

	m_mRenderTarget.clear();


	for (auto& mrt : m_mMRT)
		mrt.second.clear();

	m_mMRT.clear();
}

//ReadyMRT 였던 것
void CRenderTargetManager::InitMRT(const _tchar* mrtKey, const _tchar* targetKey)
{
	CRenderTarget* pRenderTarget = FindRenderTarget(targetKey);
	std::vector<CRenderTarget*>* pMultiRenderTarget = FindMRT(mrtKey);

	if (pMultiRenderTarget == nullptr)
	{
		std::vector<CRenderTarget*> vMRT;
		vMRT.push_back(pRenderTarget);
		m_mMRT.emplace(mrtKey, vMRT);
	}
	else
		pMultiRenderTarget->push_back(pRenderTarget);
}

void CRenderTargetManager::BeginMRT(const _tchar* mrtKey)
{
	std::vector<CRenderTarget*>* pMultiRenderTarget = FindMRT(mrtKey);

	for (auto& renderTarget : *pMultiRenderTarget)
		renderTarget->ClearRenderTarget();

	_uint index = 0;
	for (auto& renderTarget : *pMultiRenderTarget)
		renderTarget->SetUpOnDevice(index++);
}

void CRenderTargetManager::EndMRT(const _tchar* mrtKey)
{
	std::vector<CRenderTarget*>* pMultiRenderTarget = FindMRT(mrtKey);

	_uint index = 0;
	for (auto& renderTarget : *pMultiRenderTarget)
		renderTarget->ReleaseOnDevice(index++);
}

void CRenderTargetManager::InitDebugBufferMRT(const _tchar* targetKey, const _float & xPos, const _float & yPos, const _float & xSize, const _float & ySize)
{
	CRenderTarget* pRenderTarget = FindRenderTarget(targetKey);

	pRenderTarget->ReadyDebugBuffer(xPos, yPos, xSize, ySize);
}

void CRenderTargetManager::RenderDebugBufferMRT(const _tchar* mrtKey)
{
	std::vector<CRenderTarget*>* pMultiRenderTarget = FindMRT(mrtKey);

	for (auto& renderTarget : *pMultiRenderTarget)
		renderTarget->RenderDebugBuffer();
}

void CRenderTargetManager::SetRenderTargetTexture(LPD3DXEFFECT & pEffect, const _tchar* targetKey, const _char* contantTableKey)
{
	CRenderTarget* pRenderTarget = FindRenderTarget(targetKey);
	pRenderTarget->SetRenderTargetTexture(pEffect, contantTableKey);
}

//ReadyRenderTarget이었던 것
void CRenderTargetManager::AddRenderTarget(const _tchar* targetKey, const _uint & width, const _uint & height, D3DFORMAT format, D3DXCOLOR color)
{
	CRenderTarget* pRenderTarget = FindRenderTarget(targetKey);
	if (pRenderTarget != nullptr)
	{
		MSG_BOX(__FILE__, L"RenderTarget is already in MRT Map");
		ABORT;
	}

	pRenderTarget = CRenderTarget::Create(width, height, format, color);
	m_mRenderTarget.emplace(targetKey, pRenderTarget);
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

CRenderTargetManager::_MULTI_RENDER_TARGET * CRenderTargetManager::FindMRT(const _tchar* mrtKey)
{
	for (auto& mrt : m_mMRT)
	{
		if (mrt.first == mrtKey)
			return &mrt.second;
	}

	return nullptr;
}
