#include <cstdint>
#include "../Addr.hh"
#include "bw_python.hh"
#include "py_offsets.hh"
#define THISREAD(type,offset)  read<type>((unsigned long long)this + offset)

/// PyObject
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
///\ 



/// PyDictObject
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
	auto str = std::string(itemname);
	for (size_t i = 0; i <= this->ma_mask(); i++)  // https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/lib/python/Objects/dictobject.c#L944
	{
		auto ep = this->at(i);
		auto pkey= ep.me_key;
		if (!pkey) continue;
		auto  key_name = pkey->to_string();
		if (str == key_name)
			return ep.me_value;
	}


	return 0;
}
///\ 


/// PyVarObject
size_t PyVarObject::ob_size()
{
	return read<size_t>(&this->_ob_size);
}
///\ 



/// PyStringObject
std::string PyStringObject::to_string()
{
	auto slen = this->lenght() + 1;
	char stack_buffer[128];
	if (slen <= 1 || slen >= 127)
		return std::string("str_to_long");
	read((uintptr_t)(&this->str), stack_buffer, slen );
	stack_buffer[127] = '\0';
	return std::string(stack_buffer);
	//char str_buffer[128]{}; 
	//read((uintptr_t)(&this->str), str_buffer, 127);
	//return std::string(str_buffer);
}
///\ 

/// PyUnicodeObject

std::wstring PyUnicodeObject::to_wstring()
{
	auto slen =this->lenght() +1;
	wchar_t stack_buffer[128];
	if (slen <= 1 || slen >= 127)
		return std::wstring(L"wstr_to_long");
	read(read<uintptr_t>(&this->str), stack_buffer, slen*2);
	stack_buffer[127] = L'\0';
	return std::wstring(stack_buffer);
}

///\ 


/// PyTypeObject 
std::string PyTypeObject::tp_name()
{
	char stack_buffer[128];
	read(read<uintptr_t>(&this->_tp_name), stack_buffer, 127);
	stack_buffer[127] = '\0';
	return  std::string(stack_buffer);
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
///\ 

#undef THISREAD