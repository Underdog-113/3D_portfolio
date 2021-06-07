#pragma once
#include "Particle.h"

class CTestParticle : public Engine::CParticle
{
	SMART_DELETER_REGISTER

public:	
	CTestParticle(Engine::BoundingBox* _boundingBox, _int _numParticles);
	~CTestParticle() = default;

virtual	void resetParticle(Engine::ATTRIBUTE* _attribute) override;

virtual SP(CObject) MakeClone(void) override;

virtual void Awake(void) override;

virtual void Start(void) override;

virtual void FixedUpdate(void) override;

virtual	void Update() override;

virtual void LateUpdate(void) override;

virtual void OnDestroy(void) override;

virtual void OnEnable(void) override;

virtual void OnDisable(void) override;

virtual void SetBasicName(void) override;

};

