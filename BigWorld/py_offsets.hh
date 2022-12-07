#pragma once
namespace py
{
	const auto constexpr nextptr = 8;
	static_assert(nextptr == 8, "should be always 8"); // because write +8 ugly for me
	 // PyObject
		constexpr auto ob_type = 0x8; // _typeobject
		constexpr auto ob_refcnt = 0x0; //  size_t
	 // PyObject
		namespace VarObject // : PyObject
		{ 
			constexpr auto ob_size = 0x10; 	// size_t ob_size;
		}

	
		namespace TypeObject // : PyVarObject : PyObject
		{
			constexpr auto tp_name = 0x18; // const char*
			constexpr auto tp_basicsize = tp_name + nextptr; // size_t
			constexpr auto tp_itemsize = tp_basicsize + nextptr; //  size_t
			constexpr auto tp_flags = 0xA8; // long
			constexpr auto tp_dictoffset = 0x120; // ???  long size_t ???
			constexpr auto tp_base =  0x100; // PyTypeObject*  

		}

		namespace dictObject //  
		{
			constexpr auto   ma_fill = ob_type + nextptr; //   Py_ssize_t 
			constexpr auto ma_used = ma_fill + nextptr;  //    Py_ssize_t 
			constexpr auto  ma_mask = ma_used + nextptr;  //    Py_ssize_t 
			constexpr auto   ma_table = ma_mask + nextptr;  //  PyDictEntry*
			constexpr auto   ma_fn = ma_table + nextptr;  // 
			constexpr auto   ma_smalltable = ma_fn + nextptr;  // 

		}

		namespace ListObject //  : PyVarObject : PyObject
		{
			constexpr auto   ob_item = VarObject::ob_size + nextptr; // PyObject** 
			constexpr auto allocated = ob_item + nextptr;  //    Py_ssize_t allocated;
		}
		namespace Model //  : PyVarObject : PyObject
		{
			constexpr auto   SuperModel = 0x100; // SuperModel* 
			constexpr auto   visible = 0x318;// 0x214; // bool
			constexpr auto localBoundingBox_ = 0x1f0;// 0x1f0
			constexpr auto localVisibilityBox_ = 0x1fc; // 0x1fc
		 // 	PyModelNodes		knownNodes_; // 0x270
	
		}
		// PyObjectPlus this just PyObject but with vtable so every offset += 8;
}
	
