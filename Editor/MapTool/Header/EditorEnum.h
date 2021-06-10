#ifndef EDITORENUM_H
#define EDITORENUM_H


enum class ESceneID
{
	Changmo,
	NumOfSceneID
};

enum class EComponentID
{
	Default = 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID
};


enum class EColliderID
{
	Player				= 0 + (_uint)Engine::EColliderID::NumOfColliderID,
	Enemy				= 1 + (_uint)Engine::EColliderID::NumOfColliderID,
	Object				= 2 + (_uint)Engine::EColliderID::NumOfColliderID,
	Map					= 3 + (_uint)Engine::EColliderID::NumOfColliderID,
	NumOfColliderID		= 4 + (_uint)Engine::EColliderID::NumOfColliderID
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
	Camera			= 3 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	UI				= 4 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID	= 5 + (_int)Engine::ELayerID::NumOfEngineLayerID
};
#endif // CLIENTENUM_H