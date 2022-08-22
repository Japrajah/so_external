#pragma once
#define Py_SIZE(pyobject)   *(unsigned int*)((unsigned long long )pyobject + 0x10) 
#define Py_TYPE(pyobject)   *(unsigned int*)((unsigned long long )pyobject + 0x8) 
 // http://pics.wikireality.ru/upload/9/9b/Thonk.png мое ебало когда думаю как удобней сделать чтение  классов
// либо делать read<PyObject> и уже работать с таким объектом
// либо делать read<PyObject*> и через методы читать от "this" нужные поля 
// второй варик мне нравится больше , но это как-то стремно как по мне

// ебал в рот питон просто loadlibary игры сделаю
typedef size_t Py_ssize_t; 


// typeobject.c
struct method_cache_entry {
	unsigned int version;
	PyObject* name;		/* reference to exactly a str or None */
	PyObject* value;	/* borrowed */
};


class PyTypeObject;
class PyObject  // object.h 78 line
{
private:
	Py_ssize_t _ob_refcnt;
	PyTypeObject* _ob_type;
public:
	
};

class PyVarObject : public PyObject // object.h 98 line
{
private:
	Py_ssize_t _ob_size;  // 0x10 
public:
	size_t ob_size();
};


class PyTypeObject : public PyVarObject //  object.h 325 line
{
private:
	const char* _tp_name; /*  0x18 */
	Py_ssize_t _tp_basicsize, _tp_itemsize;
	char pad_0030[120]; //0x0030 //   
	long _tp_flags; //0x00A8 to do replace with  drv.read 0xa8  because we dont want read usless pading
	/* 
	https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/lib/python/Include/object.h#L329
	*/
public:
	 const char* tp_name();
	 size_t tp_basicsize();
	 size_t tp_itemsize();
	 PyTypeObject* tp_base();
};

// python get  attr 