#include "EngineStdafx.h"
#include "TransformC.h"
#include "Object.h"



USING(Engine)
CTransformC::CTransformC(void)
{
}

CTransformC::~CTransformC(void)
{
	OnDestroy();
}

SP(CComponent) CTransformC::MakeClone(CObject* pObject)
{
	SP(CTransformC) spClone(new CTransformC);
	__super::InitClone(spClone, pObject);

	spClone->SetPosition(m_position);
	spClone->SetRotation(m_rotation);
	spClone->SetSize(m_size);
	spClone->SetCheckCamDistance(m_checkCamDist);

	spClone->UpdateWorldMatrix();

	return spClone;
}

void CTransformC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
}

void CTransformC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);

	D3DXMatrixIdentity(&m_parentRotMatrix);
	//m_lastRotMatrix			= m_rotMatrix;
	//m_lastWorldMat			= m_worldMat;
	//m_lastWorldMatNoScale	= m_worldMatNoScale;
}

void CTransformC::FixedUpdate(SP(CComponent) spThis)
{
}

void CTransformC::Update(SP(CComponent) spThis)
{
	if (m_spParent && m_spParent->GetOwner() == nullptr)
	{
		_quat rotQuat;
		D3DXQuaternionRotationMatrix(&rotQuat, &m_rotMatrix);
		D3DXQuaternionNormalize(&rotQuat, &rotQuat);

		_float3 finalRotation = GET_MATH->QuatToRad(rotQuat);
		m_position = _float3(m_worldMatNoScale._41, m_worldMatNoScale._42, m_worldMatNoScale._43);
		SetRotation(finalRotation);
		m_spParent.reset();
	}
	Lerp();
	SlerpXZ();
}

void CTransformC::LateUpdate(SP(CComponent) spThis)
{
	UpdateWorldMatrix();
	
	if (m_checkCamDist)
		UpdateCamDistance();
}

void CTransformC::OnDestroy(void)
{
}

void CTransformC::OnEnable(void)
{
	__super::OnEnable();
}

void CTransformC::OnDisable(void)
{
	__super::OnDisable();
}

#pragma region TransformSettors
void CTransformC::SetPosition(_float3 position)
{
	m_position = position;
}

void CTransformC::SetPosition(_float posX, _float posY, _float posZ)
{
	m_position.x = posX;
	m_position.y = posY;
	m_position.z = posZ;
}

void CTransformC::SetPositionX(_float posX)
{
	m_position.x = posX;
}

void CTransformC::SetPositionY(_float posY)
{
	m_position.y = posY;
}

void CTransformC::SetPositionZ(_float posZ)
{
	m_position.z = posZ;
}

void CTransformC::SetRotation(_float3 rotation)
{
	m_rotation = rotation;
	UpdateForward();
}

void CTransformC::SetRotation(_float rotX, _float rotY, _float rotZ)
{
	m_rotation.x = rotX;
	m_rotation.y = rotY;
	m_rotation.z = rotZ;

	UpdateForward();
}

void CTransformC::SetRotationX(_float rotationX)
{
	m_rotation.x = rotationX;
	UpdateForward();
}

void CTransformC::SetRotationY(_float rotationY)
{
	m_rotation.y = rotationY;
	UpdateForward();
}

void CTransformC::SetRotationZ(_float rotationZ)
{
	m_rotation.z = rotationZ;
	UpdateForward();
}

void CTransformC::SetSize(_float3 size)
{
	m_size = size;
}

void CTransformC::SetSize(_float sizeX, _float sizeY, _float sizeZ)
{
	m_size.x = sizeX;
	m_size.y = sizeY;
	m_size.z = sizeZ;
}

void CTransformC::SetSizeX(_float sizeX)
{
	m_size.x = sizeX;
}

void CTransformC::SetSizeY(_float sizeY)
{
	m_size.y = sizeY;
}

