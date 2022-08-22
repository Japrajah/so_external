#include "bw_python.hh"
#include "../Addr.hh"
#include "py_offsets.hh"
int PyObject::ob_size()
{
	read<>

}


const char* PyTypeObject::tp_name()  
{
	char str_buffer[128] {}; // actualy u dont need use it because i want use s_types_ (super types) (stat and compare id /or pointer instead string 
	read(((unsigned long long)this + python::PyTypeObject::tp_name), str_buffer, 128);
}