#include "EngineStdafx.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Object.h"
#include "WndApp.h"



USING(Engine)
IMPLEMENT_SINGLETON(CCameraManager)

void CCameraManager::Awake(void)
{
	__super::Awake();
}

void CCameraManager::Start(void)
{
}

void CCameraManager::Update(void)
{	
	SetMainCameraMode();
}

void CCameraManager::LateUpdate(void)
{
	for (auto& iter = m_mCameras.begin(); iter != m_mCameras.end();)
	{
		if (iter->second == nullptr)
		{
			iter = m_mCameras.erase(iter);
		}
		else if (iter->second->GetDeleteThis())
		{
			iter->second.reset();
			iter = m_mCameras.erase(iter);
		}
		else
			++iter;
	}
}

void CCameraManager::OnDestroy(void)
{
	for (auto& camera : m_mCameras)
	{
		camera.second.reset();
	}

	m_mCameras.clear();
}

void CCameraManager::OnEnable(void)
{
}

void CCameraManager::OnDisable(void)
{
}

SP(CCamera) CCameraManager::AddCamera(const std::wstring & cameraKey, SP(CCamera) spCamera)
{
	m_mCameras.emplace(cameraKey, spCamera);

	return spCamera;
}

SP(CCamera) CCameraManager::GetCamera(const std::wstring & cameraKey)
{
	return m_mCameras[cameraKey];
}

void CCameraManager::DeleteCamera(const std::wstring & cameraKey)
{
	auto& it = m_mCameras.find(cameraKey);
	it->second.reset();
	m_mCameras.erase(it);
}

void CCameraManager::ChangeCameraKey(const std::wstring & cameraKey, const std::wstring & newKey)
{
	AddCamera(newKey, m_mCameras[cameraKey]);
	m_mCameras.erase(cameraKey);
}

void CCameraManager::DeleteMainCam(void)
{
	m_mCameras.clear();
	m_spMainCamera.reset();
}

void CCameraManager::SetMainCameraMode(void)
{
	if (IMKEY_PRESS(KEY_SHIFT) && IMKEY_DOWN(KEY_1))		
		ChangeCameraMode(ECameraMode::Fixed);
	else if (IMKEY_PRESS(KEY_SHIFT) && IMKEY_DOWN(KEY_2))
		ChangeCameraMode(ECameraMode::Free);
	else if (IMKEY_PRESS(KEY_SHIFT) && IMKEY_DOWN(KEY_3))
		ChangeCameraMode(ECameraMode::Edit);
	else if (IMKEY_PRESS(KEY_SHIFT) && IMKEY_DOWN(KEY_4))
		ChangeCameraMode(ECameraMode::FPS);
	else if (IMKEY_PRESS(KEY_SHIFT) && IMKEY_DOWN(KEY_5))
		ChangeCameraMode(ECameraMode::TPS);
	else if (IMKEY_PRESS(KEY_CONTROL) && IMKEY_DOWN(KEY_5))
		ChangeCameraMode(ECameraMode::TPS_Custom);
}

void CCameraManager::ChangeCameraMode(ECameraMode newCameraMode)
{
	switch (newCameraMode)
	{
	case ECameraMode::Fixed:
		ShowCursor(true);
		m_spMainCamera->GetTransform()->SetPosition(m_spMainCamera->GetFixedPos());
		m_spMainCamera->GetTransform()->SetForward(m_spMainCamera->GetFixedDir());
		m_spMainCamera->SetMode(ECameraMode::Fixed);
		m_spMainCamera->GetCollision()->SetIsEnabled(false);
		break;

	case ECameraMode::Free:
		ShowCursor(false);
		m_spMainCamera->SetMode(ECameraMode::Free);
		m_spMainCamera->GetCollision()->SetIsEnabled(false);
		break;

	case ECameraMode::Edit:
		ShowCursor(true);
		m_spMainCamera->SetMode(ECameraMode::Edit);
		m_spMainCamera->GetCollision()->SetIsEnabled(false);
		break;

	case ECameraMode::FPS:
		if (m_spMainCamera->GetTarget() == nullptr)
		{
			ChangeCameraMode(ECameraMode::Free);
			break;
		}

		ShowCursor(false);
		m_spMainCamera->SetMode(ECameraMode::FPS);
		m_spMainCamera->GetCollision()->SetIsEnabled(false);
		break;

	case ECameraMode::TPS:
		if (m_spMainCamera->GetTarget() == nullptr)
		{
			ChangeCameraMode(ECameraMode::Free);
			break;
		}

		ShowCursor(false);
		m_spMainCamera->SetMode(ECameraMode::TPS);
		m_spMainCamera->GetCollision()->SetIsEnabled(true);
		break;

	case ECameraMode::TPS_Custom:
		if (m_spMainCamera->GetTarget() == nullptr)
		{
			ChangeCameraMode(ECameraMode::Free);
			break;
		}

		ShowCursor(false);
		m_spMainCamera->SetMode(ECameraMode::TPS_Custom);
		m_spMainCamera->GetCollision()->SetIsEnabled(true);
		break;

	}
}