void CTransformC::SetSizeZ(_float sizeZ)
{
	m_size.z = sizeZ;
}

void CTransformC::SetForward(_float3 forward)
{
	D3DXVec3Normalize(&forward, &forward);

	if (forward == m_forward)
		return;

	m_forward = forward;
	UpdateRotation();
}

void CTransformC::SetForwardUp(_float3 forward, _float3 up)
{
	D3DXVec3Normalize(&forward, &forward);
	D3DXVec3Normalize(&up, &up);

	if (abs(D3DXVec3Dot(&forward, &up)) > EPSILON)
		return;

	if (forward == m_forward && up == m_up)
		return;

	m_forward	= forward;
	m_up		= up;

	UpdateRotationWithUp();
}


void CTransformC::AddPosition(_float3 position)
{
	m_position += position;
}

void CTransformC::AddPositionX(_float adder)
{
	m_position.x += adder;
}

void CTransformC::AddPositionY(_float adder)
{
	m_position.y += adder;
}

void CTransformC::AddPositionZ(_float adder)
{
	m_position.z += adder;
}

void CTransformC::AddRotation(_float3 rotation)
{
	m_rotation += rotation;
	UpdateForward();
}

void CTransformC::AddRotationX(_float adder)
{
	m_rotation.x += adder;
	UpdateForward();
}

void CTransformC::AddRotationY(_float adder)
{
	m_rotation.y += adder;
	UpdateForward();
}

void CTransformC::AddRotationZ(_float adder)
{
	m_rotation.z += adder;
	UpdateForward();
}

void CTransformC::AddSize(_float3 size)
{
	m_size += size;
}

void CTransformC::AddSizeX(_float adder)
{
	m_size.x += adder;
}

void CTransformC::AddSizeY(_float adder)
{
	m_size.y += adder;
}

void CTransformC::AddSizeZ(_float adder)
{
	m_size.z += adder;
}
#pragma endregion

#pragma region Interface
void CTransformC::Lerp(void)
{
	if (m_lerpOn)
	{
		_float3 dir = m_goalPosition - m_position;
		_float length = D3DXVec3Length(&dir);
		_float moveAmount = length * m_lerpProportion;

		if (length < m_lerpSpeed * GET_DT)
		{
			m_position = m_goalPosition;
			m_lerpOn	= false;
			return;
		}
		else if (moveAmount < m_lerpSpeed)
			moveAmount = m_lerpSpeed;

		dir /= length;
		m_position += (dir * moveAmount * GET_DT);
	}
}

void CTransformC::SlerpXZ(void)
{
	if (m_slerpOn)
	{
		_float dotTwoForward = D3DXVec3Dot(&m_goalForward, &m_forward);
		dotTwoForward = GET_MATH->RoundOffRange(dotTwoForward, 1);

		_float includedAngle = acos(dotTwoForward);

		if (abs(includedAngle) < m_slerpSpeed * GET_DT)
		{
			SetForwardUp(m_goalForward, UP_VECTOR);
			m_goalForward	= ZERO_VECTOR;
			m_slerpOn		= false;
			return;
		}

		_float3 determinant;
		D3DXVec3Cross(&determinant, &m_forward, &m_goalForward);

		if (determinant.y < 0)
			AddRotationY(-m_slerpSpeed * GET_DT);
		else
			AddRotationY(m_slerpSpeed * GET_DT);
	}
}

void CTransformC::MoveForward(_float magnitude)
{
	AddPosition(m_forward * magnitude);
}

void CTransformC::MoveBackward(_float magnitude)
{
	AddPosition(-m_forward * magnitude);
}

void CTransformC::MoveLeft(_float magnitude)
{
	AddPosition(-m_right * magnitude);
}

void CTransformC::MoveRight(_float magnitude)
{
	AddPosition(m_right * magnitude);
}

void CTransformC::MoveUp(_float magnitude)
{
	AddPosition(m_up * magnitude);
}

