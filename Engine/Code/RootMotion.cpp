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

CRootMotion * CRootMotion::MakeClone(void)
{
	CRootMotion* pClone = new CRootMotion;

	pClone->m_pIsFixRootMotionOffsets = m_pIsFixRootMotionOffsets;
	m_prevMoveAmount = _float3(100.f, 100.f, 100.f);

	return pClone;
}

void CRootMotion::RootMotionMove(CObject * pOwner, CAniCtrl * pAniCtrl, CDynamicMeshData* pDM)
{
	pAniCtrl->PlayFake();

	if (pAniCtrl->GetIsFakeAniEnd())
	{
		// 99% ?
		{
//			pDM->UpdateFrame();

// 			_float3 rootMotionPos = GetRootMotionLocalPos(pOwner, pDM);
//
// 			_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;
// 			moveAmount.y = 0.f;
// 			_float3 moveForward = pOwner->GetTransform()->GetForward();
// 			moveForward.y = 0.f;
// 			D3DXVec3Normalize(&moveForward, &moveForward);
//
// 			_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);
// 			pOwner->GetTransform()->AddPosition(forwardMove);
//
// 			if(m_isVerticalAnim)
// 				pOwner->GetTransform()->SetPositionY(rootMotionPos.y * pOwner->GetTransform()->GetSize().y);

		}
		// change end -> start
		pAniCtrl->ChangeFakeAnimState_EndToStart();
		pDM->UpdateFrame();
		//m_prevRootMotionPos = GetRootMotionLocalPos(pOwner, pDM);
		m_prevRootMotionPos = m_animStartOffset;
		m_prevMoveAmount = ZERO_VECTOR;
		// 1% ?
		{
			//pDM->UpdateFrame();

// 			_float3 rootMotionPos = GetRootMotionLocalPos(pOwner, pDM);
//
// 			float moveDir = (rootMotionPos.z - m_prevRootMotionPos.z) > 0.f ? 1.f : -1.f;
// 			_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;
// 			moveAmount.y = 0.f;
// 			_float3 moveForward = pOwner->GetTransform()->GetForward();
// 			moveForward.y = 0.f;
// 			D3DXVec3Normalize(&moveForward, &moveForward);
//
// 			_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);
// 			forwardMove *= moveDir;
// 			pOwner->GetTransform()->AddPosition(forwardMove);
//
// 			if (m_isVerticalAnim)
// 				pOwner->GetTransform()->SetPositionY(rootMotionPos.y * pOwner->GetTransform()->GetSize().y);
//
// 			if (m_isVerticalAnim)
// 				pOwner->GetTransform()->SetPositionY(rootMotionPos.y * pOwner->GetTransform()->GetSize().y);
//
// 			m_prevRootMotionPos = rootMotionPos;
		}

	}
	else
	{
		// Loop

		pDM->UpdateFrame();

		_float3 rootMotionPos = GetRootMotionLocalPos(pOwner, pDM);

		float moveDir = (rootMotionPos.z - m_prevRootMotionPos.z) > 0.f ? 1.f : -1.f;
		_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;

		moveAmount.y = 0.f;
		_float3 moveForward = pOwner->GetTransform()->GetForward();
		moveForward.y = 0.f;
		D3DXVec3Normalize(&moveForward, &moveForward);

		_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);

		_float3 startNoY = m_animStartOffset;
		startNoY.y = 0.f;
		_float3 startToCur = m_prevRootMotionPos - startNoY;
		if (pDM->GetAniTimeline() < 0.1)
		{
			if (D3DXVec3Length(&forwardMove) > D3DXVec3Length(&m_prevMoveAmount) * 1.2f &&
				D3DXVec3Length(&forwardMove) > D3DXVec3Length(&startToCur) * 0.75f)
			{
				if(!m_isTargetCollide)
					pOwner->GetTransform()->AddPosition(m_prevMoveAmount);
				return;
			}
		}

		forwardMove *= moveDir;
		m_prevMoveAmount = forwardMove;
		if (!m_isTargetCollide)
			pOwner->GetTransform()->AddPosition(forwardMove);
		if (m_isVerticalAnim)
			pOwner->GetTransform()->SetPositionY(rootMotionPos.y * pOwner->GetTransform()->GetSize().y);

		m_prevRootMotionPos = rootMotionPos;
	}

}

void CRootMotion::RootMotionMove_WhileChange(CObject * pOwner, CAniCtrl * pAniCtrl, CDynamicMeshData * pDM)
{
	// change
	pAniCtrl->GetFakeAniCtrl()->AdvanceTime(pAniCtrl->GetFakePeriod(), NULL);
	pAniCtrl->GetFakeAniCtrl()->SetTrackPosition(pAniCtrl->GetFakeTrack(), 0.0);

	pAniCtrl->PlayFake();
	pDM->UpdateFrame();
	_float3 rootMotionPos = GetRootMotionLocalPos(pOwner, pDM);

	if (!m_pIsFixRootMotionOffsets[pAniCtrl->GetFakeIndex()])
	{
		// none fix
		m_animStartOffset = rootMotionPos;
	}

	m_prevRootMotionPos = rootMotionPos;

	// update frame

	//pAniCtrl->PlayFake();
	//pDM->UpdateFrame();
	//_float3 rootMotionPos = GetRootMotionLocalPos(pOwner, pDM);
	//float moveDir = (rootMotionPos.z - m_prevRootMotionPos.z) > 0.f ? 1.f : -1.f;
	//_float3 moveAmount = rootMotionPos - m_prevRootMotionPos;
	//moveAmount.y = 0.f;
	//_float3 moveForward = pOwner->GetTransform()->GetForward();
	//moveForward.y = 0.f;
	//D3DXVec3Normalize(&moveForward, &moveForward);
	//
	//_float3 forwardMove = moveForward * D3DXVec3Length(&moveAmount);
	//forwardMove *= moveDir;
	//pOwner->GetTransform()->AddPosition(forwardMove);
	//
	//if (m_isVerticalAnim)
	//	pOwner->GetTransform()->SetPositionY(rootMotionPos.y * pOwner->GetTransform()->GetSize().y);
	//
	//m_prevRootMotionPos = rootMotionPos;


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

_float3 CRootMotion::GetRootMotionLocalPos(CObject* pOwner, CDynamicMeshData* pDM)
{
	_mat makeMeshLookAtMe;
	D3DXMatrixRotationY(&makeMeshLookAtMe, D3DXToRadian(180.f));
	_mat rootCombMat = pDM->GetRootFrame()->TransformationMatrix * makeMeshLookAtMe;

	D3DXFRAME* pBip001Frame = pDM->GetRootFrame()->pFrameFirstChild;
	while (strcmp(pBip001Frame->Name, "Bip001"))
	{
		pBip001Frame = pBip001Frame->pFrameFirstChild;
	}
	_mat rootChildCombMat = pBip001Frame->TransformationMatrix * rootCombMat;

//	return _float3(
//		rootChildCombMat._41,
//		rootChildCombMat._42,
//		rootChildCombMat._43);

	return GetOwnerSizedPos(pOwner,
		_float3(rootChildCombMat._41,
		rootChildCombMat._42,
		rootChildCombMat._43));

}

_float3 CRootMotion::GetOwnerSizedPos(CObject * pOwner, _float3 pos)
{
	_float3 size = pOwner->GetTransform()->GetSize();
	return _float3(
		pos.x * size.x,
		pos.y * size.y,
		pos.z * size.z);
}
