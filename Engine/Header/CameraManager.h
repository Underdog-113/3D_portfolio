#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Engine.h"
#include "Camera.h"
BEGIN(Engine)

class ENGINE_DLL CCameraManager final : public CEngine
{
	DECLARE_SINGLETON(CCameraManager)

public:
			void					Awake				(void) override;
			void					Start				(void);

			void					Update				(void);
			void					LateUpdate			(void);	

			void					OnDestroy			(void);

			void					OnEnable			(void);
			void					OnDisable			(void);

			SP(CCamera)				AddCamera			(const std::wstring& cameraKey, SP(CCamera) spCamera);
			SP(CCamera)				GetCamera			(const std::wstring& cameraKey);
			void					DeleteCamera		(const std::wstring& cameraKey);
			void					ChangeCameraKey		(const std::wstring& cameraKey, 
														 const std::wstring& newKey);

			void					DeleteMainCam		(void);

			void					ChangeCameraMode	(ECameraMode newCameraMode);
private:
			void					SetMainCameraMode	(void);

private:
	std::unordered_map<std::wstring, SP(CCamera)> m_mCameras;
	GETTOR_SETTOR	(SP(CCamera),	m_spMainCamera,		nullptr,		MainCamera)
	
};
END
#endif