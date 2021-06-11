#include "EngineStdafx.h"
#include "RootMotion.h"

#include "AniCtrl.h"
#include "DynamicMeshData.h"

USING(Engine)

CRootMotion::CRootMotion()
{
}


CRootMotion::~CRootMotion()
{
	if (m_pIsFixRootMotionOffsets)
		delete[] m_pIsFixRootMotionOffsets;
}

void CRootMotion::RootMotionMove(CObject * pOwner, CAniCtrl * pAniCtrl, CDynamicMeshData* pDM)
{
	pAniCtrl->PlayFake();

	if (pAniCtrl->GetIsFakeAniEnd())
	{
		// 99% ?
		{
			pDM->UpdateFrame();
			_float3 rootMotionPos = GetRootMotionLocalPos(pDM);
			rootMotionPos = GetOwnerSizedPos(pOwner, rootMotionPos);

			_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;
			moveAmount.y = 0.f;
			_float3 moveForward = pOwner->GetTransform()->GetForward();
			moveForward.y = 0.f;
			D3DXVec3Normalize(&moveForward, &moveForward);

			_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);
			forwardMove = GetOwnerSizedPos(pOwner, forwardMove);
			pOwner->GetTransform()->AddPosition(forwardMove);
			pOwner->GetTransform()->SetPositionY(rootMotionPos.y);

		}
		// change end -> start
		pAniCtrl->ChangeFakeAnimState_EndToStart();
		m_prevRootMotionPos = m_animStartOffset;
		
		// 1% ?
		{
			pDM->UpdateFrame();

			_float3 rootMotionPos = GetRootMotionLocalPos(pDM);
			rootMotionPos = GetOwnerSizedPos(pOwner, rootMotionPos);

			float moveDir = (rootMotionPos.z - m_prevRootMotionPos.z) > 0.f ? 1.f : -1.f;
			_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;
			moveAmount.y = 0.f;
			_float3 moveForward = pOwner->GetTransform()->GetForward();
			moveForward.y = 0.f;
			D3DXVec3Normalize(&moveForward, &moveForward);

			_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);
			forwardMove = GetOwnerSizedPos(pOwner, forwardMove) * moveDir;
			pOwner->GetTransform()->AddPosition(forwardMove);
			pOwner->GetTransform()->SetPositionY(rootMotionPos.y);

			m_prevRootMotionPos = rootMotionPos;
		}
		
	}
	else
	{
		// Loop

		pDM->UpdateFrame();

		_float3 rootMotionPos = GetRootMotionLocalPos(pDM);

		float moveDir = (rootMotionPos.z - m_prevRootMotionPos.z) > 0.f ? 1.f : -1.f;
		_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;
		moveAmount.y = 0.f;
		_float3 moveForward = pOwner->GetTransform()->GetForward();
		moveForward.y = 0.f;
		D3DXVec3Normalize(&moveForward, &moveForward);

		_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);
		forwardMove = GetOwnerSizedPos(pOwner, forwardMove) * moveDir;
		pOwner->GetTransform()->AddPosition(forwardMove);
		pOwner->GetTransform()->SetPositionY(rootMotionPos.y);

		m_prevRootMotionPos = rootMotionPos;
	}

}

void CRootMotion::RootMotionMove_WhileChange(CObject * pOwner, CAniCtrl * pAniCtrl, CDynamicMeshData * pDM)
{
	// change

	if (!m_pIsFixRootMotionOffsets[pAniCtrl->GetFakeIndex()])
	{
		// none fix
		pAniCtrl->GetFakeAniCtrl()->AdvanceTime(pAniCtrl->GetFakePeriod() * 0.01, NULL);
		//pAniCtrl->GetFakeAniCtrl()->AdvanceTime(0, NULL);
		pDM->UpdateFrame();
		_float3 rootMotionPos = GetRootMotionLocalPos(pDM);
		m_animStartOffset = rootMotionPos;
		m_prevRootMotionPos = m_animStartOffset;
	}

	// update frame

	pAniCtrl->PlayFake();
	pDM->UpdateFrame();
	_float3 rootMotionPos = GetRootMotionLocalPos(pDM);

	float moveDir = (rootMotionPos.z - m_prevRootMotionPos.z) > 0.f ? 1.f : -1.f;
	_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;
	moveAmount.y = 0.f;
	_float3 moveForward = pOwner->GetTransform()->GetForward();
	moveForward.y = 0.f;
	D3DXVec3Normalize(&moveForward, &moveForward);

	_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);
	forwardMove = GetOwnerSizedPos(pOwner, forwardMove) * moveDir;
	pOwner->GetTransform()->AddPosition(forwardMove);
	pOwner->GetTransform()->SetPositionY(rootMotionPos.y * pOwner->GetTransform()->GetSize().y);

	m_prevRootMotionPos = rootMotionPos;


	pAniCtrl->SetIsFakeAniChange(false);
}

void CRootMotion::OnFixRootMotionOffset(_uint index)
{
	m_pIsFixRootMotionOffsets[index] = true;
}

void CRootMotion::OffFixRootMotionOffset(_uint index)
{
	m_pIsFixRootMotionOffsets[index] = false;
}

void CRootMotion::CreateFixOffsetArray(_uint size)
{
	m_pIsFixRootMotionOffsets = new bool[size];

	for (_uint i = 0; i < size; ++i)
	{
		m_pIsFixRootMotionOffsets[i] = false;
	}
}

_float3 CRootMotion::GetRootMotionLocalPos(CDynamicMeshData* pDM)
{
	_mat makeMeshLookAtMe;
	D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f));
	_mat rootCombMat = pDM->GetRootFrame()->TransformationMatrix * makeMeshLookAtMe;
	_mat rootChildCombMat = pDM->GetRootFrame()->pFrameFirstChild->TransformationMatrix * rootCombMat;
	
	return _float3(rootChildCombMat._41, rootChildCombMat._42, rootChildCombMat._43);
}

_float3 CRootMotion::GetOwnerSizedPos(CObject * pOwner, _float3 pos)
{
	_float3 size = pOwner->GetTransform()->GetSize();
	return _float3(
		pos.x * size.x,
		pos.y * size.y,
		pos.z * size.z);
}
