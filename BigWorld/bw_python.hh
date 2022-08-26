#pragma once
#include <string>
//#define Py_SIZE(pyobject)   *(unsigned int*)((unsigned long long )pyobject + 0x10) 
//#define Py_TYPE(pyobject)   *(unsigned int*)((unsigned long long )pyobject + 0x8) 
 // http://pics.wikireality.ru/upload/9/9b/Thonk.png мое ебало когда думаю как удобней сделать чтение  классов
// либо делать read<PyObject> и уже работать с таким объектом
// либо делать read<PyObject*> и через методы читать от "this" нужные поля 
// второй варик мне нравится больше , но это как-то стремно как по мне

// ебал в рот питон просто loadlibary игры сделаю
typedef size_t Py_ssize_t; 
class PyTypeObject	;
class PyDictObject;
class PyStringObject;

class PyObject;
// typeobject.c



class PyObject  // object.h 78 line
{
private:
	Py_ssize_t _ob_refcnt;
	PyTypeObject* _ob_type;
public:
	PyTypeObject* ob_type();
	PyDictObject* ob_dict();
	size_t ob_refcnt();
};

struct PyDictEntry
{
	Py_ssize_t 	me_hash;
	PyStringObject* me_key;
	PyObject* me_value;
};

class PyDictObject : public PyObject
{
	public:

		PyDictEntry	at(int i);
		size_t ma_mask();
	
	
		PyObject* find_item(const char* itemname);

	Py_ssize_t _ma_fill;  /* # Active + # Dummy */
	Py_ssize_t _ma_used;  /* # Active */

	///* The table contains ma_mask + 1 slots, and that's a power of 2.
	// * We store the mask instead of the size because the mask is more
	// * frequently needed.
	// */
	Py_ssize_t _ma_mask;

	///* ma_table points to ma_smalltable for small tables, else to
	// * additional malloc'ed memory.  ma_table is never NULL!  This rule
	// * saves repeated runtime null-tests in the workhorse getitem and
	// * setitem calls.
	// */
	PyDictEntry* _ma_table;
	void* _ma_fn;
	PyDictEntry _ma_smalltable[8];
};


class PyVarObject : public PyObject // object.h 98 line
{
private:
	Py_ssize_t _ob_size;  // 0x10 
public:
	size_t ob_size();
};
class PyStringObject : public PyVarObject // object.h 98 line
{
private:
	Py_ssize_t hash;  
	const char str[128];
public:
	size_t lenght() { return this->ob_size(); };
	std::string to_string();
};

class PyUnicodeObject : public PyVarObject // object.h 98 line
{
private:
	const wchar_t* str;
public:
	size_t lenght() { return this->ob_size(); };
	std::wstring to_wstring();
};

class PyTypeObject : public PyVarObject //  object.h 325 line
{
private:
	const char* _tp_name; /*  0x18 */
	Py_ssize_t _tp_basicsize, _tp_itemsize;
	char pad_0030[120]; //0x0030 //   
	long _tp_flags; //0x00A8 to do replace with  drv.read 0xa8  because we dont want read usless pading
	/* 
	https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/lib/py/Include/object.h#L329
	*/
public:
	 std::string tp_name();
	 size_t tp_basicsize();
	 size_t tp_itemsize();
	 int tp_dictoffset();

	 PyTypeObject* tp_base();
};

// py get  attr 