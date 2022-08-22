#pragma once
#define Py_SIZE(pyobject)   *(unsigned int*)((unsigned long long )pyobject + 0x10) 
#define Py_TYPE(pyobject)   *(unsigned int*)((unsigned long long )pyobject + 0x8) 
 // http://pics.wikireality.ru/upload/9/9b/Thonk.png мое ебало когда думаю как удобней сделать чтение  классов
// либо делать read<PyObject> и уже работать с таким объектом
// либо делать read<PyObject*> и через методы читать от "this" нужные поля 
// второй варик мне нравится больше , но это как-то стремно как по мне
typedef size_t Py_ssize_t; 

class PyTypeObject;
class PyObject  // object.h 78 line
{
	Py_ssize_t ob_refcnt;
	PyTypeObject* ob_type;
public:
	int ob_size();
};

class PyVarObject : public PyObject // object.h 98 line
{
private:
	Py_ssize_t ob_size;  // 0x10 
public:
};


class PyTypeObject : public PyVarObject //  object.h 325 line
{
private:
	const char* tp_name; /*  0x18 */
	Py_ssize_t tp_basicsize, tp_itemsize; 
	char pad_0030[120]; //0x0030 //   
	long tp_flags; //0x00A8 to do replace with  drv.read 0xa8  because we dont want read usless pading
	/* 
	https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/lib/python/Include/object.h#L329
	*/
public:
	 const char* tp_name();
};
