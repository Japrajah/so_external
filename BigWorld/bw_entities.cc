#include "bw_entities.hh"
#include "bw_offsets.hh"
#include "../Addr.hh"
#define THISREAD(type,offset)  read<type>((unsigned long long)this + offset)


// EntityMapEntry
EntityMapEntry* EntityMapEntry::next()
{
	
	return THISREAD(EntityMapEntry*, bw::EntityManager::next);
}

Entity* EntityMapEntry::entity()
{
	auto ent = THISREAD(unsigned __int64, bw::EntityManager::Entity);
	return (Entity*)(ent) ; 
}

int EntityMapEntry::entityID()
{
	return THISREAD(int, bw::EntityManager::EntityID);
}
// EntityManager
EntityManager* EntityManager::instance()
{
	return reinterpret_cast<EntityManager*>(game::g_entitymanager);
}

EntityMap EntityManager::Entities()
{
	return THISREAD(EntityMap, bw::EntityManager::enteredEntities_);
}



#undef THISREAD