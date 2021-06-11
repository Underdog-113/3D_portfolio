#include "EngineStdafx.h"
#include "RootMotion.h"

#include "AniCtrl.h"

USING(Engine)

CRootMotion::CRootMotion()
{
}


CRootMotion::~CRootMotion()
{
	if (m_pIsFixRootMotionOffsets)
		delete[] m_pIsFixRootMotionOffsets;
}

void CRootMotion::RootMotionMove(CObject * pOwner, CAniCtrl * pAniCtrl)
{
	// root motion
	_float3 ownerSize = pOwner->GetTransform()->GetSize();

	_float3 ownerForward = pOwner->GetTransform()->GetForward();
	ownerForward.y = 0.f;
	D3DXVec3Normalize(&ownerForward, &ownerForward);

	_float3 sizedRootMotionPos = 
		_float3(
			m_rootMotionPos.x * ownerSize.x,
			0.f,//m_rootMotionPos.y * ownerSize.y,
			m_rootMotionPos.z * ownerSize.z);
	

	_float3 sizedLocalStartOffset =
		_float3(
			m_rootMotionOffset.x * ownerSize.x,
			0.f,//m_rootMotionOffset.y * ownerSize.y,
			m_rootMotionOffset.z * ownerSize.z);

	float moveDir = (sizedRootMotionPos.z - m_prevSizedRootMotionPos.z) > 0.f ? 1.f : -1.f;
	ownerForward *= moveDir;

	// change anim
	if (m_prevFakeIndex != pAniCtrl->GetFakeIndex())
	{
		if (!m_pIsFixRootMotionOffsets[pAniCtrl->GetFakeIndex()])
		{
			m_prevSizedRootMotionPos = ZERO_VECTOR;
		}


		m_prevFakeIndex = pAniCtrl->GetFakeIndex();
		return;
	}

	//if (pAniCtrl->GetIsFakeAniEnd())
	//{
	//	/*
	//	pOwner->GetTransform()->AddPosition(m_animEndPos);
	//	m_animStartPos = _float3(m_animEndPos.x - sizedOffset.x, 0.f, m_animEndPos.z - sizedOffset.z);
	//	m_animEndPos = m_animStartPos + sizedPos;

	//	pOwner->GetTransform()->SetPosition(m_animEndPos);

	//	m_prevTimeLine = 0;
	//	pAniCtrl->SetIsFakeAniEnd(false);
	//	*/

	//	// loop
	//	_float3 curOwnerPos = pOwner->GetTransform()->GetPosition();
	//	curOwnerPos.y = 0.f;

	//	_float3 moveAmount = sizedRootMotionPos - m_prevSizedRootMotionPos;
	//	_float3 forwardMoveAmount = ownerForward * D3DXVec3Length(&moveAmount);
	//	_float3 worldOffset = ownerForward * D3DXVec3Length(&sizedLocalStartOffset);

	//	pOwner->GetTransform()->SetPosition(curOwnerPos + forwardMoveAmount - worldOffset);
	//			
	//	pAniCtrl->SetIsFakeAniEnd(false);
	//	pAniCtrl->PlayFake_SavedTime();
	//}
	//else
	//{
	//	_float3 moveAmount = sizedRootMotionPos - m_prevSizedRootMotionPos;
	//	_float3 forwardMoveAmount = ownerForward * D3DXVec3Length(&moveAmount);
	//	pOwner->GetTransform()->AddPosition(forwardMoveAmount);
	//}

	if (pAniCtrl->GetIsFakeAniStart())
	{
		// loop
		_float3 curOwnerPos = pOwner->GetTransform()->GetPosition();
		curOwnerPos.y = 0.f;

		_float3 worldOffset = ownerForward * D3DXVec3Length(&sizedLocalStartOffset);
		pOwner->GetTransform()->SetPosition(curOwnerPos - worldOffset);
		m_startWorldOffset = worldOffset;
				
		pAniCtrl->SetIsFakeAniStart(false);
	}

	_float3 moveAmount = sizedRootMotionPos - m_prevSizedRootMotionPos;
	_float3 forwardMoveAmount = ownerForward * D3DXVec3Length(&moveAmount);
	pOwner->GetTransform()->AddPosition(forwardMoveAmount);

	m_prevSizedRootMotionPos = sizedRootMotionPos;

	if (pAniCtrl->GetIsFakeAniEnd())
	{
		_float3 worldOffset = ownerForward * D3DXVec3Length(&sizedLocalStartOffset);
		m_endWorldOffset = worldOffset;

		m_prevSizedRootMotionPos = ZERO_VECTOR;
		pAniCtrl->PlayFake_SavedTime();
	}
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
