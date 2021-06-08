#include "EngineStdafx.h"
#include "RootMotion.h"

#include "AniCtrl.h"

USING(Engine)

CRootMotion::CRootMotion()
{
}


CRootMotion::~CRootMotion()
{
	delete[] m_pIsFixRootMotionOffsets;
}

void CRootMotion::RootMotionMove(CObject * pOwner, CAniCtrl * pAniCtrl)
{
	// root motion
	_float3 ownerSize = pOwner->GetTransform()->GetSize();

	_float3 sizedPos = _float3(ownerSize.x * m_rootMotionPos.x, ownerSize.y * m_rootMotionPos.y, ownerSize.z * m_rootMotionPos.z);
	_float3 sizedOffset = _float3(ownerSize.x * m_rootMotionOffset.x, ownerSize.y * m_rootMotionOffset.y, ownerSize.z * m_rootMotionOffset.z);

	double timeline = pAniCtrl->GetFakeTimer() / pAniCtrl->GetFakePeriod();
	int timeRepeat = (int)timeline;
	timeline -= (double)timeRepeat;


	// change anim
	if (m_prevFakeIndex != pAniCtrl->GetFakeIndex())
	{
		m_animStartPos = _float3(m_animEndPos.x - sizedOffset.x, 0.f, m_animEndPos.z - sizedOffset.z);
		m_prevFakeIndex = pAniCtrl->GetFakeIndex();
		
		m_prevTimeLine = 0;
		return;
	}

	if (timeline < m_prevTimeLine)
	{
		// loop
		m_animEndPos = m_animStartPos + sizedPos;
		m_animStartPos = _float3(m_animEndPos.x - sizedOffset.x, 0.f, m_animEndPos.z - sizedOffset.z);
		pOwner->GetTransform()->AddPosition(m_animEndPos);
		m_prevTimeLine = 0;
	}
	else
	{
		m_animEndPos = m_animStartPos + sizedPos;
		pOwner->GetTransform()->SetPosition(m_animEndPos);

		m_prevTimeLine = timeline;
		m_animEndPosLastFrame = m_animEndPos;
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
