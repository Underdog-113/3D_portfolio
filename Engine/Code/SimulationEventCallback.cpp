#include "EngineStdafx.h"
#include "SimulationEventCallback.h"

USING(Engine)
void CSimulationEventCallback::onConstraintBreak(PxConstraintInfo * constraints, PxU32 count)
{
}

void CSimulationEventCallback::onWake(PxActor** actors, PxU32 count)
{
}

void CSimulationEventCallback::onSleep(PxActor** actors, PxU32 count)
{
}

void CSimulationEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	const PxU32 bufferSize = 64;
	PxContactPairPoint contacts[bufferSize];

	for (PxU32 i = 0; i < nbPairs; ++i)
	{
		const PxContactPair& curContactPair = pairs[i];
		PxU32 numOfContacts = curContactPair.extractContacts(contacts, bufferSize);

		for (PxU32 j = 0; j < numOfContacts; ++j)
		{
			PxVec3 point = contacts[j].position;
		}
	}
}

void CSimulationEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	//loop through all trigger-pairs of PhysX simulation
	for (PxU32 i = 0; i < count; i++)
	{
		//get current trigger actor & other actor info 
		//from current trigger-pair 
		const PxTriggerPair& curTriggerPair = pairs[i];

		PxRigidActor* triggerActor = curTriggerPair.triggerActor;
		PxRigidActor* otherActor = curTriggerPair.otherActor;
	}
}

void CSimulationEventCallback::onAdvance(const PxRigidBody*const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
{
}
