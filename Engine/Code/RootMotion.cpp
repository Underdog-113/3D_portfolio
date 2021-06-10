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
			m_rootMotionPos.y * ownerSize.y,
			m_rootMotionPos.z * ownerSize.z);
	

	_float3 sizedLocalStartOffset =
		_float3(
			m_rootMotionOffset.x * ownerSize.x,
			m_rootMotionOffset.y * ownerSize.y,
			m_rootMotionOffset.z * ownerSize.z);

	// change anim
	if (m_prevFakeIndex != pAniCtrl->GetFakeIndex())
	{
		if (!m_pIsFixRootMotionOffsets[pAniCtrl->GetFakeIndex()])
		{
			m_prevSizedRootMotionPos = ZERO_VECTOR;

			_float3 worldOffset = ownerForward * D3DXVec3Length(&sizedLocalStartOffset);
			m_animStartWorldPos = _float3(m_animEndWorldPos.x, 0.f, m_animEndWorldPos.z) - worldOffset;
			m_animEndWorldPos = m_animStartWorldPos;
		}
		m_prevFakeIndex = pAniCtrl->GetFakeIndex();
		return;
	}

	if (pAniCtrl->GetIsFakeAniEnd())
	{
		/*
		pOwner->GetTransform()->AddPosition(m_animEndPos);
		m_animStartPos = _float3(m_animEndPos.x - sizedOffset.x, 0.f, m_animEndPos.z - sizedOffset.z);
		m_animEndPos = m_animStartPos + sizedPos;

		pOwner->GetTransform()->SetPosition(m_animEndPos);

		m_prevTimeLine = 0;
		pAniCtrl->SetIsFakeAniEnd(false);
		*/

		// loop
		m_animStartWorldPos = m_animEndWorldPos;

		_float3 worldOffset = ownerForward * D3DXVec3Length(&sizedLocalStartOffset);
		m_animStartWorldPos = _float3(m_animEndWorldPos.x, 0.f, m_animEndWorldPos.z) - worldOffset;

		_float3 forwardMoveAmount = ownerForward * D3DXVec3Length(&sizedRootMotionPos);
		m_animEndWorldPos = m_animStartWorldPos + forwardMoveAmount;

		pOwner->GetTransform()->SetPosition(m_animEndWorldPos);
				
		pAniCtrl->SetIsFakeAniEnd(false);
	}
	else
	{
		_float3 moveAmount = sizedRootMotionPos - m_prevSizedRootMotionPos;
		_float3 forwardMoveAmount = ownerForward * D3DXVec3Length(&moveAmount);
		m_animEndWorldPos += forwardMoveAmount;
		pOwner->GetTransform()->SetPosition(m_animEndWorldPos);
	}

	m_prevSizedRootMotionPos = sizedRootMotionPos;
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
