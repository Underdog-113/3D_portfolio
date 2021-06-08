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

	_float3 forward = pOwner->GetTransform()->GetForward();
	_float3 sizedPos = 
		_float3(ownerSize.x * m_rootMotionPos.x * forward.x,
			ownerSize.y * m_rootMotionPos.y * forward.y,
			ownerSize.z * m_rootMotionPos.z * forward.z);
	_float3 sizedOffset = _float3(ownerSize.x * m_rootMotionOffset.x, ownerSize.y * m_rootMotionOffset.y, ownerSize.z * m_rootMotionOffset.z);

	double timeline = pAniCtrl->GetFakeTimer() / pAniCtrl->GetFakePeriod();
	int timeRepeat = (int)timeline;
	timeline -= (double)timeRepeat;
	

	// change anim
	if (m_prevFakeIndex != pAniCtrl->GetFakeIndex())
	{
		if (!m_pIsFixRootMotionOffsets[pAniCtrl->GetFakeIndex()])
		{
			m_animStartPos = _float3(m_animEndPos.x - sizedOffset.x, 0.f, m_animEndPos.z - sizedOffset.z);
		}
		m_prevFakeIndex = pAniCtrl->GetFakeIndex();
		m_prevTimeLine = 0;
		return;
	}

	if (pAniCtrl->GetIsFakeAniEnd())
	{
		// loop
		pOwner->GetTransform()->AddPosition(m_animEndPos);
		m_animStartPos = _float3(m_animEndPos.x - sizedOffset.x, 0.f, m_animEndPos.z - sizedOffset.z);
		m_animEndPos = m_animStartPos + sizedPos;
		
		pOwner->GetTransform()->SetPosition(m_animEndPos);
		
		m_prevTimeLine = 0;
		pAniCtrl->SetIsFakeAniEnd(false);
	}
	else
	{
		m_animEndPos = m_animStartPos + sizedPos;
		pOwner->GetTransform()->SetPosition(m_animEndPos);

		m_prevTimeLine = timeline;
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
