#ifndef SLIDERSHADER_H
#define SLIDERSHADER_H

#include "Shader.h"
#include "Slider.h"
BEGIN(Engine)
class ENGINE_DLL CSliderShader final : public CShader
{
private:
	explicit							CSliderShader(void);
	~CSliderShader(void);

public:
	static				CShader*			Create(void);
	void				Free(void);

	void				Awake(void) override;

public:
	void				SetUpConstantTable(SP(CGraphicsC) spGC) override;

private:
	CSlider* m_spSlider;
	GETTOR_SETTOR		(_int,		m_directionID,		UNDEFINED,		DirectionID)
};
END

#endif