void CTransformC::MoveDown(_float magnitude)
{
	AddPosition(-m_up * magnitude);
}

#pragma endregion

void CTransformC::UpdateForward(void)
{
	_mat rot;
	_float yaw, pitch, roll;
	yaw		= m_rotation.y;
	pitch	= m_rotation.x;
	roll	= m_rotation.z;

	D3DXMatrixRotationYawPitchRoll(&rot, yaw, pitch, roll);
	D3DXVec3TransformNormal(&m_forward, &FORWARD_VECTOR, &rot);
	D3DXVec3TransformNormal(&m_up, &UP_VECTOR, &rot);
	D3DXVec3TransformNormal(&m_right, &RIGHT_VECTOR, &rot);

	D3DXVec3Normalize(&m_forward, &m_forward);
	D3DXVec3Normalize(&m_up, &m_up);
	D3DXVec3Normalize(&m_right, &m_right);
}

void CTransformC::UpdateRotation(void)
{
	_float3 withoutY;
	_mat yRot;
	if (abs(m_forward.y) + EPSILON < 1.f)
	{
		withoutY = _float3(m_forward.x, 0.f, m_forward.z);
		D3DXVec3Normalize(&withoutY, &withoutY);
		_float dotCheck = D3DXVec3Dot(&withoutY, &FORWARD_VECTOR);
		dotCheck = GET_MATH->RoundOffRange(dotCheck, 1);

		_float yRotAngle = acosf(dotCheck);

		_float3 crossResult;
		D3DXVec3Cross(&crossResult, &FORWARD_VECTOR, &withoutY);

		if (crossResult.y < 0)
			yRotAngle *= -1;

		D3DXMatrixRotationAxis(&yRot, &UP_VECTOR, yRotAngle);

		D3DXVec3Cross(&m_right, &UP_VECTOR, &m_forward);
		dotCheck = D3DXVec3Dot(&withoutY, &m_forward);
		dotCheck = GET_MATH->RoundOffRange(dotCheck, 1);

		_float rightRotAngle = acosf(dotCheck);
		if (m_forward.y >= 0)
			rightRotAngle *= -1;

		_mat rightRot;
		D3DXMatrixRotationAxis(&rightRot, &m_right, rightRotAngle);

		_mat rotMatrix = yRot * rightRot;

		_quat rotQuat;
		D3DXQuaternionRotationMatrix(&rotQuat, &rotMatrix);
		D3DXQuaternionNormalize(&rotQuat, &rotQuat);


		m_rotation = GET_MATH->QuatToRad(rotQuat);
		if (abs(m_rotation.x) < EPSILON)
			m_rotation.x = 0;
		if (abs(m_rotation.z) < EPSILON)
			m_rotation.z = 0;
	}
	else
	{
		if (m_forward.y > 0)
			m_rotation = _float3(D3DXToRadian(90), 0, 0);
		else
			m_rotation = _float3(D3DXToRadian(-90), 0, 0);
	}
}

void CTransformC::UpdateRotationWithUp(void)
{
	D3DXVec3Cross(&m_right, &m_up, &m_forward);
	_mat rotMatrix;
	D3DXMatrixIdentity(&rotMatrix);
	rotMatrix._11 = m_right.x;		rotMatrix._12 = m_right.y;		rotMatrix._13 = m_right.z;
	rotMatrix._21 = m_up.x;			rotMatrix._22 = m_up.y;			rotMatrix._23 = m_up.z;
	rotMatrix._31 = m_forward.x;	rotMatrix._32 = m_forward.y;	rotMatrix._33 = m_forward.z;

	_quat rotQuat;
	D3DXQuaternionRotationMatrix(&rotQuat, &rotMatrix);
	D3DXQuaternionNormalize(&rotQuat, &rotQuat);


	m_rotation = GET_MATH->QuatToRad(rotQuat);
	if (abs(m_rotation.x) < EPSILON)
		m_rotation.x = 0;
	if (abs(m_rotation.z) < EPSILON)
		m_rotation.z = 0;
}


