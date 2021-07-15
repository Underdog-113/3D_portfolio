#include "EngineStdafx.h"
#include "CameraLight.h"

USING(Engine)
CCameraLight::CCameraLight()
{
}


CCameraLight::~CCameraLight()
{
}

CLight * CCameraLight::Create(D3DLIGHT9 * pLightInfo, const _int & index)
{
	CLight* pInstance = new CCameraLight;
	pInstance->InitLight(pLightInfo, index);

	return pInstance;
}

void CCameraLight::Free(void)
{
	__super::Free();
	
}

void CCameraLight::InitLight(D3DLIGHT9 * pLightInfo, const _int & index)
{
	__super::InitLight(pLightInfo, index);
	
}

void CCameraLight::UpdateLight(void)
{
	if (m_pLightInfo->Type == D3DLIGHT_POINT)
	{
		_float3 camPosition = GET_MAIN_CAM->GetTransform()->GetPosition();
		if (D3DXVec3LengthSq(&(camPosition + _float3(0, 0.5f, 0) - m_pLightInfo->Position)) > 1)
			m_timer += GET_DT;

		if (m_timer >= m_timeLimit)
		{

			_float3 dir = camPosition - m_pLightInfo->Position;
			_float length = D3DXVec3Length(&dir);
			_float moveAmount = length * 0.25f;

			if (length < 2 * GET_DT)
			{
				m_pLightInfo->Position = camPosition;
				m_timer = 0;
				return;
			}
			else if (moveAmount < 2)
				moveAmount = 2;

			dir /= length;
			m_pLightInfo->Position = (dir * moveAmount * GET_DT) + m_pLightInfo->Position;
		}
	}
	//else if (m_pLightInfo->Type == D3DLIGHT_DIRECTIONAL)
	//{
	//	m_pLightInfo->Direction = GET_MAIN_CAM->GetTransform()->GetForward();
	//	//_float3 camDirection = GET_MAIN_CAM->GetTransform()->GetForward();
	//	//_float3 lightGoalDir = camDirection;
	//	//lightGoalDir.y = 0;
	//	//D3DXVec3Normalize(&lightGoalDir, &lightGoalDir);
	//	//
	//	//_float3 curLightDir = m_pLightInfo->Direction;
	//	//curLightDir.y = 0;
	//	//
	//	//_float dotLight = D3DXVec3Dot(&curLightDir, &lightGoalDir);
	//	//dotLight = GET_MATH->RoundOffRange(dotLight, 1);
	//	//
	//	//_float includeAngle = acos(dotLight);
	//	//if (includeAngle > PI / 18)
	//	//	m_timer += GET_DT;
	//	//
	//	//if (m_timer >= m_timeLimit)
	//	//{
	//	//	if (abs(includeAngle) < PI / 36 * GET_DT)
	//	//	{
	//	//		m_pLightInfo->Direction = lightGoalDir;
	//	//		m_timer = 0;
	//	//		return;
	//	//	}
	//	//
	//	//
	//	//	_mat rotMat;
	//	//	_float3 determinant;
	//	//	D3DXVec3Cross(&determinant, &curLightDir, &lightGoalDir);
	//	//	if (determinant.y < 0)
	//	//		D3DXMatrixRotationAxis(&rotMat, &determinant, -PI / 36 * GET_DT);
	//	//	else
	//	//		D3DXMatrixRotationAxis(&rotMat, &determinant, PI / 36 * GET_DT);
	//	//
	//	//	D3DXVec3TransformNormal(&curLightDir, &curLightDir, &rotMat);
	//	//
	//	//	curLightDir.y = m_pLightInfo->Direction.y;
	//	//	D3DXVec3Normalize(&curLightDir, &curLightDir);
	//	//	m_pLightInfo->Direction = curLightDir;
	//	//}
	//}
}

void CCameraLight::RenderLight(LPD3DXEFFECT pEffect)
{
	__super::RenderLight(pEffect);
}
