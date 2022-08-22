#pragma once
namespace python
{
	const auto constexpr nextptr = 8;
	static_assert(nextptr == 8, "should be always 8"); // because write +8 ugly for me
	 // PyObject
		constexpr auto ob_type = 0x8; // _typeobject
		constexpr auto ob_refcnt = 0x0; //  size_t
	 // PyObject
		namespace PyVarObject // : PyObject
		{ 
			constexpr auto ob_size = 0x10; 	// size_t ob_size;
		}

	
		namespace PyTypeObject // : PyVarObject : PyObject
		{
			constexpr auto tp_name = 0x18; // const char*
			constexpr auto tp_basicsize = tp_name + nextptr; // size_t
			constexpr auto tp_itemsize = tp_basicsize + nextptr; //  size_t
			constexpr auto tp_flags = 0xA8; // long
		}
		namespace PyListObject //  : PyVarObject : PyObject
		{
			constexpr auto   ob_item = PyVarObject::ob_size + nextptr; // PyObject** 
			constexpr auto allocated = ob_item + nextptr;  //    Py_ssize_t allocated;
		}

}
	
