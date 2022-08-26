#include <cstdint>
#include "../Addr.hh"
#include "bw_python.hh"
#include "py_offsets.hh"
#define THISREAD(type,offset)  read<type>((unsigned long long)this + offset)
size_t PyObject::ob_refcnt()
{
	return read<size_t>(&this->_ob_refcnt);
	
}



PyTypeObject* PyObject::ob_type()
{
//	return THISREAD(PyTypeObject*,py::ob_type);
	return read<PyTypeObject*>(&this->_ob_type);
}

PyDictObject* PyObject::ob_dict()
{
	auto type = this->ob_type();
	if (!type) return nullptr;
	auto dict_offset = type->tp_dictoffset();
	if (!dict_offset) return nullptr;
	return THISREAD(PyDictObject*, dict_offset);
}

PyDictEntry	PyDictObject::at(int idx)
{
	return read<PyDictEntry>(THISREAD(uintptr_t,py::dictObject::ma_table) + sizeof(PyDictEntry) * idx);
}
size_t	PyDictObject::ma_mask()
{
	//return THISREAD(size_t, py::dictObject::ma_mask);
	return read<size_t>(&this->_ma_mask);
}

PyObject* PyDictObject::find_item(const char* itemname) // 	PyObject* find_item(const char* itemname)
{
	for (size_t i = 0; i <= this->ma_mask(); i++)  // https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/lib/python/Objects/dictobject.c#L944
	{
		auto ep = this->at(i);
		PyObject* pvalue = ep.me_value;
		PyObject* pkey= ep.me_key;

	}


	return 0;
}


size_t PyVarObject::ob_size()
{
	return read<size_t>(&this->_ob_size);
}

std::string PyTypeObject::tp_name()
{
	char str_buffer[128]{}; // actualy u dont need use it because i want use s_types_ (super types)  and compare id /or pointer instead string 
	read(read<uintptr_t>(&this->_tp_name), str_buffer, 128);
	return  std::string(str_buffer);
}

size_t PyTypeObject::tp_basicsize()
{
	return read<size_t>(&this->_tp_basicsize);
}

int PyTypeObject::tp_dictoffset()
{
	return THISREAD(int, py::TypeObject::tp_dictoffset);
}

size_t PyTypeObject::tp_itemsize()
{
	return read<size_t>(&this->_tp_itemsize);
}


PyTypeObject* PyTypeObject::tp_base()
{
	return THISREAD(PyTypeObject*, py::TypeObject::tp_base);
}

#undef THISREAD