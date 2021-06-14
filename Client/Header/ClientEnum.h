#ifndef CLIENTENUM_H
#define CLIENTENUM_H


enum class ESceneID
{
	Changmo,
	NumOfSceneID
};

enum class EComponentID
{
	Default				= 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	Text				= 1 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	NumOfComponentID	= 2 + (_uint)Engine::EComponentID::NumOfEngineComponentID
};


enum class ECollisionID
{
	Map					= 0 + (_uint)Engine::ECollisionID::NumOfColliderID,
	NumOfColliderID		= 1 + (_uint)Engine::ECollisionID::NumOfColliderID
};

enum class EDataID
{
	BasicObject			= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player				= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene				= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Enemy				= 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	UI					= 4 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID			= 5 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	Player			= 0 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Map				= 1 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Enemy			= 2 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID	= 3 + (_int)Engine::ELayerID::NumOfEngineLayerID
};

enum class ELoadingID
{
	StaticResource,
	BossSceneResource
};
#endif // CLIENTENUM_H