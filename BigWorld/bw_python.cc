#include <cstdint>
#include "../Addr.hh"
#include "bw_python.hh"
#include "py_offsets.hh"


size_t PyVarObject::ob_size()
{
	return read<size_t>((uintptr_t)this + python::VarObject::ob_size);
}

const char* PyTypeObject::tp_name()
{
	char str_buffer[128]{}; // actualy u dont need use it because i want use s_types_ (super types)  and compare id /or pointer instead string 
	read(((uintptr_t)this + python::TypeObject::tp_name), str_buffer, 128);
	return  str_buffer;
}

size_t PyTypeObject::tp_basicsize()
{
	return read<size_t>((uintptr_t)this + python::TypeObject::tp_basicsize);
}

size_t PyTypeObject::tp_itemsize()
{
	return read<size_t>((uintptr_t)this + python::TypeObject::tp_itemsize);
}


PyTypeObject* PyTypeObject::tp_base()
{
	return read<PyTypeObject*>((uintptr_t)this + python::TypeObject::tp_base);
}

