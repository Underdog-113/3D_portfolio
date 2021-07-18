#ifndef DECALSHADER_H
#define DECALSHADER_H

#include "Shader.h"

class CDecalShader final : public Engine::CShader
{
private:
	explicit CDecalShader(void);
	~CDecalShader(void);

public:
	static				Engine::CShader*			Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	Engine::CSlider* m_spSlider;
	GETTOR_SETTOR(_int, m_directionID, UNDEFINED, DirectionID)
};

#endif