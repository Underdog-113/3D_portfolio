#include "stdafx.h"
#include "..\Header\Shot_FixPivot.h"


CShot_MovePivot::CShot_MovePivot()
{
}


CShot_MovePivot::~CShot_MovePivot()
{
}

void CShot_MovePivot::Ready(CTake * pTake, _float startTimeline, _float endTimeline, void * pDesc, _float enterTimeline)
{
	CShot::Ready(pTake, startTimeline, endTimeline, pDesc, enterTimeline);

	memcpy(&m_desc, pDesc, sizeof(Desc));

	m_savedPivotPos = m_pCameraMan->GetPivot()->GetTransform()->GetPosition();
}

void CShot_MovePivot::Enter()
{
	if (m_desc.pTargetMat)
	{
		_float3 pivotPos = _float3(m_desc.pTargetMat->_41, m_desc.pTargetMat->_42, m_desc.pTargetMat->_43);
		m_pCameraMan->GetPivot()->GetTransform()->SetPosition(pivotPos + m_desc.startOffset);
	}
	else
		m_pCameraMan->GetPivot()->GetTransform()->SetPosition(m_savedPivotPos + m_desc.startOffset);
}

void CShot_MovePivot::Action()
{
	CShot::Action();


	_float timeline = GetTimeline();

	_float3 curOffset = GetLerpFloat3(m_desc.startOffset, m_desc.endOffset, timeline);
	
	if (m_desc.pTargetMat)
	{
		_float3 pivotPos = _float3(m_desc.pTargetMat->_41, m_desc.pTargetMat->_42, m_desc.pTargetMat->_43);
		m_pCameraMan->GetPivot()->GetTransform()->SetPosition(pivotPos + curOffset);
	}
	else
		m_pCameraMan->GetPivot()->GetTransform()->SetPosition(m_savedPivotPos + curOffset);
}

void CShot_MovePivot::Cut()
{
}

void CShot_MovePivot::Rollback()
{
	m_pCameraMan->GetPivot()->GetTransform()->SetPosition(m_savedPivotPos);
}
