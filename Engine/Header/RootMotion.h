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
	void		RootMotionMove(CObject* pOwner, CAniCtrl* pAniCtrl);

	void		OnFixRootMotionOffset(_uint index);
	void		OffFixRootMotionOffset(_uint index);

private:
	GETTOR			(_bool*,	m_pIsFixRootMotionOffsets,	nullptr,		IsFixRootMotionOffsets)
	GETTOR_SETTOR	(_bool,		m_isRootMotion,				false,			IsRootMotion)
		
	GETTOR			(_float3,	m_rootMotionOffset,			ZERO_VECTOR,	RootMotionOffset)
	GETTOR_SETTOR	(_float3,	m_rootMotionPos,			ZERO_VECTOR,	RootMotionPos)

	_float3 m_animStartPos = ZERO_VECTOR;
	_float3 m_animEndPos = ZERO_VECTOR;
	double m_prevTimeLine = 0;
	_uint m_prevFakeIndex = 0;
};

END

#endif