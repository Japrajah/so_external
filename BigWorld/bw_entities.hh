#pragma once

struct Entity
{

	
};

struct EntityMapEntry
{
	EntityMapEntry* next();
	Entity* entity();
	int entityID();
};

struct EntityManager
{
	static EntityManager* instance(); //  https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/client/entity_manager.hpp#L48
	EntityMapEntry* Entities();
	int Entities_count();
};