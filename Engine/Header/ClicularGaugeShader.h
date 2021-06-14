#ifndef CLICULARGAUGESHADER_H
#define CLICULARGAUGESHADER_H

#include "Shader.h"
#include "Slider.h"
BEGIN(Engine)
class ENGINE_DLL CClicularGaugeShader final : public CShader
{
private:
	explicit CClicularGaugeShader(void);
	~CClicularGaugeShader(void);

public:
	static				CShader*			Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(CGraphicsC) spGC) override;

private:
	CSlider* m_spSlider;
	GETTOR_SETTOR(_int,		m_directionID,		UNDEFINED,		DirectionID)
};
END

#endif