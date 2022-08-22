#include <iostream>
#include "Addr.hh"

int main()
{
	mem::ReaderInit();
	std::cout << std::hex << mem::Base <<std::endl;

}
