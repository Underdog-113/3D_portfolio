#pragma once

#ifndef ROOTMOTION_H
#define ROOTMOTION_H


BEGIN(Engine)

class CAniCtrl;
class ENGINE_DLL CRootMotion final
{
public:
	explicit	CRootMotion();
			   ~CRootMotion();

public:
	CRootMotion*	MakeClone	(void);

	void		RootMotionMove(CObject* pOwner, CAniCtrl* pAniCtrl, CDynamicMeshData* pDM);
	void		RootMotionMove_WhileChange(CObject* pOwner, CAniCtrl* pAniCtrl, CDynamicMeshData* pDM);

	void		OnFixRootMotionOffset(_uint index);
	void		OffFixRootMotionOffset(_uint index);

	void		CreateFixOffsetArray(_uint size);

	_float3		GetRootMotionLocalPos(CObject* pOwner, CDynamicMeshData* pDM);
	_float3		GetOwnerSizedPos(CObject * pOwner, _float3 pos);
private:
	GETTOR			(_bool*,	m_pIsFixRootMotionOffsets,	nullptr,		IsFixRootMotionOffsets)
	GETTOR_SETTOR	(_bool,		m_isRootMotion,				false,			IsRootMotion)

	GETTOR_SETTOR	(_float3,	m_rootMotionOffset,			ZERO_VECTOR,	RootMotionOffset)
	GETTOR_SETTOR	(_float3,	m_rootMotionPos,			ZERO_VECTOR,	RootMotionPos)
		
	GETTOR_SETTOR	(_float,	m_speed,					0.f,			Speed)

	GETTOR_SETTOR	(_bool,		m_isVerticalAnim,			false,			IsVerticalAnim)

	_float3 m_animStartOffset = ZERO_VECTOR;
	_float3 m_prevRootMotionPos = ZERO_VECTOR;
};

END

#endif
