#include "bw_entities.hh"
#include "bw_offsets.hh"
#include "../Addr.hh"
#define READ(type,offset)  read<type>((unsigned long long)this + offset);


// EntityMapEntry
EntityMapEntry* EntityMapEntry::next()
{
	return READ(EntityMapEntry*, bw::EntityManager::next);
}

Entity* EntityMapEntry::entity()
{
	return READ(Entity*, bw::EntityManager::Entity);
}

int EntityMapEntry::entityID()
{
	return READ(int, bw::EntityManager::EntityID);
}
// EntityManager
EntityManager* EntityManager::instance()
{
	return reinterpret_cast<EntityManager*>(game::g_entitymanager);
}

EntityMapEntry* EntityManager::Entities()
{
	return READ(EntityMapEntry*, bw::EntityManager::enteredEntities_);
}
int EntityManager::Entities_count()
{
		return READ(int , bw::EntityManager::EntitiesCount);
}


#undef READ