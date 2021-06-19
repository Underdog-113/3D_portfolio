#ifndef SHADER_H
#define SHADER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CShader abstract : public CEngine
{
protected:
	explicit							CShader					(void);
	virtual							   ~CShader					(void);

public:
	virtual			void				Free					(void);
	virtual			void				Awake					(void);
public:
	virtual			void				SetUpConstantTable		(SP(CGraphicsC) spGC) PURE;
					void				SetupWorldViewProj		(SP(CGraphicsC) spGC);
protected:
	GETTOR			(LPD3DXEFFECT,		m_pEffect,				nullptr,		Effect)
	GETTOR			(LPD3DXBUFFER,		m_pErrMsg,				nullptr,		ErrMsg)
};
END

#endif