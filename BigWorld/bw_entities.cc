#include "bw_entities.hh"
#include "bw_globals.hh"
#include "bw_offsets.hh"
#include "../Addr.hh"

#define THISREAD(type,offset)  read<type>((unsigned long long)this + offset)

//#define THISWRITE(type,offset,VALUE)  write<type>((unsigned long long)this + offset,VALUE)

Vector3 Entity::position()
{
	return THISREAD(Vector3, bw::Entity::pos);
}
// Avatar


//\








// CameraImpl
CameraImpl* CameraImpl::Instance()
{
	return read<CameraImpl*>(game::umbra_camera);
}

bool CameraImpl::ProjectWorldToScreen( Vector3 position, Vector2* screenpos)
{
	//auto matrix = read<Matrix4x4>(&this->matrix); // 0x28 w 0x30 h resolution
	auto matrix = THISREAD(Matrix4x4,0x1e4);

	float sw = bw_globals::Wscreen, sh = bw_globals::Hscreen;
	float x = matrix.m[0][0] * position.x + matrix.m[0][1] * position.y + matrix.m[0][2] * position.z + matrix.m[0][3];
	float y = matrix.m[1][0] * position.x + matrix.m[1][1] * position.y + matrix.m[1][2] * position.z + matrix.m[1][3];
	float w = matrix.m[3][0] * position.x + matrix.m[3][1] * position.y + matrix.m[3][2] * position.z + matrix.m[3][3];
	if (w < 0.01f) return false;
	x *= 1.f / w;
	screenpos->x = (sw * 0.5f) + (0.5f * x * sw + 0.5f);
	if (screenpos->x > 10000 || screenpos->x < -10000) return false;
	y *= 1.f / w;
	screenpos->y = (sh * 0.5f) - (0.5f * y * sh + 0.5f);
	if (screenpos->y > 10000 || screenpos->y < -10000) return false;
	return true;
}

//\






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
//\


// EntityManager
EntityManager* EntityManager::instance()
{
	return reinterpret_cast<EntityManager*>(game::g_entitymanager);
}

EntityMap EntityManager::Entities()
{
	return THISREAD(EntityMap, bw::EntityManager::enteredEntities_);
}
//\


#undef THISREAD