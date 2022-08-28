#include <cstdint>
#include "../Addr.hh"
#include "bw_python.hh"
#include "py_offsets.hh"
#define THISREAD(type,offset)  read<type>((unsigned long long)this + offset)


 // helper
//https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/lib/python/Objects/stringobject.c#L1206
long py_string_hash(const char* a)
{
	auto len = strlen(a);
	auto lencopy = len;
	auto p = (unsigned char*)a;
	long x = *p << 7;
	while (--len >= 0)
		x = (1000003 * x) ^ *p++;
	x ^= lencopy;
	if (x == -1)
		x = -2;
	return x;
}







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

PyDictObject* PyObject::ob_dict(int* dictoffset)
{
	if (*dictoffset == 0)
	{
		auto type = this->ob_type();
		if (!type) return nullptr;
		*dictoffset = type->tp_dictoffset();
		if (!dictoffset) return nullptr;
	}
	return THISREAD(PyDictObject*, *dictoffset);
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
PyDictEntry	PyDictObject::at(int idx) // need read to buf  and after just PyDictObject[idx]
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
	auto dict_size = this->ma_mask();
	auto dict_entry = new PyDictEntry[dict_size+1];
	auto p_entry = THISREAD(uintptr_t, py::dictObject::ma_table);
	if (!read(p_entry, dict_entry, dict_size * sizeof(PyDictEntry))) goto FAIL;
	for (size_t i = 0; i <= dict_size; i++)  // https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/lib/python/Objects/dictobject.c#L944
	{
		//auto ep = this->at(i); external parse
		auto ep = dict_entry[i];
		auto pkey= ep.me_key;
		if (!pkey) continue;
		auto  key_name = pkey->to_string();
		if (str == key_name) 
		{
		
			auto result = ep.me_value;
			str.~basic_string();
			delete[] dict_entry;
			return result;
		}
			
	}
FAIL:
	str.~basic_string();
	 delete[] dict_entry;
	return 0;
}
///\ 


/// PyVarObject
size_t PyVarObject::ob_size()
{
	return read<size_t>(&this->_ob_size);
}
///\ 


// PyINT8Object
__int8 PyINT8Object::get()
{
	return THISREAD(__int8, &this->value);
}

void PyINT8Object::set(__int8 val)
{
	//	 THISWRITE(__int8, &this->value,val);
}




//\


/// PyStringObject
std::string PyStringObject::to_string()
{
	auto slen = this->lenght() + 1;
	char stack_buffer[128];
	if (slen <= 1 || slen >= 127)
		return std::string("str_error");
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
		return std::wstring(L"wstr_error");
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
std::string PyTypeObject::fullname() {
	std::string temp = this->tp_name();
	for (auto parrent = this->tp_base(); parrent; parrent = parrent->tp_base()) {
		if (!parrent) break;
		auto name = parrent->tp_name();
		if (name.empty()) break;
		temp = temp + " : " + std::string(name);
	}
	return temp;
}

///\ 

#undef THISREAD