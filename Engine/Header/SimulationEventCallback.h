#ifndef SIMULATIONEVENTCALLBACK_H
#define SIMULATIONEVENTCALLBACK_H

BEGIN(Engine)
class CSimulationEventCallback final : public PxSimulationEventCallback
{
	void	onConstraintBreak		(PxConstraintInfo* constraints, PxU32 count) override;
	void	onWake					(PxActor** actors, PxU32 count) override;
	void	onSleep					(PxActor** actors, PxU32 count) override;
	void	onContact				(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;
	void	onTrigger				(PxTriggerPair* pairs, PxU32 count) override;
	void	onAdvance				(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override;
};
END
#endif