void CTransformC::UpdateWorldMatrix(void)
{
	//m_lastRotMatrix			= m_rotMatrix;
	//m_lastWorldMat			= m_worldMat;
	//m_lastWorldMatNoScale	= m_worldMatNoScale;

	_mat rotateX, rotateY, rotateZ, size, translation, result;

	D3DXMatrixRotationX(&rotateX, m_rotation.x);
	D3DXMatrixRotationY(&rotateY, m_rotation.y);
	D3DXMatrixRotationZ(&rotateZ, m_rotation.z);

    D3DXMatrixScaling(&size, m_size.x,
                             m_size.y,
                             m_size.z);

    D3DXMatrixTranslation(&translation, m_position.x,
                                        m_position.y,
                                        m_position.z);

	m_rotMatrix	= rotateX * rotateY * rotateZ;
	m_rotMatrix *= m_parentRotMatrix;

	m_worldMat = size * m_rotMatrix * translation;
	m_worldMatNoScale = m_rotMatrix * translation;

	

	if (m_spParent)
	{
		m_rotMatrix			*= m_spParent->GetRotMatrix();
		m_worldMatNoScale	*= m_spParent->GetWorldMatrixNoScale();
		m_worldMat			*= m_spParent->GetWorldMatrixNoScale();
	}
	//ApplyParentMatrix(&m_spParent->GetWorldMatrixNoScale());
	if (m_pParentMatrix)
	{
		m_worldMat *= *m_pParentMatrix;
	}
		
		//ApplyParentMatrix(m_pParentMatrix);
}

void CTransformC::UpdateCamDistance(void)
{
	_float3 camPos = GET_MAIN_CAM->GetTransform()->GetPosition();
	m_camDist = D3DXVec3LengthSq(&(camPos - m_position));
}

void CTransformC::ApplyParentMatrix(const _mat* pMat)
{
	m_worldMatNoScale	*= *pMat;
	//m_lastWorldMat		*= *pMat;

	_mat matToDecompose = m_worldMat;

	m_position = _float3(matToDecompose._41, matToDecompose._42, matToDecompose._43);
	matToDecompose._41 = 0; matToDecompose._42 = 0; matToDecompose._43 = 0;

	
	m_size.x = D3DXVec3Length(&_float3(matToDecompose._11, matToDecompose._12, matToDecompose._13));
	m_size.y = D3DXVec3Length(&_float3(matToDecompose._21, matToDecompose._22, matToDecompose._23));
	m_size.z = D3DXVec3Length(&_float3(matToDecompose._31, matToDecompose._32, matToDecompose._33));

	if (m_size.x != 0)
	{
		matToDecompose._11 /= m_size.x;
		matToDecompose._12 /= m_size.x;
		matToDecompose._13 /= m_size.x;
	}

	if (m_size.y != 0)
	{
		matToDecompose._21 /= m_size.y;
		matToDecompose._22 /= m_size.y;
		matToDecompose._23 /= m_size.y;
	}

	if (m_size.z != 0)
	{
		matToDecompose._31 /= m_size.z;
		matToDecompose._32 /= m_size.z;
		matToDecompose._33 /= m_size.z;
	}

	//m_lastRotMatrix *= matToDecompose;

	_quat rotQuat;
	D3DXQuaternionRotationMatrix(&rotQuat, &matToDecompose);
	D3DXQuaternionNormalize(&rotQuat, &rotQuat);

	m_rotation = GET_MATH->QuatToRad(rotQuat);
}

void CTransformC::SetWorldMatrix(_mat worldMat)
{
	m_worldMat = worldMat;
}

void CTransformC::SetLastWorldMatrix(_mat worldMat)
{
	//m_lastWorldMat = worldMat;
}
