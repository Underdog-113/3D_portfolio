#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"

BEGIN(Engine)
class CFrustum;
class ENGINE_DLL CCamera final : public CObject
{
	SMART_DELETER_REGISTER

private:
	explicit								CCamera				(void);
										   ~CCamera				(void);

public:
	static		SP(CCamera)					Create				(_bool isStatic, CScene* pScene);
				SP(CObject)					MakeClone			(void) override;

				void						Awake				(void) override;
				void						Start				(void) override;

				void						FixedUpdate			(void) override;
				void						Update				(void) override;
				void						LateUpdate			(void) override;

				void						OnDestroy			(void) override;

				void						OnEnable			(void) override;
				void						OnDisable			(void) override;

				void						SetBasicName		(void) override;

public:
				void						OnCollisionEnter	(_CollisionInfo ci);
				void						OnCollisionStay		(_CollisionInfo ci);
				void						OnCollisionExit		(_CollisionInfo ci);

public:
				void						SetNear				(_float nearPlane);
				void						SetFar				(_float farPlane);
				void						SetFOV				(_float FOV);

				_float2						WorldToScreenPoint	(_float3 worldPos);
private:
				void						UpdateFixed			(void);
				void						UpdateFree			(void);
				void						UpdateEdit			(void);
				void						UpdateFPS			(void);
				void						UpdateTPS			(void);
				void						UpdateTPS_Custom	(void);

				void						LateUpdateFixed		(void);
				void						LateUpdateFree		(void);
				void						LateUpdateEdit		(void);
				void						LateUpdateFPS		(void);
				void						LateUpdateTPS		(void);
				void						LateUpdateTPS_Custom(void);

				void						UpdateProjMat		(void);
				void						UpdateOrthoMat		(void);

				void						CameraRotate		(void);
				void						CameraMove			(void);
private:
	static			_uint					m_s_uniqueID;
	GETTOR			(SP(CCollisionC),		m_spCollision,		nullptr,				Collision)

	GETTOR			(CRayCollider*,			m_pCamRayCollider,	nullptr,				CamRayCollider)
	GETTOR			(CFrustum*,				m_pFrustum,			nullptr,				Frustum)
	GETTOR_SETTOR	(SP(CObject),			m_spTarget,			nullptr,				Target)

	GETTOR_SETTOR	(ECameraMode,			m_mode,				ECameraMode::Free,		Mode)

	GETTOR_SETTOR	(_bool,					m_hasChanged,		false,					HasChanged)
	GETTOR_SETTOR	(_bool,					m_projHasChanged,	true,					ProjHasChanged)
	GETTOR			(_bool,					m_wallCollided,		false,					WallCollided)
	GETTOR_SETTOR	(_bool,					m_isTargetOn,		false,					IsTargetOn)

	GETTOR_SETTOR	(_mat,					m_viewMat,			{},						ViewMatrix)
	GETTOR_SETTOR	(_mat,					m_projMat,			{},						ProjMatrix)
	GETTOR_SETTOR	(_mat,					m_orthoMat,			{},						OrthoMatrix)

	GETTOR			(_float,				m_near,				0.1f,					Near)
	GETTOR			(_float,				m_far,				1000.f,					Far)
	GETTOR			(_float,				m_FOV,				PI / 4,					FOV)

	GETTOR_SETTOR	(_float,				m_zoomSpeed,		300.f,					ZoomSpeed)
	GETTOR_SETTOR	(_float,				m_moveSpeed,		20.f,					MoveSpeed)

	//For Fixed Camera
	GETTOR_SETTOR	(_float3,				m_fixedPos,			ZERO_VECTOR,			FixedPos)
	GETTOR_SETTOR	(_float3,				m_fixedDir,			FORWARD_VECTOR,			FixedDir)
	GETTOR_SETTOR	(_float3,				m_targetPos,		ZERO_VECTOR,			TargetPos)

	//For TPS Camera
	GETTOR_SETTOR	(_float3,				m_targetOffset,		_float3(0, 0.5f, 0),	TargetOffset)
	GETTOR_SETTOR	(_float,				m_targetDist,		3.f,					TargetDist)
	GETTOR_SETTOR	(_float,				m_lookAngleRight,	PI/7.f,					LookAngleRight)
	GETTOR_SETTOR	(_float,				m_lookAngleUp,		0.f,					LookAngleUp)
	GETTOR_SETTOR	(_float,				m_awaySpeed,		1.f,					AwaySpeed)

	GETTOR_SETTOR	(_float,				m_minDistTPS,		1.f,					MinDistTPS)
	GETTOR_SETTOR	(_float,				m_maxDistTPS,		3.f,					MaxDistTPS)
	GETTOR_SETTOR	(_bool,					m_isRightClicked,	false,					RightClicked)


	POINT m_prevPT;
};
END
#endif
