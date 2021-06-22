#ifndef CLICULARGAUGESHADER_H
#define CLICULARGAUGESHADER_H

#include "Shader.h"
#include "Slider.h"

class CCircularGaugeShader final : public Engine::CShader
{
private:
	explicit CCircularGaugeShader(void);
	~CCircularGaugeShader(void);

public:
	static				Engine::CShader*			Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(Engine::CGraphicsC) spGC) override;

private:
	Engine::CSlider* m_spSlider;
	GETTOR_SETTOR(_int,		m_directionID,		UNDEFINED,		DirectionID)
};


#endif