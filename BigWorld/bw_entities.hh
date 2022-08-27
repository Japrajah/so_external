#pragma once
#include "bw_python.hh"
#include "Vectors.hh"






struct Entity : public PyObject
{


	
};
struct Avatar : public Entity
{
	Py_dicthead;

	Py_Attribute(Avatar,PyUnicodeObject*, name);
	Py_Attribute(Avatar,PyObject*, position);

	//Py_Attribute(PyObject*, skeletonCollider);

};

struct CursorCamera : public PyObject // CursorCamera : BaseCamera : PyObjectPlus : object
{
	char pad[0x18];
	Matrix4x4 matrix;
};


struct PlayerAvatar : public Avatar
{
	Py_dicthead;
	Py_Attribute(PlayerAvatar, CursorCamera*, AvatarCam); // CursorCamera : BaseCamera : PyObjectPlus : object

};
struct Creature : public Avatar
{
	

};
struct NPC : public Avatar
{
	


};
struct EntityMapEntry
{
	EntityMapEntry* next();
	Entity* entity();
	int entityID();
};
struct EntityMap
{
	EntityMapEntry* iter;
	int num;
};

struct EntityManager
{
	static EntityManager* instance(); //  https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/client/entity_manager.hpp#L48
	EntityMap Entities();
};