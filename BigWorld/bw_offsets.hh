#pragma once
namespace bw
{

	namespace Entity
	{





		constexpr auto pos = 0x40; // Vector3

	}
	namespace CameraImpl
	{





		constexpr auto viewmatrix = 0x1e4; // 

	}



	namespace EntityManager
	{

		// https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/client/entity_manager.hpp#L33
		constexpr auto enteredEntities_ = 0x20; // std::map<EntityID,Entity*>
		constexpr auto EntitiesCount = enteredEntities_ + 0x8; // 
		

		constexpr auto next = 0; // 
		constexpr auto EntityID = 0x14; // int32_t
		constexpr auto Entity = 0x18; // Entity*

	}





};

