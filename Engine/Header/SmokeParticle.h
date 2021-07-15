#pragma once
#include "ParticleSystem.h"

BEGIN(Engine)
class ENGINE_DLL SmokeParticle : public CParticleSystem
{

public:
	SmokeParticle(BoundingBox* boundingBox, _uint numParticles);
	~SmokeParticle();

public:
	void resetParticle(ATTRIBUTE* _attribute);
	void Awake() override;
	void Start() override;
	void Update() override;
};
END
